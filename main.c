#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "brot/brot.h"

#define MODULO_MAX 256

int main(int argc, const char **argv)
{

    //Tile dimensions
    const int xDimension = 50, yDimension = 50;
    uint randomR, randomG, randomB;
    int* intptr;

    //seed random for color generation
    time_t t;
    srand((unsigned)time(&t));

    //generate random, but consistent red green and blue sub colors
    randomR = rand() % MODULO_MAX;
    randomG = rand() % MODULO_MAX;
    randomB = rand() % MODULO_MAX;

    //suggested algorithm
    //"dictionary" - if iteration encountered before, get color
    // if not, generate new color

    intptr = generateSquareDimensions(xDimension,yDimension);

    free(intptr);

    createSquare(200,200,0,0,200,200, randomR, randomG, randomB);

    //We are returning here
    return EXIT_SUCCESS;

}