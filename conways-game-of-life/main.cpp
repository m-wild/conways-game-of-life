///
///  main.cpp
///  conways-game-of-life
///
///  Created by Michael Wildman on 16/08/14.
///  Copyright (c) 2014 Michael Wildman. All rights reserved.
///


#include <iostream>
#include <SDL2/sdl.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGl/glu.h>


// Function stubs
bool init();
bool initGL();
void handleKeys(unsigned char key, GLint x, GLint y);
void update();
void render();
void close();

// Global variables
const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

const int boardWidth = WINDOW_WIDTH / 4.f;
const int boardHeight = WINDOW_HEIGHT / 4.f;

int board[boardWidth * boardHeight];

int globalCount = 0;

SDL_Window* sdlWindow = NULL;
SDL_GLContext sdlGlContext;

///
/// Main program entry point
///
int main(int argc, char* argv[])
{
    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        bool quit = false;  // Main loop flag
        SDL_Event e;        // Event handler
        
        SDL_StartTextInput();
        
        // Main loop
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                // Handle keypress with mouse position
                else if (e.type == SDL_TEXTINPUT)
                {
                    GLint x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    
                    handleKeys(e.text.text[0], x, y);
                }
            }
            
            // Update the game state
            update();
            
            // OpenGL render
            render();
            
            // Update the screen
            SDL_GL_SwapWindow(sdlWindow);

        }
        
        SDL_StopTextInput();
    }
    
    close();
    
    return 0;
}

///
/// Handle keypress with mouse position
///
void handleKeys(unsigned char key, GLint x, GLint y)
{
     // Keypress handling here!
}

///
/// Per frame game state update
///
void update()
{
    
    /*
     Any live cell with fewer than two live neighbours dies, as if caused by under-population.
     Any live cell with two or three live neighbours lives on to the next generation.
     Any live cell with more than three live neighbours dies, as if by overcrowding.
     Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     */
    
    
    for (int y = 0; y < boardHeight; y++)
    {
        for (int x = 0; x < boardWidth; x++)
        {
            board[(y * boardWidth) + x] = (globalCount + x + y) % 5;
        }
    }
    
    globalCount++;
    

}

///
/// OpenGL rendering
///
void render()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    
    glColor3f(0.0, 0.0, 0.0);
    
    glBegin(GL_POINTS);
    
    
    for (int y = 0; y < boardHeight; y++)
    {
        for (int x = 0; x < boardWidth; x++)
        {
            if (board[(y * boardWidth) + x] != 0)
            {
                glVertex2f((x * 4) + 2, (y * 4) + 2);
            }
        }
    }
    
    glEnd();
    
}

// Initialize everything
bool init()
{
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Use OpenGL2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        
        if ((sdlWindow = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            if ((sdlGlContext = SDL_GL_CreateContext(sdlWindow)) == NULL)
            {
                std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                // Use Vsync (allowed to fail)
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
                }
                
                if (!initGL())
                {
                    std::cout << "Unable to initialize OpenGL! SDL Error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    
    return success;
}

// Initialize OpenGL (Projection, ModelView, ClearColor)
bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;
    
    // Initialize gl projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    
    if ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "Error initializing OpenGL! " << std::endl << gluErrorString(error) << std::endl;
        success = false;
    }
    
    // Initialize Modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "Error initializing OpenGL! " << std::endl << gluErrorString(error) << std::endl;
        success = false;
    }
    
    // Set clear color
    glClearColor(1.f, 1.f, 1.f, 0.f);
    
    if ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "Error initializing OpenGL! " << std::endl << gluErrorString(error) << std::endl;
        success = false;
    }
    
    return success;
}

// Shutdown SDL
void close()
{
    SDL_DestroyWindow(sdlWindow);
    sdlWindow = NULL;
    
    SDL_Quit();
}

