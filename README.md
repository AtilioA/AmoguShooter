# AmoguShooter
Simple side-scrolling game written in C++ OpenGL for Computer Graphics classes in 2021/2.
# Usage

The program was developed to be compatible with Linux, or, more specifically, with Ubuntu 20.04. Other platforms might not produce correct results or might not even work at all.

An executable can be obtained by calling [`make`](https://linux.die.net/man/1/make) within the project directory. The program can receive up to 3 arguments, in this order:

1. `./trabalhocg`: the game executable;

2. `arena.svg`: the input svg file for reading arena information;

3. `-d`: to enable debug mode (draws collision boxes, etc).

Example: `./trabalhocg input/arena_teste.svg -d`
