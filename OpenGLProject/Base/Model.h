#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Render/Shader.h"
#include <glm/glm.hpp>
namespace GL3D
{
    using namespace std;
    struct Vertex
    {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        aiString path;
    };



    class Mesh {
        
    public:
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader shader);
        void InstancingDraw(Shader shader,int count);
        unsigned int GetVAO();
        void BindTexture();
    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
        void SetShaderTexture(Shader shader);
        bool needReBindTexture;
    };

    class Model
    {
    public:
        Model(const char*path, bool gamma = false);
        void Draw(Shader shader);
        vector<Mesh> meshes;
        vector<Texture> textures_loaded;
        void InstancingDraw(Shader shader, int count);
    private:


        string directory;
        bool gammaCorrection;
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            string typeName);
    };

}


