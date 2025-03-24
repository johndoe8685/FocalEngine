#include "shader.h"

Shader::Shader(std::string componentName,const std::string& fragmentShader,const std::string& vertexShader)
    :System(componentName, "Shader"), m_FragmentFilePath(fragmentShader), m_VertexFilePath(vertexShader), m_ModuleID(0)
{
    std::string fragmentShaderDir = directory.getWorkDirectory() + fragmentShader;
    std::string vertexShaderDir = directory.getWorkDirectory()  + vertexShader;
    std::string fragmentSource = GetShaderSource(fragmentShaderDir);
    std::string vertexSource = GetShaderSource(vertexShaderDir);
    m_ModuleID = CreateShader(vertexSource, fragmentSource);
}

std::string Shader::GetShaderSource(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[1];
    while (getline(stream, line)) {
        ss[0] << line << '\n';
    }
    return ss[0].str();
}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        debugger.giveMessage(NixTools::Error, "CreateShader::Program compliation failed", infoLog);
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int  success;
    char infoLog[512];
    glValidateProgram(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        debugger.giveMessage(NixTools::Error, "CompileShader::Shader compliation failed", infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationMap.find(name) != m_UniformLocationMap.end())
    {
        return m_UniformLocationMap[name];
    }
    else
    {
        int location = glGetUniformLocation(m_ModuleID, name.c_str());
        if (location == -1)
            debugger.giveMessage(NixTools::Warning, "GetUniformLocation::Uniform Doesnt exist", name);
        return location;
    }
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
{
    Bind();
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    Unbind();
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    Bind();
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    Unbind();
}
void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    Bind();
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
    Unbind();
}
void Shader::SetUniform1f(const std::string& name, float v0)
{
    Bind();
    glUniform1f(GetUniformLocation(name), v0);
    Unbind();
}
void Shader::SetUniform1i(const std::string& name, int v0)
{
    Bind();
    glUniform1i(GetUniformLocation(name), v0);
    Unbind();
}
