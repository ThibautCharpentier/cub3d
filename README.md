# cub3d

cub3d is a 42 school team project where we have to create a 3D graphical representation of a maze using a first person view. We have to implement raycasting in the style of the famous [Wolfenstein 3D game](http://users.atw.hu/wolf3d/).

## Status

* Success
* Grade: 120/100

## Rules

We should display different wall textures depending on which compass point the wall is facing (North, South, East, West). Our program should be able to have different colors for the floor and the ceiling.

The program displays the image in a window and respects the following rules:
* The management of the window must remain smooth.
* The **W**, **A**, **S**, **D** (qwerty) or **Z**, **Q**, **S**, **D** (azerty) keys will be used to move the point of view in the maze.
* The **left and right arrows keys** should rotate the point of view in the maze.
* Pressing **ESC** must close the window and quit program cleanly.
* Clicking on the red cross on the window's frame must close the window and quit the program cleanly.

The program must take as a first argument a map description file with the **.cub** extension:
* The map must be composed of only six possible characters: **0** for an empty space, **1** for a wall and **N**, **S**, **E** or **W** for the player's starting position and cardinal orientation.
* The map must surrounded by walls.
* Spaces (**' '**) are a valid part of the map, we have to manage them. We should be able to parse any kind of map as long as it respects the map rules.
* Except for the map content, each type of element can be separated by one or more empty lines.
* Except for the map content which always have to be in last, each type of element can be set in any order in the file.
* Each type of information from an element can be separated by one or more spaces.
* For each element, the first information is the identifier composed by one or two characters, followed by all specific informations for each object in a strict order: for textures we have to specify the path and
for the floor or the ceiling we have to specify the RGB (0, 255) color. There are examples in the **map** folder.

### Bonus

* There are doors which can be opened or closed.
* A minimap is displayed on the screen.
* We are able to rotate the point of view with the mouse.

## Project content

This project contains a **libft** folder which is a library that we had to create as the first 42 school project. This folder also includes files corresponding to the following 42 school project: **ft_printf** and **get_next_line**.

The **libmlx** is the MiniLibX library. It is a tiny graphics library which allows us to do the most basic things for rendering something in screen. The **libmlx_mac** is the version for Mac OS.

There is also a **map** folder which contains **.cub** files we can use as a first argument for running the program.

## Usage

Before running the project, you have to set up your MinilibX. Here you will find everything you need to make the library work according to your OS: <https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#installation>.

If you use **libmlx**, make sure that the MinilibX works by running a test. Use ```make libmlx``` command to compile the library then run the test with:
```
./libmlx/test/run_tests.sh
```

If the test works, now pay attention to the following lines in the Makefile file:
```
INCLUDES_HOME = -Ilibft -I/usr/include -Ilibmlx
LIBS_HOME = -Llibft -lft -Llibmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz

INCLUDES_42 = -Ilibft -Ilibmlx_mac
LIBS_42 = -Llibft -lft -Llibmlx_mac -lmlx -framework OpenGL -framework AppKit
```
You must choose the right configuration according to the structure of your system and your OS (perhaps the two possible configurations above will not correspond). I recommend you to follow the link I wrote above.
If you use **libmlx**, the right ```-I/usr/*/include``` and ```-L/usr/*/lib``` should match with the first line ```INC=/usr/*/include``` of the ```libmlx/Makefile.gen``` file.

If everything looks correct, use ```make``` command to compile the project then run the program with:
```
./cub3d map/map.cub
```
or:
```
./cub3d map/map2.cub
```

To run the bonus part, use ```make bonus``` command and run the bonus program with:
```
./cub3d_bonus map/map_bonus.cub
```
or:
```
./cub3d_bonus map/map2_bonus.cub
```
In the ```map/map_bonus.ber``` and ```map/map2_bonus.ber``` files, doors are represented by the **2** character.

If you have a QWERTY keyboard you can change keys in ```srcs/cub3d.h``` and in ```srcs_bonus/cub3d_bonus.h```. You also can change the MOVESPEED or ROTSPEED parameters if your game is too slow or too fast.
***
Made by:
* Ismérie George: <ismerie.george@gmail.com>
* Thibaut Charpentier: <thibaut.charpentier42@gmail.com>
