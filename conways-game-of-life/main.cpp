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

/*
Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overcrowding.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

int count = 0;

// main drawing function
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    
    glColor3f(0.0, 0.0, 0.0);
    
    glBegin(GL_POINTS);
    
    glVertex2f(0.0, 0.0);
    
    glVertex2f(10.0, count);
    
    glEnd();
   
    glFlush();
}

// main game loop
void animate(void)
{
    count++;
    
    glutPostRedisplay();
}


// initialize the view
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
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
    glutIdleFunc(animate);  // move the game
    
    glutMainLoop();
    
    return 0;
}

