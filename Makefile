CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -lSDL2_image
LDFLAGS = `sdl2-config --cflags --libs `
INCLUDES =
EXEC = main
SRC = main.c fonctions_SDL.c
OBJ = $(SRC:.c=.o)
all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)