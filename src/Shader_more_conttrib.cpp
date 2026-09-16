#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void procInput(GLFWwindow* window);

const char* vertexShaderSource=
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos,1.0);\n"
    "   ourColor = aColor;\n"
    "}\n";

const char* fragmentShaderSource=
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main(){\n"
    "   FragColor = vec4(ourColor,1.0);\n"
    "}\n";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800l,800,"",NULL,NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initializ GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    char infoLog[512];
    int success;

    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    // if (!success) {
    //     glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    //     std::cout << "Failed to compile vertex shader" << std::endl;
    //     std::cout << infoLog << std::endl;
    //     return -1;
    // }

    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    // glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    // if (!success) {
    //     glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    //     std::cout<<"fragment shader info log:"<<infoLog<<std::endl;
    //
    //     return -1;
    // }

    unsigned int program=glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[]={
        .5f,-.5f,.0f, 1.f,.0f,.0f,  //position and color
        -.5f,-.5f,.0f, .0f,1.f,.0f,
        .0f,.5f,.0f, .0f,.0f,1.f,
    };


    unsigned int VAO,VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        procInput(window);

        glClearColor(.3f,.2f,.6f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
}

void procInput(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}