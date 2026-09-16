#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\n";

const char* fragmentShaderSource="#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
    "}\n";
const char* fragmentShaderSource_1="#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(1.0,0.5,0.0,1.0);\n"
    "}\n";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window=glfwCreateWindow(800,800,"",NULL,NULL);
    if (window==NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialized GLAD" << std::endl;
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
    if (!success) {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "Failed to compile vertex shader" << std::endl;
        std::cout << infoLog << std::endl;
    }

    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "Failed to compile fragment shader" << std::endl;
        std::cout << infoLog << std::endl;
    }

    unsigned int fragmentShader_1=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_1,1,&fragmentShaderSource_1,NULL);
    glCompileShader(fragmentShader_1);
    glGetShaderiv(fragmentShader_1,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader_1,512,NULL,infoLog);
        std::cout << infoLog << std::endl;
    }

    unsigned int Program=glCreateProgram();
    glAttachShader(Program,vertexShader);
    glAttachShader(Program,fragmentShader);
    glLinkProgram(Program);

    glGetProgramiv(Program,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(Program,512,NULL,infoLog);
        std::cout << "Failed to link program" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(fragmentShader);

    unsigned int Program_1=glCreateProgram();
    glAttachShader(Program_1,vertexShader);
    glAttachShader(Program_1,fragmentShader_1);
    glLinkProgram(Program_1);

    glGetProgramiv(Program_1,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(Program_1,512,NULL,infoLog);
        std::cout << "Failed to link program2" << std::endl;
        std::cout << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader_1);

    float vertices_0[]={
        -.5f,1.f,.0f,
        -1.f,-1.f,.0f,
        .0f,-1.f,.0f
    };

    float vertices_1[]={
        .5f,1.f,.0f,
        .5f,-1.f,.0f,
        1.f,1.f,.0f
    };

    unsigned int VAOS[2];
    unsigned int VBOS[2];
    glGenBuffers(2,VBOS);
    glGenVertexArrays(2,VAOS);

    glBindBuffer(GL_ARRAY_BUFFER,VBOS[0]);
    glBindVertexArray(VAOS[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_0),vertices_0,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,VBOS[1]);
    glBindVertexArray(VAOS[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_1),vertices_1,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(.3,0.0,0.5f,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        glUseProgram(Program);
        glBindVertexArray(VAOS[0]);
        glDrawArrays(GL_TRIANGLES,0,3);

        glUseProgram(Program_1);
        glBindVertexArray(VAOS[1]);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(2,VBOS);
    glDeleteVertexArrays(2,VAOS);
    glDeleteProgram(Program);
    glDeleteProgram(Program_1);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}