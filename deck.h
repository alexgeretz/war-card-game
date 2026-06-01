#include "card.h"

#if !defined(DECK_H)
#define DECK_H
/*
  File description:
  deck.h defines the data structure for a deck of playing cards.
*/

#define DECK_CAPACITY 52

typedef struct
{
    Card cards[DECK_CAPACITY];
    int top;
    int bottom;
    int size;
} Deck;

/* Function prototypes */

/* Initializes an empty deck */
void deck_init(Deck *deck);

/* Deck size functions */
int deck_size(const Deck *deck);

int deck_is_empty(const Deck *deck);
int deck_is_full(const Deck *deck);

/* Function prototypes for drawing and adding cards */
Card deck_draw_top(Deck *deck);
Card deck_draw_bottom(Deck *deck);
int deck_add_top(Deck *deck, Card card);
int deck_add_bottom(Deck *deck, Card card);

void deck_shuffle(Deck *deck);
void deck_print(const Deck *deck);

#endif