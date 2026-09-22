//
// Created by Gal on 9/22/26.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath,const char* fragmentPath) {
        std::ifstream vertexFile, fragmentFile;
        std::string vertexCode, fragmentCode;

        vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try {
            vertexFile.open(vertexPath);
            fragmentFile.open(vertexPath);

            std::stringstream vShaderStream, fShaderStream;
            vShaderStream<<vertexFile.rdbuf();
            fShaderStream<<fragmentFile.rdbuf();

            vertexFile.close();
            fragmentFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" <<e.what()<< std::endl;
        }
        const char* vShaderSource = vertexCode.c_str();
        const char* fShaderSource = fragmentCode.c_str();

        unsigned int vertex,fragment;
        vertex=glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vertexSource,NULL);
        glCompileShader(vertex);
        Check(vertex,"vertex");
        fragment=glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fragmentSource,NULL);
        glCompileShader(fragment);
        Check(fragment,"fragment");

        ID = glCreateProgram();
        glAttachShader(ID,vertex);
        glAttachShader(ID,fragment);
        glLinkProgram(ID);
        Check(ID,"program");
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use() {
        glUseProgram(ID);
    }

    void setInt(const char* name, int value) const {
        glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
    }
    void SetFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
    }

private:
    void Check(unsigned mem,std::string Type) {
        int success;
        char infoLog[512];
        if (Type == "program") {
            glGetProgramiv(mem,GL_LINK_STATUS,&success);
            if (!success) {
                glGetProgramInfoLog(mem,512,NULL,infoLog);
                std::cout<<Type<<" ERROR:"<<infoLog<<std::endl;
            }
        }else {
            glGetShaderiv(mem,GL_COMPILE_STATUS,&success);
            if (!success) {
                glGetShaderInfoLog(mem,512,NULL,infoLog);
                std::cout<<Type<<" ERROR:"<<infoLog<<std::endl;
            }
        }
    }
};
#endif //LEARNOPENGL_SHADER_H
