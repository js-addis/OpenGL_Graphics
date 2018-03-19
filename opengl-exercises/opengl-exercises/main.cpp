//
//  main.cpp
//  opengl-exercises-solutions
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
    
    // The vertice specifications
    // Task 1: Draw a red triangle in the lower right corner
    /* static const GLfloat vertices[] =
     {
     +0.8f, -0.9f, 0.0f,
     +0.9f, -0.7f, 0.0f,
     +0.7f, -0.7f, 0.0f
     }; */
    
    // Task 2: Draw two red triangles, one from task 1, and the other
    // in the upper right corner pointing upwards
    /* static const GLfloat vertices[] =
     {
     +0.8f, -0.9f, 0.0f,
     +0.9f, -0.7f, 0.0f,
     +0.7f, -0.7f, 0.0f,
     +0.8f, +0.9f, 0.0f,
     +0.7f, +0.7f, 0.0f,
     +0.9f, +0.7f, 0.0f
     }; */
    
    // Task 3: Add to task 2 with two green triangles mirrored on
    // the Y-axis
    /* static const GLfloat vertices[] =
     {
     +0.8f, -0.9f, 0.0f,         // lower right triangle
     +0.9f, -0.7f, 0.0f,
     +0.7f, -0.7f, 0.0f,
     
     +0.8f, +0.9f, 0.0f,         // upper right triangle
     +0.7f, +0.7f, 0.0f,
     +0.9f, +0.7f, 0.0f,
     
     -0.8f, -0.9f, 0.0f,         // lower left triangle
     -0.7f, -0.7f, 0.0f,
     -0.9f, -0.7f, 0.0f,
     
     -0.8f, +0.9f, 0.0f,         // upper left triangle
     -0.9f, +0.7f, 0.0f,
     -0.7f, +0.7f, 0.0f
     }; */
    
    // Task 4: Draw a red house with green roof
    /* static const GLfloat vertices[] =
     {
     +0.0f, +0.6f, 0.0f,         // roof
     -0.5f, +0.2f, 0.0f,
     +0.5f, +0.2f, 0.0f,
     
     -0.1f, -0.1f, 0.0f,         // house
     +0.1f, -0.1f, 0.0f,
     +0.1f, +0.2f, 0.0f,
     -0.1f, +0.2f, 0.0f
     }; */
    
    // Task 5: Draw a pentagon
    /* static const GLfloat vertices[] =
     {
     +0.0f, +0.5f, +0.0f,
     -0.4f, +0.1f, +0.0f,
     -0.2f, -0.5f, +0.0f,
     +0.2f, -0.5f, +0.0f,
     +0.4f, +0.1f, +0.0f,
     +0.0f, +0.5f, +0.0f,
     -0.4f, +0.1f, +0.0f
     };
     */
    
    // Task 6: Draw 10 red rectangles across the X-axis
    const int NRECTANGLES = 10;
    const int VERTICES_PER_RECT = 4;
    static GLfloat vertices[NRECTANGLES * VERTICES_PER_RECT * 3];
    int i;
    GLfloat YHI = 0.2f, YLO = -0.2f;
    GLfloat x = -1.0f;                      // left side of 1st rectangle
    GLfloat space = 0.1;
    GLfloat width = (2.0 - space*NRECTANGLES) / NRECTANGLES;
    int o = 0;                              // Index offset for next rectangle
    printf("width is %f\n",width);
    
    
    for (i=0; i<NRECTANGLES; i++)
    {
        vertices[o+0] = x;        vertices[o+1] = YHI;   vertices[o+2] = 0.0f;    // Top left
        vertices[o+3] = x;        vertices[o+4] = YLO;   vertices[o+5] = 0.0f;    // Bottom left
        vertices[o+6] = x+width;  vertices[o+7] = YLO;   vertices[o+8] = 0.0f;    // Bottom right
        vertices[o+9] = x+width;  vertices[o+10] = YHI;  vertices[o+11] = 0.0f;   // Top right
        
        // Increase the index offset variable o to the starting index of the next rectangle
        o = o + VERTICES_PER_RECT * 3;
        // Increase the x value to that of the left side of the next rectangle
        x = x + width + space;
    }
    
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices),
                 vertices,
                 GL_STATIC_DRAW);
    
    // Load the shader that we will use for drawing
    GLuint redID = LoadShaders("SimpleVertexShader.vertexshader",
                               "SimpleFragmentShader.fragmentshader");
    GLuint greenID = LoadShaders("SimpleVertexShader.vertexshader",
                                 "green.fragmentshader");
    
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use the loaded shader to draw
        glUseProgram(redID);
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
        
        // glDrawArrays function calls goes here
        // Task 1: Draw a red triangle in the lower right display
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // Task 2: Draw two red triangles, one from task 1, and
        // the second at the top right of the display
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Task 3: Add to task 2 with two green triangles mirrored on
        // the Y-axis
        /* glDrawArrays(GL_TRIANGLES, 0, 6);
         glUseProgram(greenID);
         glDrawArrays(GL_TRIANGLES, 6, 6); */
        
        // Task 4: Draw a red house with green roof
        /* glUseProgram(greenID);
         glDrawArrays(GL_TRIANGLES, 0, 3);
         glUseProgram(redID);
         glDrawArrays(GL_TRIANGLE_FAN, 3, 4);
         */
        
        // Task 5: Draw a pentagon
        /* glUseProgram(redID);
         glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
         */
        
        // Task 6: Draw 10 red rectangles across the X-axis
        glUseProgram(redID);
        for (i=0; i<NRECTANGLES; i++)
        {
            glDrawArrays(GL_LINE_LOOP, i*VERTICES_PER_RECT, VERTICES_PER_RECT);
        }
        
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
    glDeleteProgram(redID);
    glDeleteProgram(greenID);
    
    // Close the window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
