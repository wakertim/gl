CC =gcc
BIN =bin/a.out
LIBS =-lGL -lX11 -lm
SOURCE_FILES =main.c platform.c gl.c shader.c umalloc.c matrix.c
CFLAGS =-g -Wall 

all:
	clear
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(LIBS) -o $(BIN)
	./$(BIN)

compile:
	clear
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(LIBS) -o $(BIN)

valgrind:
	valgrind ./$(BIN)
	
clean:
	rm -fr $(BIN)

