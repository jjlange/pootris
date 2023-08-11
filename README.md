# Pootris
## Prerequisites for macOS

1. Install command line tools `xcode-select --install`
 - Refer to <https://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/>

2. Install brew `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
 - Refer to <https://brew.sh/>

3. Install CMake `brew install cmake` 
 - Run `cmake --version` to confirm that CMake works from commmand line, if not:
 - Make sure `/usr/local/bin` is in your `PATH`
`echo $PATH` should contain `/usr/local/bin`
 - Refer to <https://stackoverflow.com/questions/32185079/installing-cmake-with-home-brew>

5. Download and install VSCode
 - <https://code.visualstudio.com/>
 - Install the C/C++ extension for VS Code. You can install the C/C++ extension by searching for 'c++' in the Extensions view (⇧⌘X).
  - (Optional) Install CMake language support <https://marketplace.visualstudio.com/items?itemName=twxs.cmake>

# How to build?
1. Clone project or download zip-file and unzip it
2. Open terminal inside of the project
3. `mkdir build` -  to make "build" directory inside of project folder
4. `cd ./build` - go inside of "build" folder
5. `cmake ..` - to link files (On Windows use command `cmake .. -G "MinGW Makefiles` if you followed windows prerequisites guide)
6. `make` - to build project (On Windows use command `mingw32-make.exe` if you followed windows prerequisites guide)
7. `./a` - to display output


# 3rd party libraries

## SFML
- SFML: SFML is a simple, fast, cross-platform and object-oriented multimedia API
- <https://github.com/SFML/SFML>

## Dear ImGui
- ImGui: Dear ImGui is a bloat-free graphical user interface library for C++.
- <https://github.com/ocornut/imgui>

## ImGui-SFML binding
- ImGui-SFML: Library which allows you to use Dear ImGui with SFML binding 
- <https://github.com/eliasdaler/imgui-sfml>