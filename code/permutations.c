#include "state.h"     // state dimensions and Lane type
#include "constants.h" // RC and rho offsets
#include "permutations.h" 

#define A(x, y)		    state[5*y + x]                  // state2stateArray
#define A_TEMP(x, y)	stateBckp[5*y + x]              
#define SAVE_STATE()	for(int i = 0; i < WIDTH; i++) \
                        stateBckp[i] = state[i];

// global backupArray for memory efficiency
Lane stateBckp[WIDTH];

// adapted from https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
static Lane rotate(Lane lane, int offset)
{
  return (lane << offset)|(lane >> (LANE_SIZE - offset));
}

static void theta(Lane state[WIDTH])
{	
	// xor lanes along y and store 5 squeezed lanes in one line of A_TEMP
  for(int x = 0; x < 5; x++)
    A_TEMP(x, 0) = A(x, 0)^A(x, 1)^A(x, 2)^A(x, 3)^A(x, 4);
	
	// rotate these 5 lanes by one bit and store them in another line
  for(int x = 0; x < 5; x++)
    A_TEMP(x, 1) = rotate(A_TEMP(x, 0), 1); 
	
	// xor each lane of the state with adjacent squeezed lanes
  for(int x = 0; x < 5; x++)
    for(int y = 0; y < 5; y++)
      A(x, y) ^= A_TEMP(x > 0 ? x - 1 : 4, 0)^A_TEMP((x + 1)%5, 1);
}

static void rho(Lane state[WIDTH])
{
  for(int x = 0; x < 5; x++)
    for(int y = 0; y < 5; y++)
      A(x, y) = rotate(A(x, y), rhoOffsets[x][y]%LANE_SIZE);
}

static void pi(Lane state[WIDTH])
{
  SAVE_STATE()
  for(int x = 0; x < 5; x++)
    for(int y = 0; y < 5; y++)
      A(x, y) = A_TEMP((x + 3*y)%5, x);
}

static void chi(Lane state[WIDTH])
{
  SAVE_STATE()
  for(int x = 0; x < 5; x++)
    for(int y = 0; y < 5; y++)
      A(x, y) ^= (~A_TEMP((x + 1)%5, y))&A_TEMP((x + 2)%5, y);
}

static void iota(Lane state[WIDTH], int roundIndex)
{
  A(0, 0) ^= RC[roundIndex]; 
}

static void rnd(Lane state[WIDTH], int roundIndex)
{
  theta(state);
  rho(state);
  pi(state);
  chi(state);
  iota(state, roundIndex);
}

void keccak_p(Lane state[WIDTH])
{
  for(int i = 0; i < N_ROUNDS; i++)
    rnd(state, i);
}

