CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -lSDL2_image -lGL
LDFLAGS = `sdl2-config --cflags --libs ` -lSDL2_ttf
INCLUDES =
EXEC = main
SRC = main.c fonctions_SDL.c functions_main.c chrono.c score.c end_menu_renderers.c
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