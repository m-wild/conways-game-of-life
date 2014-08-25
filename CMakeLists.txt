cmake_minimum_required (VERSION 2.8)

set(MacOSX-SDKs /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks)
set(Windows-SDKs C:/Program\ Files\ \(x86\)/Microsoft\ SDKs/Windows/v7.1A/Lib)

project (conways-game-of-life)

add_executable(conways-game-of-life conways-game-of-life/main.cpp)

if (APPLE)
	target_link_libraries(conways-game-of-life ${MacOSX-SDKs}/OpenGL.framework)
endif()

if (WIN32)
	include_directories(C:/usr/local/SDL2/2.0.3/include)

	target_link_libraries(conways-game-of-life ${Windows-SDKs}/OpenGL32.Lib)
	target_link_libraries(conways-game-of-life ${Windows-SDKs}/GlU32.Lib)
	target_link_libraries(conways-game-of-life C:/usr/local/SDL2/2.0.3/lib/x86/SDL2.lib)
endif()