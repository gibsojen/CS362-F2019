#include "dominion.h"
#include "dominion_helpers.h"
#include "kingdom_cards.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void cardNumToName(int card, char *name) {
    switch(card) {
    case curse:
        strcpy(name,"Curse");
        break;
    case estate:
        strcpy(name,"Estate");
        break;
    case duchy:
        strcpy(name,"Duchy");
        break;
    case province:
        strcpy(name,"Province");
        break;
    case copper:
        strcpy(name,"Copper");
        break;
    case silver:
        strcpy(name,"Silver");
        break;
    case gold:
        strcpy(name,"Gold");
        break;
    case adventurer:
        strcpy(name,"Adventurer");
        break;
    case council_room:
        strcpy(name,"Council Room");
        break;
    case feast:
        strcpy(name,"Feast");
        break;
    case gardens:
        strcpy(name,"Gardens");
        break;
    case mine:
        strcpy(name,"Mine");
        break;
    case remodel:
        strcpy(name,"Remodel");
        break;
    case smithy:
        strcpy(name,"Smithy");
        break;
    case village:
        strcpy(name,"Village");
        break;
    case baron:
        strcpy(name,"Baron");
        break;
    case great_hall:
        strcpy(name,"Great Hall");
        break;
    case minion:
        strcpy(name,"Minion");
        break;
    case steward:
        strcpy(name,"Steward");
        break;
    case tribute:
        strcpy(name,"Tribute");
        break;
    case ambassador:
        strcpy(name,"Ambassador");
        break;
    case cutpurse:
        strcpy(name,"Cutpurse");
        break;
    case embargo:
        strcpy(name,"Embargo");
        break;
    case outpost:
        strcpy(name,"Outpost");
        break;
    case salvager:
        strcpy(name,"Salvager");
        break;
    case sea_hag:
        strcpy(name,"Sea Hag");
        break;
    case treasure_map:
        strcpy(name,"Treasure Map");
        break;

    default:
        strcpy(name,"?");
    }

}




int main() {

   // set players and seed
   int numOfPlayers = 2;
   int seed = 232;

   // declare game state
   struct gameState G, testGame;

   // set card array
   int k[10] = {adventurer, baron, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int handPos = -1;
   int currPlayer = 0;
   int choice1 = 0;
   int choice2 = 0;
   int i = 0;
   int retError;


   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** choice1 = 1, choice2 = 0, +2 coins, +1 action\n");
   printf("** hand is not discarded \n");
   printf("** in this test, the user chooses to gain 2 coins \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   // Players Hand
   printf("Players Hand Before Play:\n");
    int handCount = testGame.handCount[currPlayer];
    int handIndex;
    printf("Player %d's hand:\n", currPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[currPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");


   choice1 = 1;
   choice2 = 0;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = minionCard (choice1, choice2, &testGame, handPos, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of minion was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of minion was -1.\n\n");
   }


   if (G.numActions + 1 == testGame.numActions) {
      printf("OK:  the number of actions has increased by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }
   else {
      printf("ERROR:  the number of actions did not increase by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }



   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins has increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }


   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer]) {
      printf("OK:  the number of discards is 0.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 0\n\n");
   }
   else {
      printf("ERROR:  the number of discards is not 0.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = 0\n\n");
   }
  

   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  hand count remained the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand aftere play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  hand count has changed.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand aftere play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }



   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");


   printf("** END TEST No. 1 *************************************************************\n\n\n\n");



   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** choice1 = 0, choice1 = 0, +0 coins, +1 action, +4 new cards\n");
   printf("** hand is discarded \n");
   printf("** in this test, the user chooses to discard hand and gain 4 new cards \n");
   printf("** this only tests current player's hand \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));


   // Players Hand
   printf("Players Hand Before Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n");



   choice1 = 0;
   choice2 = 1;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = minionCard (choice1, choice2, &testGame, handPos, currPlayer);

   
   if (retError == 0) {
      printf("OK:  the return code of minion was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of minion was -1.\n\n");
   }

   if (G.numActions + 1 == testGame.numActions) {
      printf("OK:  the number of actions has increased by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }
   else {
      printf("ERROR:  the number of actions did not increase by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }

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

   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer] + 5) {
      printf("OK:  the number of discards has increased by 5 for discarding hand.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n", G.discardCount[currPlayer] + 5);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 5 for discarding hand.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n", G.discardCount[currPlayer] + 5);

      
      if (testGame.playedCardCount > G.playedCardCount) {
         printf("Instead of being discarded, the cards are in played cards.\n");
         printf("Number of played cards before play = %d\n", G.playedCardCount);
         printf("Number of played cards after play = %d\n", testGame.playedCardCount);
         printf("These are the cards in played cards:\n");
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n\n");
      }
   }


   if (testGame.handCount[currPlayer] == 4) {
      printf("OK:  the new number of cards in player's hand is 4.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = 4\n\n");
   } 
   else {
      printf("ERROR:  the number of played cards in player's hand is not 4.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = 4\n\n");
   }



   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");





   printf("** END TEST No. 2 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 3 *************************************************************\n");
   printf("** choice1 = 0, choice1 = 0, +0 coins, +1 action, +4 new cards\n");
   printf("** hand is discarded \n");
   printf("** in this test, the user chooses to discard hand and gain 4 new cards\n");
   printf("** this only tests opponent's hands \n\n\n");

   int nextPlayer = 1;
   int extraPlayer = 2;

   G.hand[nextPlayer][0] = baron;
   G.hand[nextPlayer][1] = minion;
   G.hand[nextPlayer][2] = mine;
   G.hand[nextPlayer][3] = gold;
   G.hand[nextPlayer][4] = silver;
   G.handCount[nextPlayer] = 5;


   G.hand[extraPlayer][0] = baron;
   G.hand[extraPlayer][1] = minion;
   G.hand[extraPlayer][2] = mine;
   G.hand[extraPlayer][3] = gold;
   G.hand[extraPlayer][4] = silver;
   G.handCount[extraPlayer] = 5;

   G.deck[extraPlayer][0] = curse;
   G.deck[extraPlayer][1] = duchy;
   G.deck[extraPlayer][2] = adventurer;
   G.deck[extraPlayer][3] = feast;
   G.deck[extraPlayer][4] = gardens;
   G.deckCount[extraPlayer] = 5;


   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

   

   // Next Players Hand
   printf("Next Players Hand Before Play:\n");
    handCount = testGame.handCount[nextPlayer];
    printf("Player %d's hand:\n", nextPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[nextPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n\n");



   // Extra Players Hand
   printf("Extra Players Hand Before Play:\n");
    handCount = testGame.handCount[extraPlayer];
    printf("Player %d's hand:\n", extraPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[extraPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n\n");

   choice1 = 0;
   choice2 = 1;
   int played = testGame.playedCardCount;

   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = minionCard (choice1, choice2, &testGame, handPos, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of minion was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of minion was -1.\n\n");
   }


   if (G.handCount[nextPlayer] == 5 && testGame.handCount[nextPlayer] == 4) {
      printf("OK:  the next player had 5 cards, and now they have 4.\n");
      printf("Player 1 hand count before play: %d\n", G.handCount[nextPlayer]);
      printf("Player 1 hand count after play: %d,  ", testGame.handCount[nextPlayer]);
      printf("Player 1 hand count expected:  %d\n\n", G.handCount[nextPlayer] - 1);
   }
   else {
      printf("ERROR:  the next player had 5 cards, but they do not have 4 now.\n");
      printf("Player 1 hand count before play: %d\n", G.handCount[nextPlayer]);
      printf("Player 1 hand count after play: %d,  ", testGame.handCount[nextPlayer]);
      printf("Player 1 hand count expected:  %d\n\n", G.handCount[nextPlayer] - 1);
   }


   if (testGame.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 5) {
      printf("OK:  the number of discards has increased by 5 for discarding hand.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n", G.discardCount[nextPlayer] + 5);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 5 for discarding hand.\n");
      printf("Number of discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of discards expected = %d\n", G.discardCount[nextPlayer] + 5);

      
      if (testGame.playedCardCount > played) {
         printf("Instead of being discarded, the cards are in played cards.\n");
         printf("Number of played cards before play = %d\n", played);
         printf("Number of played cards after play = %d\n\n", testGame.playedCardCount);
      }
   }



   if (G.handCount[extraPlayer] == testGame.handCount[extraPlayer]) {
      printf("OK:  since this is a 2 player game, the extra player's hand count did not change.\n");
      printf("Player 2 hand count before play: %d\n", G.handCount[extraPlayer]);
      printf("Player 2 hand count after play: %d,  ", testGame.handCount[extraPlayer]);
      printf("Player 2 hand count expected:  %d\n\n", G.handCount[extraPlayer]);
   }
   else {
      printf("ERROR:  since this is a 2 player game, the extra player's hand count should not change but it did.\n");
      printf("Player 2 hand count before play: %d\n", G.handCount[extraPlayer]);
      printf("Player 2 hand count after play: %d,  ", testGame.handCount[extraPlayer]);
      printf("Player 2 hand count expected:  %d\n\n", G.handCount[extraPlayer]);
     
   }


   // Next Players Hand
   printf("Next Players Hand After Play:\n");
    handCount = testGame.handCount[nextPlayer];
    printf("Player %d's hand:\n", nextPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[nextPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n\n");



   // Extra Players Hand
   printf("Extra Players Hand After Play:\n");
   handCount = testGame.handCount[extraPlayer];
   printf("Player %d's hand:\n", extraPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[extraPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }




   printf("\n\n");


 
   printf("** END TEST No. 3 *************************************************************\n\n\n\n");



   // begin testing
   printf("\n\n** BEGIN TEST No. 4 *************************************************************\n");
   printf("** choice1 = 1, choice2 = 1, +2 coins, +1 action\n");
   printf("** all options are tested \n");
   printf("** in this test, check for boundard case \n\n\n");

   // copy game state for test game
   memcpy(&testGame, &G, sizeof(struct gameState));

 
   // Players Hand
   printf("Players Hand Before Play:\n");
    handCount = testGame.handCount[currPlayer];
    printf("Player %d's hand:\n", currPlayer);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = testGame.hand[currPlayer][handIndex];
        char name[32];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");


   choice1 = 1;
   choice2 = 1;
   //cardEffect(minion, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = minionCard (choice1, choice2, &testGame, handPos, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of minion was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of minion was -1.\n\n");
   }


   if (G.numActions + 1 == testGame.numActions) {
      printf("OK:  the number of actions has increased by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }
   else {
      printf("ERROR:  the number of actions did not increase by 1.\n");
      printf("Number of actions before play = %d\n", G.numActions);
      printf("Number of actions after play = %d,  ", testGame.numActions);
      printf("Number of actions expected = %d\n\n", G.numActions + 1);
   }



   if (G.coins + 2 == testGame.coins) {
      printf("OK:  the number of coins has increased by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }
   else {
      printf("ERROR:  the number of coins did not increase by 2.\n");
      printf("Number of coins before play = %d\n", G.coins);
      printf("Number of coins after play = %d,  ", testGame.coins);
      printf("Number of coins expected = %d\n\n", G.coins + 2);
   }



   if (testGame.discardCount[currPlayer] == G.discardCount[currPlayer]) {
      printf("OK:  the number of discards remained the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the number of discards did not remain the same.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);

      
      if (testGame.playedCardCount > G.playedCardCount) {
         printf("Instead of being discarded, the cards are in played cards.\n");
         printf("Number of played cards before play = %d\n", G.playedCardCount);
         printf("Number of played cards after play = %d\n", testGame.playedCardCount);
         printf("These are the cards in played cards:\n");
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n\n");
      }
   }


   if (testGame.handCount[currPlayer] == G.handCount[currPlayer]) {
      printf("OK:  the number of cards in hand remained the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   } 
   else {
      printf("ERROR:  the number of cards in hand did not remain the same.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of cards in hand expected = %d\n\n", G.handCount[currPlayer]);
   }



   // Players Hand
   printf("Players Hand After Play:\n");
   handCount = testGame.handCount[currPlayer];
   printf("Player %d's hand:\n", currPlayer);
   if(handCount > 0) printf("#  Card\n");
   for(handIndex = 0; handIndex < handCount; handIndex++) {
      int card = testGame.hand[currPlayer][handIndex];
      char name[32];
      cardNumToName(card, name);
      printf("%-2d %-13s\n", handIndex, name);
   }
   printf("\n\n");


   printf("** END TEST No. 4 *************************************************************\n\n\n\n");




   

   return 0;	
}
