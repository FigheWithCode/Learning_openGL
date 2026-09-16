#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

const char* vertexShaderSource="#version 330 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos,1.0);\n"
    "}\n";

const char* fragmentShaderSource="#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(1.0f,.5f,.2f,1.0f);\n"
    "}\n";

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window=glfwCreateWindow(800,800,"",NULL,NULL);

    if (window==NULL) {
        std::cout<<"Failed to create GLFW window."<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD."<<std::endl;
        glfwTerminate();
        return -1;
    }

    //line mode
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glViewport(0,0,800,800);

    //检查是否创建成功
    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout<<"Vertex Shader Compiled Failed "<<infoLog<<std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout<<"Fragment Shader Compiled Failed "<<infoLog<<std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram=glCreateProgram();

    //Link
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    //test
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout<<"Vertex Program Linking Failed "<<infoLog<<std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[]={
        -.5f,.5f,.0f,
        -1.0f,.0f,.0f,
        .0f,.0f,.0f,
        .5f,.5f,.5f,
        1.0f,.0f,.0f
    };

    unsigned int indices[]={
        0,1,2,
        2,3,4,
    };

    unsigned int VBO,VAO;
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(.4f,.4f,.5f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height) {
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose (window,true);
    }
}
