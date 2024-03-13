#include "utils.h"
#include "state.h"  // Ensure that macros match b,w,l,c=1600,64,6,256  
#include "sponge.h" //absorb, squeeze
#include "shake128.h"

int shake128(FILE *message, int digestSize, uint8_t *hash)
{
  Lane state[WIDTH] = {0};
  
  if(digestSize <= 0 || digestSize > 1000000)
  {
    fputs("Cannot compute digests of that size.\n", stderr);
    return -1;
  }

  if(message == NULL)
  {
    fputs("Unreadable stream of bytes.\n", stderr);
    return -1;
  }

  absorb(message, state);
  squeeze(state, digestSize, hash);

  return 0;
}
