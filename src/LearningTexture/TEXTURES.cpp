#include "TEXTURES.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

TEXTURES::TEXTURES(std::string vertexPath,std::string fragmentPath) {
    std::string vertexCode,fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch (std::ifstream::failure& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertex,fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertexSource,NULL);
    glCompileShader(vertex);
    Debug(vertex,"vertex");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragmentSource,NULL);
    glCompileShader(fragment);
    Debug(fragment,"fragment");

    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    Debug(ID,"program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void TEXTURES::use() {
    glUseProgram(ID);
}

void TEXTURES::setInt(const std::string& name,int value) const{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
void TEXTURES::Debug(unsigned int shader, std::string name) {
    int success;
    char infoLog[512];
    if (name == "program") {
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if (!success) {
            glGetProgramInfoLog(shader,512,NULL,infoLog);
            std::cout <<" ERRORR: "<< name << infoLog << std::endl;
        }
    }else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader,512,NULL,infoLog);
            std::cout << "ERROR: " << name << ": " << infoLog << std::endl;
        }

    }
}
