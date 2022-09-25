#CC specifies which compiler we're using
CC = gcc

LIBS =

SRC=src
SRCS=$(wildcard $(SRC)/*.c)

LIBS=$(wildcard $(SRC)/*.h)

BIN = bin/main

COMPILER_FLAGS = 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2main -lSDL2_ttf

RM = 

#OBJ_NAME specifies the name of our exectuable


#This is the target that compiles our executable
all : $(BIN) run clean


$(BIN):  $(SRCS) $(LIBS)
	$(CC) $(SRCS) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@


main: $(SRCS) $(LIBS)
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN)


run: $(BIN)
	$(BIN)


clean : 
	rm -r bin/*