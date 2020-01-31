CC=gcc
CFLAGS=-ansi -Wall -Wfatal-errors -std=c99 -g
LDFLAGS= -lMLV -lm

SRCDIR= src/
INCLDIR= include/
OBJS= bin/main.o bin/background.o bin/rocket.o bin/enemy.o bin/shoot.o bin/collision.o bin/file.o

Game:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


bin/main.o: $(SRCDIR)main.c $(INCLDIR)background.h $(INCLDIR)rocket.h $(INCLDIR)enemy.h $(INCLDIR)shoot.h $(INCLDIR)collision.h $(INCLDIR)file.h 
	$(CC) -c $< $(CFLAGS) -o bin/main.o
bin/background.o: $(SRCDIR)background.c $(INCLDIR)background.h 
	$(CC) -c $< $(CFLAGS) -o bin/background.o
bin/rocket.o: $(SRCDIR)rocket.c $(INCLDIR)rocket.h  $(INCLDIR)background.h
	$(CC) -c $< $(CFLAGS) -o bin/rocket.o
bin/enemy.o: $(SRCDIR)enemy.c $(INCLDIR)enemy.h $(INCLDIR)background.h
	$(CC) -c $< $(CFLAGS) -o bin/enemy.o
bin/shoot.o: $(SRCDIR)shoot.c $(INCLDIR)shoot.h $(INCLDIR)background.h
	$(CC) -c $< $(CFLAGS) -o bin/shoot.o
bin/collision.o: $(SRCDIR)collision.c $(INCLDIR)collision.h $(INCLDIR)enemy.h $(INCLDIR)shoot.h
	$(CC) -c $< $(CFLAGS) -o bin/collision.o
bin/file.o:$(SRCDIR)file.c $(INCLDIR)file.h
	$(CC) -c $< $(CFLAGS) -o bin/file.o
clean:
	rm -f bin/*.o
mrproper: clean
	rm -f Game
