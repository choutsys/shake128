#include "utils.h"
#include "shake128.h"

static int checkArgs(int argc, char *argv[], int *digestSize)
{
  mpz_t tmp;

  if(argc != 2)
    return 0;
  else if(mpz_init_set_str(tmp, argv[1], 10) == -1 
                          || mpz_cmp_si(tmp, 0) < 0)
  {
    mpz_clear(tmp);
    return 0;
  }
  else if(mpz_cmp_ui(tmp, 1000000) > 0)
  {
    mpz_clear(tmp);
    return 0;
  }

  *digestSize = (int) mpz_get_ui(tmp);
  mpz_clear(tmp);

  return 1;
}

static void printUsage(void)
{
  fputs("Usage  : ./shake128 N\n", stderr);
  fputs("         where N is a positive integer\n", stderr);
  fputs("         given in decimal notation.\n", stderr);
  fputs("Output : Hexadecimal representation of the first N bytes\n", 
                                                                  stderr);
  fputs("         of the SHAKE128 digest of stdin.\n", stderr);
  fputs("Please make sure N is not greater than a million.\n", stderr);
}

int main(int argc, char *argv[])
{
  uint8_t *hash;
  int digestSize;

  if(!checkArgs(argc, argv, &digestSize))
  {
    printUsage();
    exit(EXIT_FAILURE);
  }
 
  hash = malloc(digestSize);

  shake128(stdin, digestSize, hash);
  print_buffer(hash, digestSize);  

  free(hash);
  return EXIT_SUCCESS;
}
