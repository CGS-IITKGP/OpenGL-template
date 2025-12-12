#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <FileWatch.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <string>

class Shader {
private:
    std::vector<std::string> loadedPaths; // paths of shaders

    std::unique_ptr<filewatch::FileWatch<std::string>> watcher = NULL;
    std::atomic<bool> reloadRequested = false;

public:
    unsigned int ID = 0;

    explicit Shader(const std::vector<std::string>& shaderPaths, bool enableAutoReload = true);
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
