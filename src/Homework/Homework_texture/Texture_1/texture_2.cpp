#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#include"Texture_2.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}

void ProcIn(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}

static float value = 0;
void Texture_uper(Texture_2 &textures,GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_UP) && value<=1) {
        textures.SetFloat("TexOffset",value+=.01);
    }
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_DOWN) && value>=0) {
        textures.SetFloat("TexOffset",value-=.01);
    }
}
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"",NULL,NULL);
    if (window == NULL) {
        std::cout<<"window create false"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"glad load false"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,800,800);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 左上
    };
    unsigned int indices[]={
        0,1,3,
        1,2,3,
    };

    unsigned int VAO,VBO,EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    Texture_2 texture("/home/Gal/Projects/learnopengl/src/Homework/Homework_texture/Texture_1/vertex","/home/Gal/Projects/learnopengl/src/Homework/Homework_texture/Texture_1/fragment");

    stbi_set_flip_vertically_on_load(true);
    unsigned int textures[2];
    glGenTextures(2,textures);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textures[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    //加载和生成纹理
    int width,height,nrChannels;
    unsigned char* data = stbi_load("/home/Gal/Projects/textures_Pictures/wall.jpg",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout<<"texture image load false"<<std::endl;
        return -1;
    }

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textures[1]);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    data = stbi_load("/home/Gal/Projects/textures_Pictures/awesomeface.png",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout<<"texture1 image load false"<<std::endl;
        return -1;
    }

    stbi_image_free(data);
    texture.use();
    texture.setInt("texture1",0);
    texture.setInt("texture2",1);

    while (!glfwWindowShouldClose(window)) {
        ProcIn(window);
        glClearColor(1.f,.4f,.6f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.use();
        Texture_uper(texture,window);
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,textures[1]);

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(2, textures);
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(texture.ID);
    glDeleteVertexArrays(1,&VAO);
    glfwTerminate();
}