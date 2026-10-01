#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#include<Shader.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void proIn(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}
void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"",NULL,NULL);
    if (window == NULL) {
        std::cout<<"Failed to create GLFW window!"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD!"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices[] {
         -.5f,.5f,0.f,  0.f,1.f,
          .5f,.5f,0.f,  1.f,1.f,
         .5f,-.5f,0.f,  1.f,0.f,
        -.5f,-.5f,0.f,  0.f,0.f,
    };
    unsigned int indices[]={
        0,1,2,
        0,2,3,
    };

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("/home/Gal/Projects/learnopengl/src/Transform_Learning/vertex","/home/Gal/Projects/learnopengl/src/Transform_Learning/fragment");

    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1,&texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    int width,height,nrChannels;
    unsigned char* data = stbi_load("/home/Gal/Projects/textures_Pictures/超时空辉夜姬.jpg",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout<<"Failed to load texture"<<std::endl;
        glfwTerminate();
        return -1;
    }

    stbi_image_free(data);
    shader.Use();
    shader.setInt("texture0",0);

    unsigned int transformLoc = glGetUniformLocation(shader.ID,"transform");

    while (!glfwWindowShouldClose(window)) {
        proIn(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        //matrix
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans,glm::vec3(0.5f,-0.5f,0.0f));
        trans = glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0,0.0,1.0));
        //缩放+旋转
        //最后一个参数代表旋转轴
        // trans = glm::scale(trans,glm::vec3(.5f,.5f,.5f));
        //首先我们将图片在每个轴上缩放0.5,再沿z轴旋转90度
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteTextures(1,&texture);

    glfwTerminate();
    return 0;
}