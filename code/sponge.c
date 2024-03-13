#include "utils.h"
#include "state.h" 	  // state dimensions and Lane type definition
#include "permutations.h" // keccak permutation function
#include "sponge.h" 


void squeeze(Lane state[WIDTH], int digestSize, uint8_t *digest)
{
  int squeezes; // number of squeezes necessary
  int rate;     // in bytes
  
  squeezes = (digestSize*8)/(LANE_SIZE*RATE) + 1; 
  rate = RATE*LANE_SIZE/8;

  for(int i = 0; i < squeezes - 1; i++)
  {/*
    mpz_mul_2exp(digest, digest, RATE*LANE_SIZE); // room for squeeze;
    mpz_import(tmp, RATE, 1, LANE_SIZE/8, 1, 0, state); // lanes -> bignum
    mpz_add(digest, digest, tmp); // append that bignum to the digest
    */
    memcpy(&digest[i*rate], (uint8_t *) state, rate);
    keccak_p(state); // squeeze next RATE Lanes
  }

  if((squeezes - 1)*rate < digestSize)
    memcpy(&digest[(squeezes - 1)*rate], (uint8_t *) state,
                                        digestSize - (squeezes - 1)*rate);
}


static void xor(Lane state[WIDTH], Lane buffer[RATE])
{
  for(int i = 0; i < RATE; i++)
    state[i] ^= buffer[i];
}

static void absorbPadding(unsigned char buffer[RATE*8], 
                                   Lane state[WIDTH], int bytesRead)
{
  unsigned char leadingOnes = 0x1f; // pad with byte = 0001 1111
  buffer[bytesRead] = leadingOnes;
  buffer[RATE*8 - 1] = 1 << 7; // pad with closing 
  xor(state, (Lane *) buffer);
  keccak_p(state);
}

void absorb(FILE *message, Lane state[WIDTH])
{
  int bytesRead = 0; // bytes read into single chunk of RATE lanes
  unsigned char buffer[RATE*8] = {0};
  
  while((bytesRead = fread(buffer, 1, RATE*8, message)) == RATE*8)
  {
    xor(state, (Lane *) buffer);
    keccak_p(state);
    for(int i = 0; i < RATE*8;i++)
      buffer[i] = 0;
  }

  absorbPadding(buffer, state, bytesRead); 
}
