#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include"Shader.h"
#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}
void ProcIn(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"",NULL,NULL);
    if (window == NULL) {
        std::cout<<"Window failed created"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,800,800);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices[]={
        /*  ==顶点==             ==texturecoirdinate==*/
         -.5f,.5f,1.f,             .48f,.52f,   //左上
          .5f,.5f,1.f,             .52f,.52f,   //右上
        -.5f,-.5f,1.f,             .48f,.48f,   //左下
         .5f,-.5f,1.f,             .52f,.48f,   //右下
    };
    unsigned int indices[]={
        0,1,2,
        1,2,3
    };

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("/home/Gal/Projects/learnopengl/src/Homework/Homework_texture/texture_2/vertex","/home/Gal/Projects/learnopengl/src/Homework/Homework_texture/texture_2/fragment");

    stbi_set_flip_vertically_on_load(true);
    unsigned int textures[2];
    glGenTextures(2, textures);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textures[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    int width,height,nrChannels;
    unsigned char* data=stbi_load("/home/Gal/Projects/textures_Pictures/wall.jpg",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout<<"Failed to load texture"<<std::endl;
        glfwTerminate();
        return -1;
    }

    stbi_image_free(data);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textures[1]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    data=stbi_load("/home/Gal/Projects/textures_Pictures/awesomeface.png",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout<<"Failed to load texture"<<std::endl;
        glfwTerminate();
        return -1;
    }

    stbi_image_free(data);
    shader.Use();
    shader.setInt("texture1",0);
    shader.setInt("texture2",1);

    while (!glfwWindowShouldClose(window)) {
        ProcIn(window);

        glClearColor(0.3f,.6f,.9f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,textures[1]);

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}