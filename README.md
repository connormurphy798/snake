# Snake
My first attempt to write a game in C++ using SDL2. Currently fully playable.

Credit to [codergopher's](https://github.com/codergopher/2D-RPG-Platformer-Cplusplus-SDL2) tutorial for the basic setup and structure.

## Setup

Compiling and playing Snake on Windows requires the following dependencies:
* mingw-w64
* SDL2
* SDL2_image

To compile, run the following:

```
g++ -c src/*.cpp -std=c++14 -O3 -m64 -I include -I C:/SDL2-w64/include && g++ *.o -o bin/release/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows && start bin/release/main
```

To play, simply run:

```
start bin/release/main
```
