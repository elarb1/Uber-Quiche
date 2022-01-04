CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -lSDL2_image -lGL
LDFLAGS = `sdl2-config --cflags --libs ` -lSDL2_ttf
INCLUDES =
EXEC = main
<<<<<<< HEAD
SRC = main.c fonctions_SDL.c functions_main.c chrono.c score.c end_menu_renderers.c
=======
SRC = main.c fonctions_SDL.c functions_main.c player.c
>>>>>>> 7db6951d2083f5c824c6325fbb98d977e3426e8e
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