#include "deck.h"

#if !defined(WAR_H)
#define WAR_H
/*
  File description:
  war_game.h defines the data structure for a game of War and the function prototypes for operations on a WarGame.
*/

/* WarGame struct definition */
typedef struct
{
  Deck player1;
  Deck player2;
  Deck pile;
  int round;
} WarGame;

/* Function prototypes for WarGame operations */
void war_game_init(WarGame *game);

int war_game_play_round(WarGame *game);

int war_game_is_over(const WarGame *game);

int war_game_get_winner(const WarGame *game);

#endif