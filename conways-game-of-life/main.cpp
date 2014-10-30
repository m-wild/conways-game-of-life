///
///  main.cpp
///  conways-game-of-life
///
///  Created by Michael Wildman on 16/08/14.
///  Copyright (c) 2014 Michael Wildman. All rights reserved.
///

#ifdef _WIN32
#include <Windows.h>
#include <SDL2/sdl.h>
#undef main
#include <Gl/glu.h>
#else
#include <SDL2/SDL.h>
#include <OpenGL/glu.h>
#endif //_WIN32


#include <iostream>
#include <SDL2/SDL_opengl.h>



// Function stubs
bool init();
bool initGL();
void handleKeys(unsigned char key, int x, int y);
void handleMouse(int x, int y);
void seedRandomBoard();
void update();
void render();
void close();

// Global variables
const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

const int boardWidth = WINDOW_WIDTH / 4.f;
const int boardHeight = WINDOW_HEIGHT / 4.f;

int board[boardWidth * boardHeight];
int boardBuffer[boardWidth * boardHeight];

bool simulationRunning = false;
int simulationPeriod = 20; // number of frames per update
int currentPeriod = 0;

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
        
        // Main game loop
        while (!quit)
        {
            // Handle events and update the game state
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_TEXTINPUT)
                {
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    
                    handleKeys(e.text.text[0], x, y);
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    
                    handleMouse(x, y);
                }
                
            }
            update();
            
            // GL render and swap buffers
            render();
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
void handleKeys(unsigned char key, int x, int y)
{
    // start/stop running
	if (key == 'r')
    {
        simulationRunning = !simulationRunning;
    }
	// clear the board
	else if (key == 'c')
	{
		for (int i = 0; i < boardWidth * boardHeight; i++)
		{
			board[i] = 0;
		}
	}
	// adjust simulation period
	else if (key == '=')
	{
		simulationPeriod -= 2;
		if (simulationPeriod < 1)
		{
			simulationPeriod = 1;
		}
	}
	else if (key == '-')
	{
		simulationPeriod += 2;
	}
    else if (key == 's')
    {
        seedRandomBoard();
    }
}

///
/// Handle mouse event
///
void handleMouse(int x, int y)
{
    x = ((WINDOW_WIDTH + x) / 4);
    y = ((WINDOW_HEIGHT - y) / 4) - 1;
    
	if (board[(y * boardWidth) + x] == 0)
	{
		board[(y * boardWidth) + x] = 1;
	}
	else
	{
		board[(y * boardWidth) + x] = 0;
	}
}

//
// Seed a random game board
void seedRandomBoard()
{
    srand((uint) time(NULL));
    
    for (int y = 1; y < boardHeight - 1; y++)
    {
        for (int x = 1; x < boardWidth - 1; x++)
        {
            board[(y * boardWidth) + x] = rand() % 2;
        }
    }
}

///
/// Per frame game state update
///
void update()
{
    if (simulationRunning)
    {
		if ((currentPeriod % simulationPeriod) == 0)
		{
			currentPeriod = 1;
			
			// 0 = dead
			// 1 = alive
			for (int y = 1; y < boardHeight - 1; y++)
			{
				for (int x = 1; x < boardWidth - 1; x++)
				{
					int numNeighbors = board[((y - 1) * boardWidth) + x - 1]
						+ board[((y - 1) * boardWidth) + x]
						+ board[((y - 1) * boardWidth) + x + 1]
						+ board[(y * boardWidth) + x - 1]
						+ board[(y * boardWidth) + x + 1]
						+ board[((y + 1) * boardWidth) + x - 1]
						+ board[((y + 1) * boardWidth) + x]
						+ board[((y + 1) * boardWidth) + x + 1];
				
					// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
					if ((board[(y * boardWidth) + x] == 0) && (numNeighbors == 3))
					{
						boardBuffer[(y * boardWidth) + x] = 1;
					}
					// Any live cell... 
					else if (board[(y * boardWidth) + x] == 1)
					{
						// ... with fewer than two live neighbours dies, as if caused by under-population.
						// ... with more than three live neighbours dies, as if by overcrowding.
						if ((numNeighbors < 2) || (numNeighbors > 3))
						{
							boardBuffer[(y * boardWidth) + x] = 0;
						}
						// ... with two or three live neighbours lives on to the next generation.
						else if ((numNeighbors == 2) || (numNeighbors == 3))
						{
							boardBuffer[(y * boardWidth) + x] = 1;
						}
					}
				}
			}
			
			// swap buffers
			for (int i = 0; i < boardWidth * boardHeight; i++)
			{
				board[i] = boardBuffer[i];
			}
		}
		else
		{
			currentPeriod++;
		}
    }
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
    
    
    for (int y = 1; y < boardHeight - 1; y++)
    {
        for (int x = 1; x < boardWidth - 1; x++)
        {
            if (board[(y * boardWidth) + x] != 0)
            {
                glVertex2f((x * 4) + 2, (y * 4) + 2);
            }
        }
    }
    
    glEnd();
    
}

//
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
        
        if ((sdlWindow = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)) == NULL)
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

//
// Initialize OpenGL (Projection, ModelView, ClearColor)
bool initGL()
{
    // Initialize gl projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.f, 1.f);
    
    // Initialize Modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set clear color
    glClearColor(1.f, 1.f, 1.f, 0.f);
    
    if (glGetError() != GL_NO_ERROR)
    {
        std::cout << "Error initializing OpenGL! GL Error: " << glGetError() << std::endl;
        return false;
    }
    
    return true;
}

//
// Shutdown SDL
void close()
{
    SDL_DestroyWindow(sdlWindow);
    sdlWindow = NULL;
    
    SDL_Quit();
}

