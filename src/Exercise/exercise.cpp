#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

void frambuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow* window);
int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window_0=glfwCreateWindow(800,800,"",NULL,NULL);
    GLFWwindow *window_1=glfwCreateWindow(800,800,"",NULL,NULL);

    if (window_0==NULL || window_1==NULL) {
        std::cout<<"Failed ti Create a window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window_0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed ti initializa glad"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800);

    glfwMakeContextCurrent(window_1);
    glViewport(0,0,800,800);

    glfwSetFramebufferSizeCallback(window_0,&frambuffer_size_callback);
    glfwSetFramebufferSizeCallback(window_1,&frambuffer_size_callback);

    while (window_0!=NULL || window_1!=NULL) {
        if (window_0!=NULL) {

            glfwMakeContextCurrent(window_0);
            processInput(window_0);

            glClearColor(0.8f,0.0f,.5f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //让窗口显现出来，交换颜色缓冲
            glfwSwapBuffers(window_0);

            if (glfwWindowShouldClose(window_0)) {
                glfwDestroyWindow(window_0);
                window_0=NULL;
            }
        }
        if (window_1!=NULL) {

            glfwMakeContextCurrent(window_1);
            processInput(window_1);

            glClearColor(0.8f,0.6f,.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //让窗口显现出来，交换颜色缓冲
            glfwSwapBuffers(window_1);

            if (glfwWindowShouldClose(window_1)) {
                glfwDestroyWindow(window_1);
                window_1=NULL;
            }
        }
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void frambuffer_size_callback(GLFWwindow* window,int width,int height) {
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
}
