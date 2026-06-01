CC = gcc
CFLAGS = -pedantic-errors -Wall -Wextra -fstack-protector-all -Werror -g

all: war_game.exe

war_game.exe: war_game.o deck.o card.o
	$(CC) war_game.o deck.o card.o -o war_game.exe

war_game.o: war_game.c war_game.h deck.h card.h
	$(CC) $(CFLAGS) -c war_game.c

deck.o: deck.c deck.h card.h
	$(CC) $(CFLAGS) -c deck.c

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

clean:
	- rm *.o *.exe