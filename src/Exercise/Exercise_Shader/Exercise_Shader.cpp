//
// Created by Gal on 9/14/26.
//

#include "Exercise_Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

Exercise_Shader::Exercise_Shader(const char* vertexPath,const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
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

        vShaderFile.close();
        fShaderFile.close();

        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();
    }catch (std::ifstream::failure& e) {
        std::cout<<"ERROR"<<e.what()<<std::endl;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertex,fragment;
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertexSource,NULL);
    glCompileShader(vertex);
    CheckSuccess(vertex,"vertex");

    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragmentSource,NULL);
    glCompileShader(fragment);
    CheckSuccess(fragment,"fragment");

    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    CheckSuccess(ID,"program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Exercise_Shader::use() {
    glUseProgram(ID);
}

void Exercise_Shader::CheckSuccess(unsigned int shader, std::string name) {
    int success;
    char infoLog[512];
    if (name == "Program") {
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if (!success) {
            glGetProgramInfoLog(shader,512,NULL,infoLog);
            std::cout<<name<<": "<<infoLog<<std::endl;
        }
    }
    else {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if (!success) {
            glGetShaderInfoLog(shader,512,NULL,infoLog);
            std::cout<<"ERROR"<<name<<": "<<infoLog<<std::endl;
        }
    }
}
