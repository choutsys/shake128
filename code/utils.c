#include "utils.h"

int is_hexstring(const char *hexstring, const size_t nbytes)
{
  size_t len;

  len = strlen(hexstring);

  if(len != nbytes*2)
    return 0;

  for(size_t i = 0; i < len; i++)
  {
    if((hexstring[i] < '0') || 
      (hexstring[i] > '9' && hexstring[i] < 'A') ||
      (hexstring[i] > 'F' && hexstring[i] < 'a') ||
      (hexstring[i] > 'f'))
      return 0;
  }

  return 1;
}

void hexstring2buffer(const char *hexstr, uint8_t *buf, 
                      const size_t nbytes)
{
  for(size_t i = 0; i < nbytes; i++)
    sscanf(&hexstr[2*i], "%02hhx", &buf[i]);
}


void print_buffer(const uint8_t *buf, const size_t nbytes)
{
  for(size_t i = 0; i < nbytes; i++)
    printf("%02hhx", buf[i]);
  printf("\n");
}

