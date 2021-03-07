#include <stdlib.h>

//#ifndef arc4random_uniform
//#include <bsd/stdlib.h>
//#endif

#include <stdio.h>
#include "brot/brot.h"
#include "Rect/rect.h"
#include <assert.h>


#define MODULO_MAX 256

int main(int argc, const char **argv)
{

    //Tile dimensions
    const int xDimension = 50, yDimension = 50;
    unsigned int randomR, randomG, randomB;
    int* intptr;

    //generate random, but consistent red green and blue sub colors
    randomR = arc4random_uniform(255);
    randomG = arc4random_uniform(255);
    randomB = arc4random_uniform(255);

    printf("random r:%d g:%d b:%d\n",randomR,randomG,randomB);

    //suggested algorithm
    //"dictionary" - if iteration encountered before, get color
    // if not, generate new color

    //Main Routine

    /*
     * Complete Set
     */
    //Draw set within bounds

    //Create file pointer
    FILE *testFile = fopen("mytestfullset.ppm","wb");
    //draw grayscale set within bounds
    drawEntireSet(testFile,300,300,255,255,255);

    /*
    *  Draw partial rect of set (zoom, pan effect)
    */
    //Defined bounds of set
    createSquare(200,200,0,0,200,200, randomR, randomG, randomB);

    /*
     * Generate Rects for partial rendering, such as with threading or hardware accelleration
     */
    int* myintPtr = generateSquareDimensions(1000,1000);


    //Get the point?
    Rect *myRect = makeRect(0,0,100,100);
    Point *center = getCenter(myRect);

    assert(center->x == 50);
    assert(center->y == 50);

    //We are returning here
    return EXIT_SUCCESS;

}