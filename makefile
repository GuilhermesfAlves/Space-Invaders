CC = gcc
Cflags = -Wall
#Para compilação dos programas que usam allegro5.h
allegro := $$(pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs $(Cflags))

#arquivos objeto
objects = main.o ship.o enemy.o space.o

all: space_invaders

space_invaders: $(objects)
	$(CC) -o $@ $^

main.o: main.c
	$(CC) -c $(allegro) $^

ship.o: ship.c
	$(CC) -c $(Cflags) $^

enemy.o: enemy.c
	$(CC) -c $(Cflags) $^

space.o: space.c
	$(CC) -c $(Cflags) $^

clean:
	remove -f $(objects) space_invaders