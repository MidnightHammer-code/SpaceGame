# SpaceGame
A simple space shooter made in 48 hours in SDL2 and C++

# How to build?

1. Install the dependencies:
`sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-image-dev libsdl2-ttf-dev`

2. Create and go in the build folder:
`mkdir build && cd build`

3. Build the source using CMake and Make using all available cores:
`cmake .. && make -j(nproc)`

4. Move the binary to main folder and go to the main folder:
`mv SpaceGame .. && cd ..`

5. Run the game:
`./SpaceGame`

6. Enjoy
