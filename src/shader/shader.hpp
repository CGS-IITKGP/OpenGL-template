#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <FileWatch.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <string>

class Shader {
private:
    std::string vertexPath;
    std::string fragmentPath;
    std::string geometryPath;
    std::string computePath;

    std::unique_ptr<filewatch::FileWatch<std::string>> watcher = NULL;
    std::atomic<bool> reloadRequested = false;

    void linkProgram(std::vector<unsigned int> shaders);
    void setupStageWatcher();

public:
    unsigned int ID = 0;

    // Forward C-string paths to the std::string overload to avoid ambiguity.
    Shader(char const* vertexPath, char const* fragmentPath)
        : Shader(std::string(vertexPath), std::string(fragmentPath))
    {
    }

    Shader(char const* vertexPath, char const* geometryPath, char const* fragmentPath)
        : Shader(std::string(vertexPath), std::string(geometryPath), std::string(fragmentPath))
    {
    }

    Shader(std::string vertexPath, std::string fragmentPath, bool enableAutoReload = true);
    Shader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, bool enableAutoReload = true);

    explicit Shader(std::string computePath, bool enableAutoReload = true);

    ~Shader();

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(const std::string& name, glm::vec3 vector) const;
    void reload();
    void setupWatcher(const std::string& directory);
    void change();
    void autoreload();
};

#endif
