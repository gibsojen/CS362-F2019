#include <stdio.h>
#define DEBUG 0

#ifndef _DOMINION_EFFECTS_H
#define _DOMINION_EFFECTS_H

int ambassadorEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
);

int baronEffect(
  int choice1,
  struct gameState *state,
  int currentPlayer
);

int mineEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
);

int minionEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
);

int tributeEffect(
  struct gameState *state,
  int currentPlayer
);

#endif

int ambassadorEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
)
{
  int i;
  // used to check if player has enough cards to discard
  int j = 0;

  if (choice2 > 2)
  {
    return -1;
  }

  for (i = 0; i < state->handCount[currentPlayer]; i++)
  {
    if (
      i != handPos &&
      i == state->hand[currentPlayer][choice1] &&
      i != choice1
    )
    {
      j++;
    }
  }

  if (j < choice2)
  {
    return -1;
  }

  if (DEBUG)
  {
    printf(
      "Player %d reveals card number: %d\n",
      currentPlayer,
      state->hand[currentPlayer][choice1]
    );
  }

  // increase supply count for choosen card by amount being discarded
  state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

  // each other player gains a copy of revealed card
  for (i = 0; i < state->numPlayers; i++)
  {
    if (i != currentPlayer)
    {
      gainCard(state->hand[currentPlayer][choice1], state, 0, i);
    }
  }

  // discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);

  // trash copies of cards returned to supply
  for (j = 0; j < choice2; j++)
  {
    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
      if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
      {
        discardCard(i, currentPlayer, state, 1);
        break;
      }
    }
  }

  return 0;
}

int baronEffect(
  int choice1,
  struct gameState *state,
  int currentPlayer
)
{
  // Increase buys by 1!
  state->numBuys++;

  // Boolean true or going to discard an estate
  if (choice1 > 0)
  {
    // Iterator for hand!
    int p = 0;
    // Flag for discard set!
    int card_not_discarded = 1;

    while (card_not_discarded)
    {
      // Found an estate card!
      if (state->hand[currentPlayer][p] == estate)
      {
        // Add 4 coins to the amount of coins
        state->coins += 4;
        state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
        state->discardCount[currentPlayer]++;
        for (; p < state->handCount[currentPlayer]; p++)
        {
          state->hand[currentPlayer][p] = state->hand[currentPlayer][p + 1];
        }
        state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
        state->handCount[currentPlayer]--;
        // Exit the loop
        card_not_discarded = 0;
      }
      else if (p > state->handCount[currentPlayer])
      {
        if (DEBUG)
        {
          printf("No estate cards in your hand, invalid choice\n");
          printf("Must gain an estate if there are any\n");
        }

        gainCard(estate, state, 0, currentPlayer);

        // Decrement estates
        state->supplyCount[estate]--;

        if (supplyCount(estate, state) == 0)
        {
          isGameOver(state);
        }

        // Exit the loop
        card_not_discarded = 0;
      }
      else
      {
        // Next card
        p++;
      }
    }
  }

  else {
    // Gain an estate
    gainCard(estate, state, 0, currentPlayer);

    // Decrement Estates
    state->supplyCount[estate]--;

    if (supplyCount(estate, state) == 0)
    {
      isGameOver(state);
    }
  }


  return 0;
}

int mineEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
)
{
  int i;
  // store card we will trash
  int j = state->hand[currentPlayer][choice1];

  if (
    state->hand[currentPlayer][choice1] < copper ||
    state->hand[currentPlayer][choice1] > gold ||
    getCost(state->hand[currentPlayer][choice1]) + 3 > getCost(choice2)
  )
  {
    return -1;
  }

  gainCard(choice2, state, 2, currentPlayer);

  // discard card from hand
  discardCard(handPos, currentPlayer, state, 0);

  // discard trashed card
  for (i = 0; i < state->handCount[currentPlayer]; i++)
  {
    if (state->hand[currentPlayer][i] == j)
    {
      discardCard(i, currentPlayer, state, 0);
      break;
    }
  }

  return 0;

}

int minionEffect(
  int choice1,
  int choice2,
  int handPos,
  struct gameState *state,
  int currentPlayer
) {
  int i;
  int j;

  // +1 action
  state->numActions++;

  // discard card from hand
  discardCard(handPos, currentPlayer, state, 0);

  if (choice1)
  {
    state->coins = state->coins + 2;
  }
  // discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
  else if (choice2)
  {
    // draw 4
    for (i = 0; i < 4; i++)
    {
      discardCard(handPos, currentPlayer, state, 0);
      drawCard(currentPlayer, state);
    }

    // other players discard hand and redraw if hand size > 4
    for (i = 0; i < state->numPlayers; i++)
    {
      if (i != currentPlayer)
      {
        if (state->handCount[i] > 4)
        {
          // draw 4
          for (j = 0; j < 4; j++)
          {
            discardCard(handPos, i, state, 0);
            drawCard(i, state);
          }
        }
      }
    }
  }

  return 0;
}

int tributeEffect(
  struct gameState *state,
  int currentPlayer
)
{
  int i;
  int tributeRevealedCards[2] = {-1, -1};
  int nextPlayer = currentPlayer + 1;

  // Bug introduced in Assignment 2 removed this conditional block
  if (nextPlayer > (state->numPlayers - 1))
  {
    nextPlayer = 0;
  }

  if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1)
  {
    if (state->deckCount[nextPlayer] > 0)
    {
      tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
      state->deckCount[nextPlayer]--;
    }
    else if (state->discardCount[nextPlayer] > 0)
    {
      tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer] - 1];
      state->discardCount[nextPlayer]--;
    }
    else
    {
      // No Card to Reveal
      if (DEBUG)
      {
        printf("No cards to reveal\n");
      }
    }
  }
  else
  {
    if (state->deckCount[nextPlayer] == 0)
    {
      for (i = 0; i < state->discardCount[nextPlayer]; i++)
      {
        // Move to deck
        state->deck[nextPlayer][i] = state->discard[nextPlayer][i];
        state->deckCount[nextPlayer]++;
        state->discard[nextPlayer][i] = -1;
        state->discardCount[nextPlayer]--;
      }
      // Shuffle the deck
      shuffle(nextPlayer, state);
    }
    tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    state->deckCount[nextPlayer]--;
    tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    state->deckCount[nextPlayer]--;
  }

  for (i = 0; i <= 2; i++)
  {
    // Treasure cards
    if (
      tributeRevealedCards[i] == copper ||
      tributeRevealedCards[i] == silver ||
      tributeRevealedCards[i] == gold)
    {
      state->coins += 2;
    }
    // Victory Card Found
    else if (
      tributeRevealedCards[i] == estate ||
      tributeRevealedCards[i] == duchy ||
      tributeRevealedCards[i] == province ||
      tributeRevealedCards[i] == gardens ||
      tributeRevealedCards[i] == great_hall
    )
    {
      drawCard(currentPlayer, state);
      drawCard(currentPlayer, state);
    }
    // Action Card
    else
    {
      state->numActions = state->numActions + 2;
    }
  }

  return 0;
}
