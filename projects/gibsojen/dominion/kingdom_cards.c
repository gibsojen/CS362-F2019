#include "dominion.h"
#include <stdio.h>
//#include <math.h>
#include <stdlib.h>

// for testing only
/*
int smithyCard (int card, int choice1, struct gameState *state, int handPos, int *bonus,
     	       int currentPlayer) {
	int i;
        //+3 Cards
        for (i = 0; i < 3; i++)
        {
            drawCard(currentPlayer, state);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;
}
*/

int baronCard (int card, int choice1, struct gameState *state, int handPos, int currentPlayer) {
    //int i;
    //int j;
    //int k;
    //int x;
    //int index;
    //int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;

    //int tributeRevealedCards[2] = {-1, -1};
    //int temphand[MAX_HAND];// moved above the if statement
    //int drawntreasure=0;
    //int cardDrawn;
    //int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)) {
        nextPlayer = 0;
    }

	state->numBuys++;//Increase buys by 1!
        if (choice1 > 0) { //Boolean true or going to discard an estate
            int p = 0;//Iterator for hand!
            int card_not_discarded = 1;//Flag for discard set!
            while(card_not_discarded) {
                if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
                    state->coins += 4;//Add 4 coins to the amount of coins
                    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
                    state->discardCount[currentPlayer]++;
                    for (; p < state->handCount[currentPlayer]; p++) {
                        state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
                    }
                    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
                    state->handCount[currentPlayer]--;
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > state->handCount[currentPlayer]) {
                    if(DEBUG) {
                        printf("No estate cards in your hand, invalid choice\n");
                        printf("Must gain an estate if there are any\n");
                    }
                    if (supplyCount(estate, state) > 0) {
                        gainCard(estate, state, 0, currentPlayer);

                        state->supplyCount[estate]--;//Decrement estates
                        if (supplyCount(estate, state) == 0) {
                            isGameOver(state);
                        }
                    }
                    card_not_discarded = 0;//Exit the loop
                }

                else {
                    p++;//Next card
                }
            }
        }

        else {
            if (supplyCount(estate, state) > 0) {
                gainCard(estate, state, 0, currentPlayer);//Gain an estate

                state->supplyCount[estate]--;//Decrement Estates
                if (supplyCount(estate, state) == 0) {
                    isGameOver(state);
                }
            }
        }

	return 0;
}



int minionCard (int card, int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer) {

	int i;
	int j;
    	int nextPlayer = currentPlayer + 1;
    	if (nextPlayer > (state->numPlayers - 1)) {
        	nextPlayer = 0;
    	}

        //+1 action
        state->numActions++;

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

	if (choice1)
        {
            state->coins = state->coins + 2;
        }
        else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
        {
            //discard hand
            while(numHandCards(state) > 0)
            {
                discardCard(handPos, currentPlayer, state, 0);
            }

            //draw 4
            for (i = 0; i < 4; i++)
            {
                drawCard(currentPlayer, state);
            }

            //other players discard hand and redraw if hand size > 4
            for (i = 0; i < state->numPlayers; i++)
            {
                if (i != currentPlayer)
                {
                    if ( state->handCount[i] > 4 )
                    {
                        //discard hand
                        while( state->handCount[i] > 0 )
                        {
                            discardCard(handPos, i, state, 0);
                        }

                        //draw 4
                        for (j = 0; j < 4; j++)
                        {
                            drawCard(i, state);
                        }
                    }
                }
            }

        }
        return 0;


}

/*

int ambassadorCard (int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus,
     	       int currentPlayer) {

}



int tributeCard (int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus,
     	       int currentPlayer) {

}


int mineCard (int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus,
     	       int currentPlayer) {

}

*/
