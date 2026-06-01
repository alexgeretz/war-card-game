#if !defined(CARD_H)
#define CARD_H
/*
  File description:
  card.h defines an enum for the suits of a playing card
  and the data structure for a playing card.

  Each card has a suit and a rank.

  Deck is a linked list with a dummy head; any function parameters calling
  the Deck take this into account.
  Each Deck contains a pointer to a Card head, a pointer to a
  Card tail, and a pointer to the next Inoq_list.
  Pointers are used to bound the memory allocation required for an Inoq_list.
*/

typedef enum
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

typedef enum
{
    JOKER,
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Rank;

typedef struct
{
    Suit suit;
    Rank rank;
} Card;

/* Function prototypes */
void card_print(Card card);
int card_compare_rank(Card a, Card b);

/* Declare constant*/
extern const Card INVALID_CARD;

#endif