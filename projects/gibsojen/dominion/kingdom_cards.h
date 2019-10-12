#ifndef _KINGDOM_CARDS_H
#define _KINGDOM_CARDS_H


int remEstateSupply (struct gameState *state);

int baronCard (int choice1, struct gameState *state, int currentPlayer);

int minionCard (int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

int ambassadorCard (int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

int tributeCard (struct gameState *state, int currentPlayer);

int mineCard (int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

// for testing only
//int smithyCard (int card, int choice1, struct gameState *state, int handPos, int *bonus,
//     	       int currentPlayer);
#endif
