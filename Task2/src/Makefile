OBJS = main.cpp game.cpp Texture.cpp character.cpp button.cpp play.cpp menu.cpp maze.cpp sounds.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
clean: $(OBJ_NAME)
	rm $(OBJ_NAME)
