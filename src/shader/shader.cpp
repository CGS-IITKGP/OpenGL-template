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

unsigned int Shader::compile(GLenum type, const std::string& src, const std::string& path)
{
    unsigned int shader = glCreateShader(type);
    int success;
    char infoLog[512];

    const char* shaderCode = src.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "\nERROR::SHADER::" << type << "::COMPILATION_FAILED (" << path << ")\n"
                  << infoLog << std::endl;
    }

    return shader;
}

void Shader::linkProgram(std::vector<unsigned int> shaders)
{
    this->ID = glCreateProgram();
    int success;
    char infoLog[512];

    for (unsigned s : shaders)
        glAttachShader(ID, s);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "\nERROR::SHADER::PROGRAM_LINK_FAILED\n"
                  << infoLog << "\n";
    }

    for (unsigned s : shaders)
        glDeleteShader(s);
}

Shader::Shader(std::string vertexPath, const std::string fragmentPath, bool enableAutoReload)
    : Shader(vertexPath, "", fragmentPath, enableAutoReload)
{
}

Shader::Shader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, bool enableAutoReload)
{
    std::string vShaderCode = readFileToString(vertexPath);

    std::string fShaderCode = readFileToString(fragmentPath);

    unsigned int vertex = compile(GL_VERTEX_SHADER, vShaderCode, vertexPath);
    unsigned int fragment = compile(GL_FRAGMENT_SHADER, fShaderCode, fragmentPath);

    if (!geometryPath.empty()) {
        std::string gShaderCode = readFileToString(geometryPath);
        unsigned int geometry = compile(GL_GEOMETRY_SHADER, gShaderCode, geometryPath);

        linkProgram({ vertex, geometry, fragment });
        this->geometryPath = geometryPath;
    } else
        linkProgram({ vertex, fragment });

    this->vertexPath = vertexPath;
    this->fragmentPath = fragmentPath;

    if (enableAutoReload)
        setupStageWatcher();
}

Shader::Shader(std::string computePath, bool enableAutoReload)
{
    std::string cShaderCode = readFileToString(computePath);
    unsigned int compute = compile(GL_COMPUTE_SHADER, cShaderCode, computePath);

    linkProgram({ compute });

    this->computePath = computePath;

    if (enableAutoReload)
        setupStageWatcher();
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

void Shader::setupStageWatcher()
{
    if (watcher)
        return;

    std::string path = computePath.empty() ? vertexPath : computePath;
    std::string directory = std::filesystem::path(path).parent_path().string();

    setupWatcher(directory);
    if (watcher) {
        std::cout << "Watcher is set for directory: " << directory << std::endl;
    }
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
    this->ID = Shader(vertexPath, fragmentPath, false).ID;
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