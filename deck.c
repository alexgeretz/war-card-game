#include "deck.h"
#include "card.h"
#include <stdlib.h>

/* Initializes an empty deck */
void deck_init(Deck *deck)
{
    deck->top = 0;
    deck->bottom = 0;
    deck->size = 0;
}

/* Check deck size */
int deck_size(const Deck *deck)
{
    return deck->size;
}

/* Check if deck is empty */
int deck_is_empty(const Deck *deck)
{
    return deck->size == 0;
}

/* Check if deck is full */
int deck_is_full(const Deck *deck)
{
    return deck->size == DECK_CAPACITY;
}

/* Function prototypes for drawing and adding cards */
Card deck_draw_top(Deck *deck)
{
    /* Initialize card  */
    Card card;

    /* If deck is empty, return early */
    if (deck_is_empty(deck))
        return INVALID_CARD;

    /* Point card to the top Card in the Deck */
    card = *(deck->cards + deck->top);

    /* Move top pointer forward and decrement size */
    deck->top = (deck->top + 1) % DECK_CAPACITY;
    deck->size--;

    /* Done! */
    return card;
}

Card deck_draw_bottom(Deck *deck)
{
    /* Initialize card  */
    Card card;

    /* If deck is empty, return early */
    if (deck_is_empty(deck))
        return INVALID_CARD;

    /* Point card to the bottom Card in the Deck */
    card = *(deck->cards + deck->bottom);

    /* Move bottom pointer back and decrement size */
    deck->bottom = (deck->bottom - 1 + DECK_CAPACITY) % DECK_CAPACITY;
    deck->size--;

    /* Done! */
    return card;
}

int deck_add_top(Deck *deck, Card card)
{
    /* If deck is full, return early */
    if (deck_is_full(deck))
        return 1;

    /* Move top pointer back and add card */
    deck->top = (deck->top - 1 + DECK_CAPACITY) % DECK_CAPACITY;
    deck->cards[deck->top] = card;

    /* Increment size */
    deck->size++;

    /* Done! */
    return 0;
}

int deck_add_bottom(Deck *deck, Card card)
{
    /* If deck is full, return early */
    if (deck_is_full(deck))
        return 1;

    /* Add card and move bottom pointer forward */
    deck->cards[deck->bottom] = card;
    deck->bottom = (deck->bottom + 1) % DECK_CAPACITY;

    /* Increment size */
    deck->size++;

    /* Done! */
    return 0;
}

void deck_shuffle(Deck *deck)
{
    /* Initialize variables */
    int i, r;
    Card temp;

    /* Shuffle using the Fisher-Yates algorithm */
    for (i = deck->size - 1; i > 0; i--)
    {
        /* Generate a random index from 0 to i */
        r = rand() % (i + 1);

        /* Save temp of card at index i */
        temp = deck->cards[(deck->top + i) % DECK_CAPACITY];

        /* Swap cards at indices i and r */
        deck->cards[(deck->top + i) % DECK_CAPACITY] = deck->cards[(deck->top + r) % DECK_CAPACITY];
        deck->cards[(deck->top + r) % DECK_CAPACITY] = temp;
    }
}

void deck_print(const Deck *deck)
{
    int i;
    for (i = 0; i < deck->size; i++)
    {
        card_print(deck->cards[(deck->top + i) % DECK_CAPACITY]);
    }
}