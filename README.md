## Conway's Game of Life

Built in C++ with SDL2 and OpenGL 2.1

[Conway's Game of Life - Wikipedia](http://en.wikipedia.org/wiki/Conway's_Game_of_Life)

### Controls
- `r` toggle the game running/stopped
- `s` seed a (semi) random board
- `c` clear the board
- `=` increase speed
- `-` decrease speed


### Dependencies
- OpenGL 2.1
- SDL2


### Build instructions
- Modify `CMakeLists.txt` to point to your OpenGL and SDL libraries
- run `CMake .`
- On windows run `MSBuild conways-game-of-life.vcxproj /p:Configuration=Release`
	- then copy `SDL2.dll` to the `Release` folder
- On mac run with xcode should work :)
