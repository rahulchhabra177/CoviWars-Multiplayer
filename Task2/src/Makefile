OBJS = ./main/main.cpp ./main/game.cpp ./texture/Texture.cpp ./character/coviwars.cpp ./button/button.cpp ./playstate/play.cpp ./menu/menu.cpp ./maze/maze.cpp ./sound/sounds.cpp ./character/enemy.cpp ./scoreboard/scoreboard.cpp ./network/network.cpp ./menu/popup.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
OBJ_NAME = game
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
clean: $(OBJ_NAME)
	rm $(OBJ_NAME)