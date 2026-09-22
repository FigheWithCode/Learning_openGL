#include"Shader.h"

#include<iostream>
#include<cmath>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffersizecallback(GLFWwindow* window,int width,int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}
void proc(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window=glfwCreateWindow(800,800,"",NULL,NULL);
    if (window==NULL) {
        std::cout<<"Failed to create a window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800);
    glfwSetFramebufferSizeCallback(window,framebuffersizecallback);


    float vertices[] {
        -.5f,.5f,1.f, .5f,0.f,0.f,
        .5f,.5f,1.f, 0.f,.5f,0.f,
        0.f,-1.f,1.f, 0.f,0.f,.5f,
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader Shader("/home/Gal/Projects/learnopengl/src/Exercise/Exercise_Shader/vertex","/home/Gal/Projects/learnopengl/src/Exercise/Exercise_Shader/fragment");

    while(!glfwWindowShouldClose(window)) {
        proc(window);

        glClearColor(1.f,.4f,.6f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float Value = std::sin(timeValue);
        float off=Value;
        float Blue = Value/2;

        int vertexOff = glGetUniformLocation(Shader.ID,"offset");
        Shader.use();
        glUniform3f(vertexOff,off,0,0);
        int CB = glGetUniformLocation(Shader.ID,"changeBlue");
        glUniform3f(CB,0,0,Blue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}