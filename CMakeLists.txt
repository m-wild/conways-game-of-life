cmake_minimum_required (VERSION 2.8)

set(MacOSX-SDKs /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks)

project (conways-game-of-life)

add_executable(conways-game-of-life conways-game-of-life/main.cpp)

target_link_libraries(conways-game-of-life ${MacOSX-SDKs}/OpenGL.framework)

target_link_libraries(conways-game-of-life ${MacOSX-SDKs}/GLUT.framework)
