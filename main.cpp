#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
const char *WIN_TITLE = "Solar System Prototype";

int main(){
    if (!glfwInit()){
        printf("GLFW FAILED!!");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // setting OPENGL versions: (MAJOR)3.3(MINOR)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // yes to forward compatibility

    //@TODO modularize those initialization functions

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, WIN_TITLE, NULL, NULL);

    if (!mainWindow){
        printf("WINDOWN FAILED!!");
        glfwTerminate();
        return 1;
    }

    int ndv, ndh; // size of addressable points, vertically and horizontally
    glfwGetFramebufferSize(mainWindow, &ndh, &ndv); // getting the recently created window frame buffer size

    glfwMakeContextCurrent(mainWindow); // set context for GLEW to use == saying which window I want my things to be drawn on
    glewExperimental = GL_TRUE; // allow modern extension features

    if (glewInit() != GLEW_OK){
        printf("GLEW FAILED!!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, ndh, ndv); // setting the viewport size, making the whole window a drawable area

    while(!glfwWindowShouldClose(mainWindow)){ // loop until window is closed
        glfwPollEvents(); // event listener and handler
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // clear | 0-1 notation, just divide by 256
        glClear(GL_COLOR_BUFFER_BIT); // what I want to clear in the buffer
        glfwSwapBuffers(mainWindow); // didnt get it.. theres what user can see and what we can draw...
    }

    return 0;
}