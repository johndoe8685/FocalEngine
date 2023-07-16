#include "texture.h"

Texture::Texture(const std::string& path)
    :m_textureID(0), m_BPP(0), m_filepath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), System("Texture")
{
    directory.changePath(m_filepath);
}

bool Texture::LoadTexture()
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(directory.getPath().c_str(), &m_Width, &m_Height, &m_BPP, 4);
    if (!m_LocalBuffer)
    {
        debugger.giveMessage(NixTools::Debugger::Error, "Failed to Find", m_filepath);
        return false;
    }
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    //TODO: Create Texture Parameter Interface so Model could define their looks by coding it.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
    }
    return true;
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}
void Texture::Blend() const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}
void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


