#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>

#include "../shader/shader.hpp"
#include "mesh.h"

class Model {
public:
    Model(char* path);

    void Draw(Shader& shader);

private:
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif
