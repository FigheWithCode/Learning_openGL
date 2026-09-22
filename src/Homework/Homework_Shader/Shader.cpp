#include "Shader.h"
#include<iostream>
#include<cmath>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffersizecallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void procInput(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window=glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (window==NULL) {
        std::cout<<"failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"failed to initialize GLAD"<<std::endl;
        return -1;
    }
    glViewport(0,0,800,800);

    glfwSetFramebufferSizeCallback(window,framebuffersizecallback);

    float vertices[]={
        -1.f,1.f,1.f,
        0.f,1.f,1.f,
        -.5f,-1.f,1.f,
    };
    Shader shader("/home/Gal/Projects/learnopengl/src/Homework/Homework_Shader/vertexShader","/home/Gal/Projects/learnopengl/src/Homework/Homework_Shader/fragmentShader");

    unsigned int VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)) {
        procInput(window);
        glClearColor(.3f,.2f,.6f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue=glfwGetTime();
        float value = std::sin(timeValue);
        int location = glGetUniformLocation(shader.ID,"offset");
        shader.Use();
        glUniform3f(location,value,0,0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}