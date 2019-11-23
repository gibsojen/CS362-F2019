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
   struct gameState G, testGame;

   // set card array
   int k[10] = {adventurer, baron, ambassador, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int currPlayer = 0;
   int nextPlayer = 1;


   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** 2 different treasure cards revealed, so +4 coins\n");
   printf("** current players actions remain the same, current players hand count should not change\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = copper;
   G.deck[nextPlayer][1] = gold;
   G.deck[nextPlayer][2] = silver;
   G.deck[nextPlayer][3] = copper;
   G.deck[nextPlayer][4] = silver;
   G.deck[nextPlayer][5] = gold;
   G.deck[nextPlayer][6] = copper;
   G.deck[nextPlayer][7] = silver;
   G.deckCount[nextPlayer] = 8;

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   cardEffect(tribute, 0 ,0 ,0, &testGame, 0, 0);



   if (G.coins + 4 == testGame.coins) {
      printf("OK:  the number of coins increased by 4, 2 for each treasure card.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 4, 2 for each treasure card.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 4);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remained the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else if (G.numActions < testGame.numActions) {
      printf("ERROR:  the number of actions increased.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions decreased.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count of the current player has not changed.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if (G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count of the current player has increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count of the current player has decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }



   printf("** END TEST No. 1 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** 2 different action cards revealed, so +2 actions per card\n");
   printf("** current players coins remain the same, current players hand count should not change\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = remodel;
   G.deck[nextPlayer][1] = outpost;
   G.deck[nextPlayer][2] = feast;
   G.deck[nextPlayer][3] = adventurer;
   G.deck[nextPlayer][4] = tribute;
   G.deckCount[nextPlayer] = 5;

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   cardEffect(tribute, 0 ,0 ,0, &testGame, 0, 0);

   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins remained the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not remain the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }



   if (G.numActions + 4 == testGame.numActions) {
      printf("OK:  the number of actions increased by 4, 2 for each action card revealed.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 4);
   }
   else {
      printf("ERROR:  the number of actions did not increase by 4, 2 for each action card revealed.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 4);
   }



   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count of the current player has not changed.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else if (G.handCount[currPlayer] < testGame.handCount[currPlayer]) {
      printf("ERROR:  the hand count of the current player has increased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count of the current player has decreased.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer]);
   }





   printf("** END TEST No. 2 *************************************************************\n\n\n\n");


   
   // begin testing
   printf("\n\n** BEGIN TEST No. 3 *************************************************************\n");
   printf("** 2 different victory cards revealed, so +2 cards per card\n");
   printf("** current players coins remain the same, current players hand count should increase by 4, actions remain the same\n");
   printf("** next players deck should decrease by 2, next players discards should increase by 2 \n\n\n");


   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = duchy;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = minion;
   G.hand[currPlayer][4] = ambassador;
   G.handCount[currPlayer] = 5;


   G.deck[nextPlayer][0] = province;
   G.deck[nextPlayer][1] = duchy;
   G.deck[nextPlayer][2] = estate;
   G.deck[nextPlayer][3] = province;
   G.deck[nextPlayer][4] = duchy;
   G.deckCount[nextPlayer] = 5;

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   cardEffect(tribute, 0 ,0 ,0, &testGame, 0, 0);


   if (G.coins == testGame.coins) {
      printf("OK:  the number of coins remained the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }
   else {
      printf("ERROR:  the number of coins did not remain the same.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins);
   }



   if (G.numActions == testGame.numActions) {
      printf("OK:  the number of actions remains the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }
   else {
      printf("ERROR:  the number of actions did not remain the same.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions);
   }



   if (G.handCount[currPlayer] + 4 == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count has increased by 4 cards, +2 cards for each card by next player.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer] + 4);
   }
   else {
      printf("ERROR:  the hand count has not increased by 4 cards, +2 cards for each card by next player.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.deckCount[currPlayer] + 4);
   }



   printf("** END TEST No. 3 *************************************************************\n\n\n\n");



   return 0;	
}
