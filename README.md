<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/cub3de.png" alt="Cub3D 42 project badge"/>
</p>

# Cub3D Raycasting Game

## Description
Cub3D is a simple raycasting game project developed in C using the MinilibX graphics library. The project aims to recreate a 3D-like visual effect using 2D graphics and basic raycasting techniques. Players navigate through a maze-like environment and interact with textured walls.

## Getting Started
To run the game, you will need a UNIX-like operating system and the MinilibX graphics library.

## Clone the Repository
Clone the repository to your local machine using the following command:

```bash
git clone git@github.com:Splix777/cub3d.git
```
## Running the Game
After compilation, run the executable with the provided map file:
```bash
./cub3D maps/map.cub
```
## Controls
- W/A/S/D: Move forward/left/backward/right
- ←/→: Rotate the view left/right
- ESC: Exit the game

## Map Configuration
Maps are configured using a .cub file format. You can create your own maps using a text editor. Here's a basic example:
```bash
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 220,100,0
C 0,0,128

111111
100E01
111101
100001
111111
```
- NO, SO, WE, EA: Texture paths for north, south, west, and east walls.
- F: Floor color (RGB).
- C: Ceiling color (RGB).
- Map layout using numbers where 1 is a wall and 0 is an empty space.
- NSEW for player starting position and direction facing.

## Ressources

* [Playable Wolfenstein 3D](http://users.atw.hu/wolf3d/)
* [Raycasting in JS](http://www.playfuljs.com/a-first-person-engine-in-265-lines/)
* [Some X11 event numbers](https://github.com/qst0/ft_libgfx)
* [Full tutorial in English](https://lodev.org/cgtutor/raycasting.html)
* [Images in minilibx](https://github.com/keuhdall/images_example)
* [BMP format on StackOverflow](https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries)
* [BMP format explanation](https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html)
