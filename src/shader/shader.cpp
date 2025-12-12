#include <FileWatch.hpp>
#include <filesystem>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <sstream>

#include "shader.hpp"

GLenum shaderTypeFromExtension(const std::string& ext)
{
    if (ext == "vert" || ext == "vs" || ext == "vsh")
        return GL_VERTEX_SHADER;
    if (ext == "frag" || ext == "fs" || ext == "fsh")
        return GL_FRAGMENT_SHADER;
    if (ext == "geom" || ext == "gs" || ext == "gsh")
        return GL_GEOMETRY_SHADER;
    // if (ext == "tesc" || ext == "tcs")
    //     return GL_TESS_CONTROL_SHADER;
    // if (ext == "tese" || ext == "tes")
    //     return GL_TESS_EVALUATION_SHADER;

    /// if you pass only a .comp file, the class will create a compute-only program — calling use() is fine and then you can glDispatchCompute(...).
    if (ext == "comp" || ext == "cs")
        return GL_COMPUTE_SHADER;

    throw std::runtime_error("Unknown shader extension: " + ext);
}

std::string getShaderStage(const std::string& filename)
{
    size_t lastDot = filename.rfind('.');
    if (lastDot == std::string::npos)
        return "";

    std::string lastExt = filename.substr(lastDot + 1);

    // Case 1: shader.vert.glsl → lastExt == "glsl"
    if (lastExt == "glsl") {
        size_t secondDot = filename.rfind('.', lastDot - 1);
        if (secondDot == std::string::npos)
            return "";

        return filename.substr(secondDot + 1, lastDot - secondDot - 1); // extracts "vert"
    }

    // Case 2: shader.vert → return "vert"
    return lastExt;
}

static std::string readFileToString(const std::string& path)
{
    std::ifstream file(path, std::ios::in);
    // file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_NOT_FOUND" << std::endl;
        // throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(const std::vector<std::string>& shaderPaths, bool enableAutoReload)
{
    if (shaderPaths.empty())
        throw std::runtime_error("ERROR::SHADER::EMPTY_SHADER_PATHS"); // Don't let the program run

    loadedPaths = shaderPaths;

    std::vector<GLuint> compiledShaders;
    compiledShaders.reserve(shaderPaths.size());

    int success;
    char infoLog[512];

    try {
        for (const std::string& path : shaderPaths) {
            GLenum type = shaderTypeFromExtension(getShaderStage(path));

            std::string code = readFileToString(path);
            const char* shaderCode = code.c_str();

            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &shaderCode, nullptr);
            glCompileShader(shader);

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::COMPILATION_FAILED (" << path << ")\n"
                          << infoLog << "\n";
            }

            compiledShaders.push_back(shader);
        }

        ID = glCreateProgram();
        for (const GLuint s : compiledShaders)
            glAttachShader(ID, s);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM_LINK_FAILED\n"
                      << infoLog << "\n";
        }

        for (GLuint s : compiledShaders)
            glDeleteShader(s);
    } catch (const std::exception& e) {
        for (const GLuint s : compiledShaders)
            glDeleteShader(s);
        if (ID != 0) {
            glDeleteProgram(ID);
            ID = 0;
        }
        throw; // rethrow to let caller handle
    }

    if (enableAutoReload && !watcher) {
        std::string directory = std::filesystem::path(shaderPaths.front()).parent_path().string();
        setupWatcher(directory);
        if (watcher) {
            std::cout << "Watcher is set for directory: " << directory << std::endl;
        }
    }
}

Shader::~Shader()
{
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, glm::vec3 vector) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}

void Shader::setupWatcher(const std::string& directory)
{
    watcher = std::make_unique<filewatch::FileWatch<std::string>>(
        directory,
        [this](const std::string& path, const filewatch::Event change_type) {
            using namespace std::chrono;
            if (change_type == filewatch::Event::added || change_type == filewatch::Event::modified) {
                std::cout << "change detected" << std::endl;
                std::this_thread::sleep_for(milliseconds(1000));
                this->change();
            }
            if (change_type == filewatch::Event::removed) {
                std::cout << "Warning: " << path << " was removed." << std::endl;
            }
        });
}

void Shader::reload()
{
    this->ID = Shader(loadedPaths, false).ID;
    std::cout << "Shader reloaded" << std::endl;
}

void Shader::change()
{
    reloadRequested = true;
}

void Shader::autoreload()
{
    if (reloadRequested.exchange(false)) {
        reload();
    }
}