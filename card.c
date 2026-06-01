#include <stdio.h>
#include "card.h"

/* Define constant for invalid card */
const Card INVALID_CARD = {-1, -1};

/* Compares the ranks of two cards and returns a positive value if a > b, negative if a < b, and 0 if a == b */
int card_compare_rank(Card a, Card b)
{
    /* Initialize ranks */
    int rank1 = a.rank, rank2 = b.rank;

    /* Handle Ace as highest rank */
    rank1 += (rank1 == 1) ? 13 : 0;
    rank2 += (rank2 == 1) ? 13 : 0;

    /* Return difference in ranks */
    return rank1 - rank2;
}

/* Prints a card in the format, "Rank of Suit" */
void card_print(Card card)
{
    /* Define suit and rank names */
    const char *suit_names[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char *rank_names[] = {"J", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    /* Check that card is valid */
    if (card.rank < 0 || card.rank > 13 ||
        card.suit < 0 || card.suit > 3)
    {
        printf("Invalid card\n");
        return;
    }

    /* Handle Joker case */
    if (card.rank == 0)
    {
        printf("Joker\n");
        return;
    }

    /* Print card */
    printf("%s of %s\n", rank_names[card.rank - 1], suit_names[card.suit]);
}