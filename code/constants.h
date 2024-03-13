#ifndef CONSTANTS_H
#define CONSTANTS_H


const int rhoOffsets[5][5] = 
  {
    {0, 36, 3, 105, 210},
    {1, 300, 10, 45, 66},
    {190, 6, 171, 15, 253},
    {28, 55, 153, 21, 120},
    {91, 276, 231, 136, 78}
  };

// precomputed and available on the XKCP Github repository
const Lane RC[24] = 
  {
    (Lane) 0x0000000000000001,
    (Lane) 0x0000000000008082,
    (Lane) 0x800000000000808A,
    (Lane) 0x8000000080008000,
    (Lane) 0x000000000000808B,
    (Lane) 0x0000000080000001,
    (Lane) 0x8000000080008081,
    (Lane) 0x8000000000008009,
    (Lane) 0x000000000000008A,
    (Lane) 0x0000000000000088,
    (Lane) 0x0000000080008009,
    (Lane) 0x000000008000000A,
    (Lane) 0x000000008000808B,
    (Lane) 0x800000000000008B,
    (Lane) 0x8000000000008089,
    (Lane) 0x8000000000008003,
    (Lane) 0x8000000000008002,
    (Lane) 0x8000000000000080,
    (Lane) 0x000000000000800A,
    (Lane) 0x800000008000000A,
    (Lane) 0x8000000080008081,
    (Lane) 0x8000000000008080,
    (Lane) 0x0000000080000001,
    (Lane) 0x8000000080008008
  };

#endif // #ifndef CONSTANTS_H
