#include "SHADER.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>

SHADER::SHADER(const char* vertexpath,const char* fragpath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        vShaderFile.open(vertexpath);
        fShaderFile.open(fragpath);
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex,fragment;
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    Debug(vertex,"vertex");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    Debug(fragment,"fragment");

    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    Debug(ID,"Program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void SHADER::use() {
    glUseProgram(ID);
}

void SHADER::Debug(unsigned int Shader,const std::string name) {
    char infoLog[512];
    int success;
    if (name=="vertex" || name=="fragment") {
        glGetShaderiv(Shader,GL_COMPILE_STATUS,&success);
        if (!success) {
            glGetShaderInfoLog(Shader,512,NULL,infoLog);
            std::cout << name<<"compilation failed: " << infoLog << std::endl;
        }
    }else {
        glGetProgramiv(Shader,GL_LINK_STATUS,&success);
        if (!success) {
            glGetProgramInfoLog(Shader,512,NULL,infoLog);
            std::cout << name<<"link failed: " << infoLog << std::endl;
        }
    }
}