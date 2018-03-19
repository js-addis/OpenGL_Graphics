//
//  main.cpp
//  opengl-exam1
//
//  Created by Diaz, Christopher on 1/24/18.
//  Copyright © 2018 Diaz, Christopher. All rights reserved.
//

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
    
    // I accidentally overwrote the first problem, don't have time to re-do it.
    
    // Octagon
    /*
    static const GLfloat vertices[] =
    {
        +0.0f, +0.5f, +0.0f,
        -0.25f, +0.25f, 0.0f,
        -0.4f, +0.0f, +0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.0f, -0.5f, +0.0f,
        +0.25f, -0.25f, 0.0f,
        +0.4f, +0.0f, +0.0f,
        +0.25f, +0.25f, 0.0f
        
    };
    */
    /*
    static const GLfloat vertices[] =
    {
        -0.9f, +0.9f, 0.0f,
        -0.9f, +0.7f, 0.0f,
        -0.7f, +0.7f, 0.0f,
        -0.7f, +0.9f, 0.0f,
        
        +0.9f, +0.9f, 0.0f,
        +0.9f, +0.7f, 0.0f,
        +0.7f, +0.7f, 0.0f,
        +0.7f, +0.9f, 0.0f,
        
        -0.9f, -0.9f, 0.0f,
        -0.9f, -0.7f, 0.0f,
        -0.7f, -0.7f, 0.0f,
        -0.7f, -0.9f, 0.0f,
        
        +0.9f, -0.9f, 0.0f,
        +0.9f, -0.7f, 0.0f,
        +0.7f, -0.7f, 0.0f,
        +0.7f, -0.9f, 0.0f,
    };
     */
    
    
    // 20 Lines
    GLfloat xUpper = -0.9f;
    GLfloat yUpper = -0.9f;
    GLfloat zUpper = 0.0f;
    GLfloat xLower = +0.9f;
    GLfloat yLower = -0.9f;
    GLfloat zLower = 0.0f;
    GLfloat vertices[20];
    int o = 0;
    int i;
    GLfloat space = 0.1;
    for (i=0; i<20; i++)
    {
        vertices[o + 0] = xUpper;
        vertices[o + 1] = yUpper;
        vertices[o + 2] = zUpper;
        
        vertices[o + 3] = xLower;
        vertices[o + 4] = xUpper;
        vertices[o + 5] = zUpper;
        
        o = o + 5;
        xUpper = xUpper + space;
        yUpper = yUpper + space;
        zUpper = zUpper + space;
        
        xLower = xLower + space;
        yLower = yLower + space;
        zLower = zLower + space;
    }
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices),
                 vertices,
                 GL_STATIC_DRAW);
    
    // Load the shaders that we will use for drawing
    GLuint redShaderID = LoadShaders("SimpleVertexShader.vertexshader",
                                     "red.fragmentshader");
    GLuint greyShaderID = LoadShaders("SimpleVertexShader.vertexshader",
                                      "grey.fragmentshader");
    GLuint purpleShaderID = LoadShaders("SimpleVertexShader.vertexshader",
                                        "purple.fragmentshader");
    GLuint whiteShaderID = LoadShaders("SimpleVertexShader.vertexshader",
                                       "white.fragmentshader");
    GLuint yellowShaderID = LoadShaders("SimpleVertexShader.vertexshader",
                                        "yellow.fragmentshader");
    
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use the loaded shader to draw
        
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
        
        // glUseProgram(yellowShaderID);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 8); - FOR OCTAGON
        
        // 4 SQUARES
        /*
        glUseProgram(whiteShaderID);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
        glUseProgram(yellowShaderID);
        glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
         */
        // 20 Lines
        for(i=0; i<20; i++) {
            glDrawArrays(GL_LINE_LOOP, i + 2, 2);
        }
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
    glDeleteProgram(redShaderID);
    glDeleteProgram(greyShaderID);
    glDeleteProgram(purpleShaderID);
    glDeleteProgram(yellowShaderID);
    glDeleteProgram(whiteShaderID);
    
    // Close the window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
