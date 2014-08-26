cmake_minimum_required (VERSION 3.0)

## ----- Set variables here!
# OSX
set(MacOSX-SDKs /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks)
set(SDL2-OSX /usr/local/Cellar/sdl2/2.0.3)
# Windows
set(Windows-SDKs C:/Program\ Files\ \(x86\)/Microsoft\ SDKs/Windows/v7.1A/Lib)
set(SDL2-Win C:/usr/local/SDL2/2.0.3)


## ----- Shouldn't need to edit anything below here
project (conways-game-of-life)

add_executable(conways-game-of-life conways-game-of-life/main.cpp)

if (APPLE)
	include_directories(${SDL2-OSX}/include)

	target_link_libraries(conways-game-of-life ${MacOSX-SDKs}/OpenGL.framework)
	target_link_libraries(conways-game-of-life ${SDL2-OSX}/lib/libSDL2.dylib)
endif()

if (WIN32)
	include_directories(${SDL2-Win}/include)

	target_link_libraries(conways-game-of-life ${Windows-SDKs}/OpenGL32.Lib)
	target_link_libraries(conways-game-of-life ${Windows-SDKs}/GlU32.Lib)
	target_link_libraries(conways-game-of-life ${SDL2-Win}/lib/x86/SDL2.lib)
endif()