#define GLEW_STATIC

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    GLFWwindow* window;
    
    if(!glfwInit()) {
        cout << "GLFW failed to initalise!\n";
        return -1;
    }

    
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if(!window) {
        glfwTerminate();
        cout << "Window failed to open!\n";
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
            cout << "fuck glew\n";
            return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

            float positions[9] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    uint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window*/
    while(!glfwWindowShouldClose(window)) {
        
        /* Render Here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events*/
        glfwPollEvents();
    }
    
    glfwTerminate();

    return EXIT_SUCCESS;
}
