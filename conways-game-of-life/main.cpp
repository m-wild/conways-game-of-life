//
//  main.cpp
//  conways-game-of-life
//
//  Created by Michael Wildman on 16/08/14.
//  Copyright (c) 2014 Michael Wildman. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

// main drawing function
void display(void)
{
    
}

// initialize the view
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // white
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLdouble halfWidth = (GLdouble) WINDOW_WIDTH / 2.0;
    GLdouble halfHeight = (GLdouble) WINDOW_HEIGHT / 2.0;
    
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main program entry point
int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Conway's Game of Life");
    
    init(); // initialize the view
    
    glutDisplayFunc(display); // draw scene
    
    glutMainLoop();
    
    return 0;
}

