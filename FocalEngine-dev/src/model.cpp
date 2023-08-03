#include "model.h"

Model::Model(std::string componentName, std::string path)
	:System("Model", componentName)
{
	directory.changePath(path);
	Assimp::Importer m_importer;
    debugger.giveMessage(NixTools::Debugger::Info, "Loading", path);
	m_scene = m_importer.ReadFile(directory.getPath(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);
    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
    {
        debugger.giveMessage(NixTools::Debugger::Error, "Model Loading", m_importer.GetErrorString());
    }
    else
    {
        ProcessNode(m_scene->mRootNode, m_scene);
        ProcessTexture(m_scene);
    }
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshList.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        glm::vec3 data;

        //Get vertex data.
        Vertex vertex;
        data.x = mesh->mVertices[i].x;
        data.y = mesh->mVertices[i].y;
        data.z = mesh->mVertices[i].z;
        vertex.position = data;

        //Get Normal data
        data.x = mesh->mNormals[i].x;
        data.y = mesh->mNormals[i].y;
        data.z = mesh->mNormals[i].z;
        vertex.normal = data;

        //Get Texture Coordinates if any exists
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
        }
        else
        {
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    //Get Index data
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    m_textureID.push_back(mesh->mMaterialIndex);
    return new Mesh(vertices, indices);
}

void Model::ProcessTexture(const aiScene* scene)
{
    m_textureList.resize(scene->mNumMaterials);
    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
        m_textureList[i] = nullptr;

        aiMaterial* material = scene->mMaterials[i];
        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int idx = std::string(path.data).rfind("\\");
                std::string filename = std::string(path.data).substr(idx + 1);

                std::string texPath = std::string("/res/texture/model/") + directory.getFileName() + "/" + filename;
                debugger.giveMessage(NixTools::Debugger::Info, "Loading", texPath);

                m_textureList[i] = new Texture(texPath);

                if (!m_textureList[i]->LoadTexture())
                {
                    debugger.giveMessage(NixTools::Debugger::Error, "Failed to load a texture", texPath);
                    delete m_textureList[i];
                    m_textureList[i] = nullptr;
                }
            }
        }
        if (!m_textureList[i])
        {
            m_textureList[i] = new Texture("/res/texture/default.png");
            m_textureList[i]->LoadTexture();
        }
    }
}

void Model::RenderModel()
{
    for (size_t i = 0; i < m_meshList.size(); i++)
    {
        unsigned int materialIndex = m_textureID[i];

        if (materialIndex < m_textureList.size() && m_textureList[materialIndex])
        {
            m_textureList[materialIndex]->Bind();
            m_meshList[i]->RenderMesh();
            m_textureList[materialIndex]->Unbind();
        }
        else
        {
            m_meshList[i]->RenderMesh();
        }
    }
}