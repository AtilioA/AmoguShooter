# AmoguShooter
Simple side-scrolling game written in C++ OpenGL for Computer Graphics classes in 2021/2.
## Usage
### Prerequisites

Make sure you have FreeGLUT installed on your system:
- For Debian: [freeglut3](https://packages.debian.org/buster/freeglut3), [freeglut3-dev](https://packages.debian.org/buster/freeglut3-dev)
- For Arch: [freeglut](https://archlinux.org/packages/extra/x86_64/freeglut/), [glu](https://archlinux.org/packages/extra/x86_64/glu/)

The program was developed to be compatible with Linux, or, more specifically, with Ubuntu 20.04. Other platforms might not produce correct results or might not even work at all.

### Compiling
An executable can be obtained by calling [`make`](https://linux.die.net/man/1/make) within the project directory. `make help` will display information about relevant recipes from the Makefile.

### Executing
The program can receive up to 3 arguments, in this order:

1. `./trabalhocg`: the game executable;

2. `arena.svg`: path to the svg file with arena information;

3. `-d`: to enable debug mode (draws collision boxes, etc).

Example: `./trabalhocg input/arena_teste.svg -d`
