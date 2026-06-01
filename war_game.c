#include "war_game.h"
#include "card.h"
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

/* Function prototypes for static helper functions */
static void deal_cards(WarGame *game);
static void make_standard_deck(Deck *deck);
static void game_loop(WarGame *game);
static void resolve_war(WarGame *game);
static void award_pile_to_winner(WarGame *game, int winner);

int main()
{
    /* Initialize game */
    WarGame game;
    war_game_init(&game);

    /* Seed randomization with srand */
    srand(time(NULL));

    /* Make standard deck and add to pile */
    make_standard_deck(&game.pile);

    /* Shuffle pile */
    deck_shuffle(&game.pile);

    /* Deal cards to players */
    deal_cards(&game);

    /* Play game */
    game_loop(&game);

    return 0;
}

/* Main game loop */
static void game_loop(WarGame *game)
{
    /* Play rounds until game is over */
    while (!war_game_is_over(game))
    {
        war_game_play_round(game);
    }

    /* Determine winner */
    int winner = war_game_get_winner(game);

    /* Print winner message */
    if (winner == 1)
    {
        printf("Player 1 wins!\n");
    }
    else if (winner == 2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}

/* Initializes a new war game */
void war_game_init(WarGame *game)
{
    /* Initialize player decks and pile */
    deck_init(&game->player1);
    deck_init(&game->player2);
    deck_init(&game->pile);

    /* Initialize round counter */
    game->round = 0;
}

static void make_standard_deck(Deck *deck)
{
    int suit, rank;
    Card new_card;

    for (suit = 0; suit < NUM_SUITS; suit++)
    {
        for (rank = 1; rank <= NUM_RANKS; rank++)
        {
            new_card.suit = suit;
            new_card.rank = rank;

            if (deck_add_bottom(deck, new_card))
            {
                printf("Failed to add card. Aborting...\n");
                return;
            }
        }
    }
}

/* Deals cards from the pile to the two players */
static void deal_cards(WarGame *game)
{
    /* Initialize variables */
    Card card1, card2;
    int i;

    for (i = 0; i < 52; i += 2)
    {
        card1 = deck_draw_top(&game->pile);
        if (card1.rank == INVALID_CARD.rank)
        {
            printf("Failed to draw card. Aborting...\n");
            return;
        }

        card2 = deck_draw_top(&game->pile);
        if (card2.rank == INVALID_CARD.rank)
        {
            printf("Failed to draw card. Aborting...\n");
            return;
        }

        /* Add cards to players' decks */
        if (deck_add_bottom(&game->player1, card1) ||
            deck_add_bottom(&game->player2, card2))
        {
            printf("Failed to add card. Aborting...\n");
            return;
        }
    }
}

/* Plays a single round of War */
int war_game_play_round(WarGame *game)
{
    Card card1, card2;
    int comp_val = 0;
    /* Increment round counter */
    game->round++;

    /* Flip top cards from each player's deck */
    card1 = deck_draw_top(&game->player1);
    card2 = deck_draw_top(&game->player2);
    if (card1.rank == INVALID_CARD.rank || card2.rank == INVALID_CARD.rank)
    {
        printf("Failed to draw card. Aborting...\n");
        return 1;
    }

    /* Cards go to pile */
    deck_add_bottom(&game->pile, card1);
    deck_add_bottom(&game->pile, card2);

    /* Compare cards and determine round winner */
    comp_val = card_compare_rank(card1, card2);

    if (comp_val == 0)
    {
        /* Tie. Time for War! */
        printf("Round %d: War!\n", game->round);
        resolve_war(game);
    }
    else if (comp_val > 0)
    {
        /* Player 1 wins round */
        printf("Round %d: Player 1 wins!\n", game->round);

        /* Award pile to player 1 */
        award_pile_to_winner(game, 1);
    }
    else if (comp_val < 0)
    {
        /* Player 2 wins round */
        printf("Round %d: Player 2 wins!\n", game->round);

        /* Award pile to player 2 */
        award_pile_to_winner(game, 2);
    }

    return 0;
}

/* Resolves a war situation when both players flip cards of the same rank */
static void resolve_war(WarGame *game)
{
    Card card1, card2;
    int comp_val = 0, i;

    while (comp_val == 0)
    {
        /* Check if either player has run out of cards */
        if (game->player1.size == 0 || game->player2.size == 0)
            break;

        /* Flip additional cards for war */
        for (i = 0; i < 3; i++)
        {
            /* Each player puts three cards face down into the pile, if they have enough cards */

            /* Check if player has enough cards to continue war */
            if (game->player1.size > 1)
            {
                /* Draw card from player 1 and add to pile */
                card1 = deck_draw_top(&game->player1);
                if (card1.rank == INVALID_CARD.rank)
                {
                    printf("Failed to draw card. Aborting...\n");
                    return;
                }
                deck_add_bottom(&game->pile, card1);
            }

            /* Check if player has enough cards to continue war */
            if (game->player2.size > 1)
            {
                /* Draw card from player 2 and add to pile */
                card2 = deck_draw_top(&game->player2);
                if (card2.rank == INVALID_CARD.rank)
                {
                    printf("Failed to draw card. Aborting...\n");
                    return;
                }
                deck_add_bottom(&game->pile, card2);
            }
        }

        /* Flip one more card from each player to compare */
        card1 = deck_draw_top(&game->player1);
        card2 = deck_draw_top(&game->player2);
        if (card1.rank == INVALID_CARD.rank || card2.rank == INVALID_CARD.rank)
        {
            printf("Failed to draw card. Aborting...\n");
            return;
        }
        /* Add flipped cards to pile */
        deck_add_bottom(&game->pile, card1);
        deck_add_bottom(&game->pile, card2);

        /* Compare flipped cards */
        comp_val = card_compare_rank(card1, card2);
    }

    /* Determine winner of war */
    if (comp_val == 0)
    {
        if (!game->player1.size && !game->player2.size)
            ;
        else if (game->player1.size)
            comp_val = 1;
        else
            comp_val = -1;
    }

    if (comp_val > 0)
    {
        printf("War won by Player 1!\n");
        award_pile_to_winner(game, 1);
    }
    else if (comp_val < 0)
    {
        printf("War won by Player 2!\n");
        award_pile_to_winner(game, 2);
    }
    else
    {
        printf("War ended in a tie!\n");
    }
}

/* Awards the cards in the pile to the winner of a round or war */
static void award_pile_to_winner(WarGame *game, int winner)
{
    /* Initialize variables */
    Card card;
    Deck *winning_deck = (winner == 1) ? &game->player1 : &game->player2;

    while (game->pile.size > 0)
    {
        /* Draw card and add to winner's deck */
        card = deck_draw_top(&game->pile);
        if (card.rank == INVALID_CARD.rank)
        {
            printf("Failed to draw card. Aborting...\n");
            return;
        }

        deck_add_bottom(winning_deck, card);
    }
}

/* Checks if the game is over */
int war_game_is_over(const WarGame *game)
{
    return game->player1.size == 0 || game->player2.size == 0;
}

/* Determines the winner of the game: returns 1 for player 1, 2 for player 2, 0 for tie, and -1 if game is not over */
int war_game_get_winner(const WarGame *game)
{
    if (game->player1.size == 0 && game->player2.size == 0)
    {
        /* Tie */
        return 0;
    }
    else if (game->player1.size == 0)
    {
        /* Player 2 wins */
        return 2;
    }
    else if (game->player2.size == 0)
    {
        /* Player 1 wins */
        return 1;
    }
    else
    {
        /* Game is not over */
        return -1;
    }
}