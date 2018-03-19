//
//  main.c
//  OpenGL-Template
//
//  Created by Diaz, Christopher on 9/30/14.
//  Edited by Jacob Addis.
//  Copyright (c) 2014 Diaz, Christopher. All rights reserved.
//

#include <stdio.h>              // Input and output
#include <GL/glew.h>            // OpenGL Support
#include <GLFW/glfw3.h>         // OpenGL Support

int main(int argc, const char * argv[])
{
    // Initialize the glfw library
    if (!glfwInit())
    {
        fprintf(stderr,"Failed to init glfw!\n");
        return -1;
    }
    
    // Specify 16x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 16);
    
    // Specify preference of OpenGL 2.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    // Create and open a window of 600x600 pixels
    GLFWwindow *window = glfwCreateWindow(600, 600, "OpenGL Template", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr,"Failed to open a GLFW window!\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Init GLEW library
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr,"GLEW init failed\n");
        return -1;
    }
    
    // Set background to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    // Ensure we can capture the ESC key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glPointSize(4.0f);
        glLineWidth(4.0);
        
        // Draw purple points
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_QUADS);
            glVertex3f(-0.5f, -0.1f, +0.0f);
            glVertex3f(-0.4f, -0.2f, +0.0f);
            glVertex3f(-0.5f, -0.3f, +0.0f);
            glVertex3f(-0.6f, -0.2f, +0.0f);
        glEnd();
        
        // Draw blue points
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
            glVertex3f(+0.2f, -0.2f, +0.0f);
            glVertex3f(+0.4f, -0.2f, +0.0f);
            glVertex3f(+0.5f, -0.4f, +0.0f);
            glVertex3f(+0.3f, -0.6f, +0.0f);
            glVertex3f(+0.1f, -0.4f, +0.0f);
        glEnd();
        
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.7f, +0.5f, +0.0f);
            glVertex3f(-0.6f, +0.6f, +0.0f);
            glVertex3f(-0.8f, +0.6f, +0.0f);
        
            glVertex3f(-0.8f, +0.7f, +0.0f);
            glVertex3f(-0.6f, +0.7f, +0.0f);
            glVertex3f(-0.7f, +0.8f, +0.0f);
        glEnd();
        
        // Draw green points
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(-0.2f, +0.9f, +0.0f);
            glVertex3f(-0.3f, +0.8f, +0.0f);
            glVertex3f(-0.1f, +0.6f, +0.0f);
            glVertex3f(-0.3f, +0.4f, +0.0f);
            glVertex3f(-0.1f, +0.2f, +0.0f);
            glVertex3f(-0.3f, +0.0f, +0.0f);
            glVertex3f(-0.1f, -0.2f, +0.0f);
        glEnd();
        
        // Draw green points
        glColor3f(1.0, 0.0, 0.0);
        glRectf(0.7f, 0.6f, 0.9f, 0.8f);
        
        glRectf(0.4f, 0.0f, 0.9f, 0.1f);
        
        glfwSwapBuffers((window));
        
        glfwPollEvents();
    }
    // loop until ESC is pressed or the window is closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    
    return 0;
}

