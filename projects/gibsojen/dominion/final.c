#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>


int main() {

   // set players and seed
   int numOfPlayers = 2;
   int seed = 232;

   // declare game state
   struct gameState G;

   // set card array
   int k[10] = {adventurer, baron, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int currPlayer = 0;


   // begin testing scoreFor
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   
 
   G.hand[currPlayer][0] = estate; //1
   G.hand[currPlayer][1] = estate; 
   G.hand[currPlayer][2] = estate;
   G.hand[currPlayer][3] = estate;
   G.hand[currPlayer][4] = estate;
   G.handCount[currPlayer] = 5;


   G.deck[currPlayer][0] = duchy; //3
   G.deck[currPlayer][1] = duchy;
   G.deck[currPlayer][2] = duchy;
   G.deck[currPlayer][3] = duchy;
   G.deck[currPlayer][4] = duchy;
   G.deckCount[currPlayer] = 5;


   G.discard[currPlayer][0] = province; //6
   G.discard[currPlayer][1] = province;
   G.discard[currPlayer][2] = province;
   G.discardCount[currPlayer] = 3;

   // total 38
    

   int finalScore;
   finalScore = scoreFor (currPlayer, &G);
   printf("Final Score = %d\n\n", finalScore);


   if (finalScore == 38) {
      printf("OK: Final score is 38.\n");
   }
   else {
      printf("ERROR: Final score is %d, but it should be 38.\n", finalScore);
   }

   printf("\n\n");


   printf("** END TEST No. 1 *************************************************************\n\n\n\n");

   

   // begin testing scoreFor
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   
 
   G.hand[currPlayer][0] = estate; //1
   G.hand[currPlayer][1] = estate; 
   G.hand[currPlayer][2] = estate;
   G.hand[currPlayer][3] = estate;
   G.hand[currPlayer][4] = estate;
   G.handCount[currPlayer] = 5;


   G.deck[currPlayer][0] = duchy; //3
   G.deck[currPlayer][1] = duchy;
   //G.deck[currPlayer][2] = duchy;
   //G.deck[currPlayer][3] = province;
   G.deckCount[currPlayer] = 2;


   G.discard[currPlayer][0] = province; //6
   G.discard[currPlayer][1] = province;
   G.discard[currPlayer][2] = province;
   G.discard[currPlayer][3] = province;
   G.discard[currPlayer][4] = province;
   G.discardCount[currPlayer] = 5;

   // total 41
    

   finalScore = scoreFor (currPlayer, &G);
   printf("Final Score = %d\n\n", finalScore);


   if (finalScore == 41) {
      printf("OK: Final score is 41.\n");
   }
   else {
      printf("ERROR: Final score is %d, but it should be 41.\n", finalScore);
   }

   printf("\n\n");


   printf("** END TEST No. 2 *************************************************************\n\n\n\n");







   return 0;	
}
