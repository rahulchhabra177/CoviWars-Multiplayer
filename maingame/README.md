# Welcome to CoviWars!
This readme will guide you through the process of installation of dependencies for the game and for running the game for both single-player and multiplayer modes.


# **Requirements**
Our game uses the SDL library (v2) to run and therefore you need to install various SDL modules before playing the game. On Linux distributions, these libraries can be installed by:

 - To install SDL2 (main framework),
	 `sudo apt install libsdl2-dev libsdl2-2.0-0`
- To install SDL image (for 2D graphics),
	`sudo apt install libsdl2-image-dev libsdl2-image-2.0-0`
- To install SDL-mixer (for music and sound effects)
	`sudo apt install libsdl2-mixer-dev libsdl2-mixer-2.0-0`
- To install SDL-net (for sockets, used for multiplayer)
	`sudo apt install libsdl2-net-dev libsdl2-net-2.0-0`
- To install SDL-ttf (true-type fonts for rendering text)
	`sudo apt install libsdl2-ttf-dev libsdl2-ttf-2.0-0`
	
## **How to play the game**
	
 1. First, clone the game repository by using the command:
 `git clone https://github.com/pshrey795/COP290Assignments.git` in terminal
 2. Navigate to the [src directory](https://github.com/pshrey795/COP290Assignments/tree/Shrey_Task2/Task2/src)
 3. The game can be built using the `make` command, which will result in an executable called game.
 4. Now, the game can be started depending upon the mode:
			1. **Singleplayer Mode** : Type `./game 1` for starting the game.
			2. **Multiplayer Mode**: Type `./game 1` for starting the server and `./game 0` for starting the client.
5. Before the game window starts, the terminal will ask you certain parameters regarding the desired resolution and your IP address and port number for multiplayer mode.
![](https://github.com/pshrey795/COP290Assignments/blob/Shrey_Task2/Task2/assets/screen/image.png)
 

## **References**

**For the game**
	
 -  [LazyFoo's tutorials](https://lazyfoo.net/tutorials/SDL/) for learning SDL and its submodules. 
 -  Official [SDL documentation](https://wiki.libsdl.org/) for code/syntax related queries.
 -  We referred [this](https://en.wikipedia.org/wiki/Maze_generation_algorithm) wikipedia page for maze generation.

**For simulation**

 - We used wikipedia for reading up on [Dijkstras' algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) and the [travelling salesman(TSP)](https://en.wikipedia.org/wiki/Travelling_salesman_problem) problem.
 - We referred to a [paper by UCDavis](https://web.cs.ucdavis.edu/~amenta/w10/dijkstra.pdf) for arguing thr correctness of Dijkstras' algorithm.

