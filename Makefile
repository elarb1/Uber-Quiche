CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -lSDL2_image -lGL
LDFLAGS = `sdl2-config --cflags --libs `
INCLUDES =
EXEC = main
SRC = main.c fonctions_SDL.c camera.c timer.c
OBJ = $(SRC:.c=.o)
all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrpropre: clean
	rm -rf $(EXEC)