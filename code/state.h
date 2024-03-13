#ifndef STATE_H
#define STATE_H

#include <inttypes.h>

#define LANE_SIZE 64   // w in FIPS 202, LANE_SIZE = w

// Unit : Lanes
#define WIDTH     25   // b in FIPS 202, WIDTH = b/LANE_SIZE = 25 
#define CAPACITY  4    // c in FIPS 202, CAPACITY = c/LANE_SIZE
#define RATE      21   // r in FIPS 202, r = b - c, RATE = 25 - CAPACITY 

#define N_ROUNDS  24   // l in FIPS 202, N_ROUNDS = 12 + 2*l 

typedef uint64_t Lane; // w in FIPS 202, Lane = uint[w]_t

#endif // #ifndef STATE_H
