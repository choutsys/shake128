#ifndef SPONGE_H
#define SPONGE_H

void absorb(FILE* message, Lane state[WIDTH]);
void squeeze(Lane state[WIDTH], int digestSize, uint8_t *digest);

#endif // #ifndef SPONGE_H
