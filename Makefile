#all:
#	g++ -Iinclude -Iinclude/SDL2 -Iinclude/headers -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

#CC specifies which compiler we're using
CC = g++

#INC
INC = -Iinclude/headers

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all: 
	$(CC) $(INC) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS) 


clean:
	-rm main