//
// Created by Gal on 9/17/26.
//

#ifndef LEARNOPENGL_TEXTURE_2_H
#define LEARNOPENGL_TEXTURE_2_H

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Texture_2 {
public:
    unsigned int ID;
    Texture_2(const std::string& vertexPath,const std::string& fragmentPath ) {
        std::ifstream vertexFile,fragmentFile;
        std::string vertexCode,fragmentCode;

        vertexFile.exceptions(std::ifstream::badbit |  std::ifstream::failbit);
        fragmentFile.exceptions(std::ifstream::badbit |  std::ifstream::failbit);
        try {
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);

            std::stringstream vShaderstream,fShaderstream;
            vShaderstream<<vertexFile.rdbuf();
            fShaderstream<<fragmentFile.rdbuf();

            vertexCode=vShaderstream.str();
            fragmentCode=fShaderstream.str();
        }catch (std::ifstream::failure& e) {
            std::cout<<"ERROR: "<<e.what()<<std::endl;
        }
        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        unsigned int vertex,fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vertexSource,NULL);
        glCompileShader(vertex);
        Check(vertex,"vertex");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fragmentSource,NULL);
        glCompileShader(fragment);
        Check(fragment,"fragment");

        ID = glCreateProgram();
        glAttachShader(ID,vertex);
        glAttachShader(ID,fragment);
        glLinkProgram(ID);
        Check(ID,"program");


    }

    void use(){
        glUseProgram(ID);
    }

    void setInt(std::string name,int value) const{
        glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
    }

private:
    void Check(unsigned int shader,std::string name) {
        int success;
        char infoLog[512];
        if (name == "program") {
            glGetProgramiv(ID,GL_LINK_STATUS,&success);
            if (!success) {
                glGetProgramInfoLog(ID,512,NULL,infoLog);
                std::cout<<"Program could not be linked:"<<std::endl;
                std::cout<<infoLog<<std::endl;
            }
        }else {
            glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
            if (!success) {
                glGetShaderInfoLog(shader,512,NULL,infoLog);
                std::cout<<"ERROR: "<<name<<": "<<infoLog<<std::endl;
            }
        }
    }


};
#endif //LEARNOPENGL_TEXTURE_2_H
