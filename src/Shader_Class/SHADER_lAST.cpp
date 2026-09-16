#include"SHADER.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void procInput(GLFWwindow* window);
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window=glfwCreateWindow(800,800,"LAST",NULL,NULL);
    if (window==NULL) {
        std::cout<<"failed to create window"<<std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"failed to initialize glad"<<std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glViewport(0,0,800,800);

    //build and compile our Shader program
    Shader ourShader("/home/Gal/Projects/learnopengl/src/Shader_Class/vertexShader","/home/Gal/Projects/learnopengl/src/Shader_Class/fragmentShader");

    float vertices[]={
        -1.f,-1.f,0.f, 1.f,0.f,0.f,     //position and color
        0.f,1.f,0.f, 0.f,1.f,0.f,
        1.f,-1.f,0.f, 0.f,0.f,1.f,
    };

    unsigned int VAO,VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        procInput(window);
        glClearColor(.4f,.2f,.8f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    glViewport(0,0,width,height);
}
void procInput(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
}