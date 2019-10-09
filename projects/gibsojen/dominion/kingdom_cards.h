#ifndef _KINGDOM_CARDS_H
#define _KINGDOM_CARDS_H


int baronCard (int card, int choice1, struct gameState *state, int handPos, int currentPlayer);

int minionCard (int card, int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

// for testing only
//int smithyCard (int card, int choice1, struct gameState *state, int handPos, int *bonus,
//     	       int currentPlayer);
#endif
