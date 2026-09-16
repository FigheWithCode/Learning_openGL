#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<cmath>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char* vertexShaderSource="#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    // "out vec4 vertexColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos,1.0);\n"
    // "   vertexColor = vec4(0.5,0.0,0.3,1.0);\n"
    "}\n";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragmentColor;\n"
    // "in vec4 vertexColor;\n"
    "uniform vec4 ourColor;\n"
    "void main() {\n"
    // "   fragmentColor=vertexColor;\n"
    "   fragmentColor=ourColor;\n"
    "}\n";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "__FILE__", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initiate GLAD"<<std::endl;
        return -1;
    }
    glViewport(0,0,800, 800);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    char infoLog[512];
    int success;

    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout<<"Failed to compile vertex shader"<<std::endl;
        std::cout<<infoLog<<std::endl;
        return -1;
    }

    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout<<"Failed to compile fragment shader"<<std::endl;
        std::cout<<infoLog<<std::endl;
        return -1;
    }

    unsigned int program=glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(program,512,NULL,infoLog);
        std::cout<<"Failed to link program"<<std::endl;
        std::cout<<infoLog<<std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[]={
        -1.f,-1.f,1.f,
        0.f,1.f,1.f,
        1.f,-1.f,1.f,
    };

    unsigned int VAO,VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.3f,0.5f,0.6f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue=glfwGetTime();
        float greenValue=(std::sin(timeValue)/2.0f)+0.5f;
        int vertexColorLocation = glGetUniformLocation(program,"ourColor");
        glUseProgram(program);
        glUniform4f(vertexColorLocation,.0f,greenValue,.0f,1.0f);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (GLFW_PRESS==glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}