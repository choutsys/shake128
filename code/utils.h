#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <gmp.h>

int is_hexstring(const char *hexstring, const size_t nbytes);
void hexstring2buffer(const char *hexstr, uint8_t *buf, 
                      const size_t nbytes);
void print_buffer(const uint8_t *buf, const size_t nbytes);

#endif 
