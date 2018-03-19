// I/O support
#include <stdio.h>
#include <stdlib.h>

// OpenGL GLEW support
#include <GL/glew.h>

// OpenGL GLFW support
#include <GLFW/glfw3.h>

// OpenGL GLM support
#include <glm/glm.hpp>

#include "shader.hpp"

int main(void) {
    
    // Window object pointer
    GLFWwindow *window;
    
    // Initialize the GLFW library
    if ( !glfwInit() )                  // equivalent to glfwInit() == 0
    {
        fprintf(stderr, "Failed to initialize GLFW!\n");
        getchar();
        exit(1);
    }
    
    // Set up anti-aliasing, OpenGL version, and OS assists
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window
    window = glfwCreateWindow(1024, 768, "Window Title", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window!\n");
        getchar();
        exit(1);
    }
    // Set the created window to the current context or focus
    glfwMakeContextCurrent(window);
    
    // Initialize the GLEW library
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW!\n");
        getchar();
        glfwTerminate();
        exit(1);
    }
    
    // Ensure we can capture the ESC key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Set a dark blue background in the window
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Create and setup the data structures to draw the objects (triangles in this case)
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // The vertice specifications
    static const GLfloat triangle_vertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        +1.0f, -1.0f, 0.0f,
         0.0f, +1.0f, 0.0f
    };
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(triangle_vertices),
                 triangle_vertices,
                 GL_STATIC_DRAW);
    
    // Load the shader that we will use for drawing
    GLuint programID = LoadShaders("SimpleVertexShader.vertexshader",
                                   "SimpleFragmentShader.fragmentshader");
    
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use the loaded shader to draw
        glUseProgram(programID);
        // Draw the objects (triangles)
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0,
                              3,            // size
                              GL_FLOAT,     // data type of vertices
                              GL_FALSE,     // not normalized
                              0,            // stride
                              (void *)0     // array buffer offset
                              );
        glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 vertices starting at 0
        glDisableVertexAttribArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        
        // Check for events
        glfwPollEvents();
    }
    // loop until ESC is pressed or the window is closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    
    // Cleanup data structures we had used for drawing
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    
    // Close the window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
