#include "dominion.h"
#include "dominion_helpers.h"
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
   int k[10] = {adventurer, baron, ambassador, embargo, village, minion, mine, cutpurse, sea_hag, tribute};

   // initialize game
   initializeGame(numOfPlayers, k, seed, &G);

   int handPos = 1;
   //int bonus = 0;
   int currPlayer = 0;
   int nextPlayer = 1;
   int choice1 = 0;
   int choice2 = 0;
   //int choice3 = 0;
   int retError;


   // begin testing
   printf("\n\n** BEGIN TEST No. 1 *************************************************************\n");
   printf("** choice1 = 3 (copper), choice2 = 0\n");
   printf("** player returns 0 coppers to supply \n\n\n");

   G.hand[currPlayer][0] = mine;
   G.hand[currPlayer][1] = ambassador;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;


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


   choice1 = 3; // card in hand to return
   choice2 = 0; // how many cards player wants to return to supply

   int selectedCard = testGame.hand[currPlayer][choice1];
   char name[32];
   cardNumToName(selectedCard, name);
   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   int played = testGame.playedCardCount;

   //cardEffect(ambassador, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = ambassadorEffect (choice1, choice2, &testGame, handPos, currPlayer);

   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[copper]);


   if (retError == 0) {
      printf("OK:  the return code of ambassador was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of ambassador was -1.\n\n");
   }


   if (G.handCount[currPlayer] - choice2 - 1 == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count is decreased by %d.\n", choice2 - 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }
   else {
      printf("ERROR:  the hand count was not decreased by %d.\n", choice2 - 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }

   if (G.discardCount[currPlayer] + 1 == testGame.discardCount[currPlayer]) {
      printf("OK:  the number of discards for the current player increased by 1 for discarding ambassador.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }
   else {
      printf("ERROR:  the numbeer of discards of current player did not increase by 1 for discarding ambassador.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer]);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n\n");
   }

   if (G.supplyCount[selectedCard] + choice2 - 1 == testGame.supplyCount[selectedCard]) {
      printf("OK:  the supply was adjusted by by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] + choice2 - 1);
   }
   else {
      printf("ERROR:  the supply was adjusted by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] + choice2 - 1);
   }



   if (G.discardCount[nextPlayer] + 1 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the next player's discards was increased by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);

   }
   else {
      printf("ERROR:  the next player's discards did not increase by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);
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


   
   // begin testing
   printf("\n\n** BEGIN TEST No. 2 *************************************************************\n");
   printf("** choice1 = 3 (copper), choice2 = 1\n");
   printf("** player returns 1 coppers to supply \n\n\n");

   G.hand[currPlayer][0] = mine;
   G.hand[currPlayer][1] = ambassador;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;


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


   choice1 = 3; // card in hand to return
   choice2 = 1; // how many cards player wants to return to supply

   selectedCard = testGame.hand[currPlayer][choice1];
   cardNumToName(selectedCard, name);
   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   played = testGame.playedCardCount;

   //cardEffect(ambassador, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = ambassadorEffect (choice1, choice2, &testGame, handPos, currPlayer);

   if (retError == 0) {
      printf("OK:  the return code of ambassador was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of ambassador was -1.\n\n");
   }

   if (G.handCount[currPlayer] - choice2 - 1 == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count is decreased by %d.\n", choice2 + 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }
   else {
      printf("ERROR:  the hand count was not decreased by %d.\n", choice2 + 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }

   if (G.discardCount[currPlayer] + 1 == testGame.discardCount[currPlayer]) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }

   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
      int i;
         for (i = 0; i < testGame.playedCardCount; i++) {
            int card = testGame.playedCards[i];
            char name[32];
            cardNumToName(card, name);
            printf("Played Card #%d is: %-13s \n", i, name);
         }
         printf("\n");
   }

   if (G.supplyCount[selectedCard] + choice2 - 1 == testGame.supplyCount[selectedCard]) {
      printf("OK:  the supply was adjusted by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] +  choice2 - 1);
   }
   else {
      printf("ERROR:  the supply was not adjusted by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] + choice2 - 1);
   }


   if (G.discardCount[nextPlayer] + 1 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the next player's discards were increased by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);

   }
   else {
      printf("ERROR:  the next player's discards did not increase by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);
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
   printf("** choice1 = 3 (copper), choice2 = 2\n");
   printf("** player returns 2 coppers to supply \n\n\n");

   G.hand[currPlayer][0] = mine;
   G.hand[currPlayer][1] = ambassador;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;


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


   choice1 = 3; // card in hand to return
   choice2 = 2; // how many cards player wants to return to supply

   selectedCard = testGame.hand[currPlayer][choice1];
   cardNumToName(selectedCard, name);
   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);

   played = testGame.playedCardCount;

   //cardEffect(ambassador, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = ambassadorEffect (choice1, choice2, &testGame, handPos, currPlayer);


   if (retError == 0) {
      printf("OK:  the return code of ambassador was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of ambassador was -1.\n\n");
   }


   if (G.handCount[currPlayer] - choice2 - 1 == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count is decreased by %d.\n", choice2 + 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }
   else {
      printf("ERROR:  the hand count was not decreased by %d.\n", choice2 + 1);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer] - choice2 - 1);
   }


   if (G.discardCount[currPlayer] + 1 == testGame.discardCount[currPlayer]) {
      printf("OK:  the number of discards increased by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }
   else {
      printf("ERROR:  the number of discards did not increase by 1.\n");
      printf("Number of discards before play = %d\n", G.discardCount[currPlayer]);
      printf("Number of discards after play = %d,  ", testGame.discardCount[currPlayer]);
      printf("Number of discards expected = %d\n\n", G.discardCount[currPlayer] + 1);
   }


   if (testGame.playedCardCount == 0) {
      printf("OK:  the played card count is 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }
   else {
      printf("ERROR:  the played card count is not 0.\n");
      printf("Number of played cards before play = %d\n", played);
      printf("Number of played cards after play = %d,  ", testGame.playedCardCount);
      printf("Number of played cards expected = %d\n\n", played);
   }


   if (G.supplyCount[selectedCard] + choice2 - 1 == testGame.supplyCount[selectedCard]) {
      printf("OK:  the supply was increased by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] + choice2 - 1);
   }
   else {
      printf("ERROR:  the supply was not increased by %d\n", choice2 - 1);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard] + choice2 - 1);
   }


   if (G.discardCount[nextPlayer] + 1 == testGame.discardCount[nextPlayer]) {
      printf("OK:  the next player's discards was increased by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);

   }
   else {
      printf("ERROR:  the next player's discards did not increase by 1\n");
      printf("Number of next player's discards before play = %d\n", G.discardCount[nextPlayer]);
      printf("Number of next player's discards after play = %d,  ", testGame.discardCount[nextPlayer]);
      printf("Number of next player's discards expected = %d\n\n", G.discardCount[nextPlayer] + 1);
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


   printf("** END TEST No. 3 *************************************************************\n\n\n\n");




   // begin testing
   printf("\n\n** BEGIN TEST No. 4 *************************************************************\n");
   printf("** choice1 = 3 (copper), choice2 = 3\n");
   printf("** player returns 2 coppers to supply \n\n\n");

   G.hand[currPlayer][0] = baron;
   G.hand[currPlayer][1] = ambassador;
   G.hand[currPlayer][2] = copper;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;


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


   choice1 = 3; // card in hand to return
   choice2 = 3; // how many cards player wants to return to supply

   selectedCard = testGame.hand[currPlayer][choice1];
   cardNumToName(selectedCard, name);
   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);

   played = testGame.playedCardCount;
   
   //cardEffect(ambassador, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = ambassadorEffect (choice1, choice2, &testGame, handPos, currPlayer);

   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[copper]);

   if (retError == 0) {
      printf("OK:  the return code of ambassador was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of ambassador was -1.\n\n");
   }

   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count was not decreased because you can't return more than 2.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count was decreased by %d, but you can't return more than 2.\n", choice2);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   if (G.supplyCount[selectedCard] == testGame.supplyCount[selectedCard]) {
      printf("OK:  the supply was not increased by %d because you can't return more than 2\n", choice2);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard]);
   }
   else {
      printf("ERROR:  the supply was increased by %d, but you can't return more than 2.\n", choice2);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard]);
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




   // begin testing
   printf("\n\n** BEGIN TEST No. 5 *************************************************************\n");
   printf("** choice1 = 1 (ambassador), choice2 = 1\n");
   printf("** player returns 1 coppers to supply \n\n\n");

   G.hand[currPlayer][0] = mine;
   G.hand[currPlayer][1] = ambassador;
   G.hand[currPlayer][2] = mine;
   G.hand[currPlayer][3] = copper;
   G.hand[currPlayer][4] = copper;


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


   choice1 = 1; // card in hand to return
   choice2 = 1; // how many cards player wants to return to supply

   selectedCard = testGame.hand[currPlayer][choice1];
   cardNumToName(selectedCard, name);
   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   played = testGame.playedCardCount;

   //cardEffect(ambassador, choice1, choice2, choice3, &testGame, handPos, &bonus);
   retError = ambassadorEffect (choice1, choice2, &testGame, handPos, currPlayer);

   //printf("supply:  %d\n\n", G.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[selectedCard]);
   //printf("supply:  %d\n\n", testGame.supplyCount[copper]);


   if (retError == 0) {
      printf("OK:  the return code of ambassador was 0.\n\n");
   }
   else if (retError == -1) {
      printf("ERROR:  the return code of ambassador was -1.\n\n");
   }


   if (G.handCount[currPlayer] == testGame.handCount[currPlayer]) {
      printf("OK:  the hand count remained the same because you can't discard the ambassador card.\n");
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer]);
   }
   else {
      printf("ERROR:  the hand count was decreased by %d.\n", choice2);
      printf("Number of cards in hand before play = %d\n", G.handCount[currPlayer]);
      printf("Number of cards in hand after play = %d,  ", testGame.handCount[currPlayer]);
      printf("Number of card in hand expected = %d\n\n", G.handCount[currPlayer]);
   }


   if (G.supplyCount[selectedCard] == testGame.supplyCount[selectedCard]) {
      printf("OK:  the supply count remained the same.\n");
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard]);
   }
   else {
      printf("ERROR:  the supply was increased by %d\n", choice2);
      printf("Number of %s in the supply before play = %d\n", name, G.supplyCount[selectedCard]);
      printf("Number of %s in the supply after play = %d,  ", name, testGame.supplyCount[selectedCard]);
      printf("Number of %s in the supply expected = %d\n\n", name, G.supplyCount[selectedCard]);
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


   printf("** END TEST No. 5 *************************************************************\n\n\n\n");



   return 0;	
}
