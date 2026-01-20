#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace Acroy
{
    std::string read_file(const char* path)
    {
        std::ifstream in(path, std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        
        std::cout << "Failed to read: " << path << std::endl;
        return "ERROR";
    }

    void checkShaderCompilation(GLuint shader, const std::string& name)
    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::string infoLog(logLength, ' ');
            glGetShaderInfoLog(shader, logLength, nullptr, &infoLog[0]);
            std::cout << "ERROR: Shader compilation failed (" << name << ")" << std::endl << infoLog << std::endl;
        }
    }

    Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
    {
        uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
        uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vsSource = read_file(vertexShaderPath);
        std::string fsSource = read_file(fragmentShaderPath);

        const char* vsCharStr = vsSource.c_str();
        const char* fsCharStr = fsSource.c_str();

        glShaderSource(vs, 1, &vsCharStr, nullptr);
        glShaderSource(fs, 1, &fsCharStr, nullptr);

        glCompileShader(vs);
        checkShaderCompilation(vs, "Vertex Shader");
        
        glCompileShader(fs);
        checkShaderCompilation(fs, "Fragment Shader");

        _id = glCreateProgram();
        glAttachShader(_id, vs);
        glAttachShader(_id, fs);

        glLinkProgram(_id);
        GLint success;
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLint logLength;
            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
            std::string infoLog(logLength, ' ');
            glGetProgramInfoLog(_id, logLength, nullptr, &infoLog[0]);
            std::cout << "ERROR: Program linking failed" << std::endl << infoLog << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader()
    {
        glDeleteProgram(_id);
    }

    void Shader::Bind() const
    {
        glUseProgram(_id);
    }

    void Shader::UnBind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniformMat4(const char* name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, false, glm::value_ptr(value));
    }

    void Shader::SetUniformInt(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(_id, name), value);
    }

    void Shader::SetUniformFloat(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(_id, name), value);
    }

    void Shader::SetUniformVec4(const char* name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(value));
    }
}