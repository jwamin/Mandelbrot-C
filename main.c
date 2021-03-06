#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MODULO_MAX 256
#define ITERATION_MAX 100

#define min(a, b) ((a) < (b) ? (a) : (b))

void createSquare(int maxX, int maxY, int originX, int originY, int dimensionX, int dimensionY, int r, int g, int b);
void* generateSquareDimensions(int xDimension, int yDimension);

static unsigned char black[3];
static unsigned char white[3];

static int maxX = 100;
static int maxY = 100;

int main(int argc, const char **argv)
{

    //Tile dimensions
    const int xDimension = 50, yDimension = 50;
    int randomR, randomG, randomB;
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

    createSquare(200,200,0,0,1000,1000,randomR,randomG,randomB);

    //We are returning here
    return EXIT_SUCCESS;

}


void drawEntireSet(FILE *fp, int width, int height, int xOff, int yOff, int r, int g, int b){

    int xOffset = xOff | 0;
    int yOffset = yOff | 0;

    int randomR = r;
    int randomB = b;
    int randomG = g;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            double c_re = (col - width/2.0)*4.0/width + xOffset;
            double c_im = (row - height/2.0)*4.0/width + yOffset;
            double x = 0, y = 0;
            int iteration = 0;
            while (x*x+y*y <= 4 && iteration < ITERATION_MAX) {
                double x_new = x*x - y*y + c_re;
                y = 2*x*y + c_im;
                x = x_new;
                iteration++;
            }
            if (iteration < ITERATION_MAX) {
                int increase = iteration * 100;
                static unsigned char other[3];

                other[0] = randomR * increase;  /* red */
                other[1] = randomG * increase;  /* green */
                other[2] = randomB * increase;  /* blue */

                //printf("iteration: %d other: r:%d, g:%d, b:%d\n",iteration,other[0],other[1],other[2]);
                (void) fwrite(other, 1, 3, fp);
            } else {
                (void) fwrite(black, 1, 3, fp);
            }
        }
    }

}

void* generateSquareDimensions(int xDimension, int yDimension){

    // -4 - 4 range (double) // 0 center
    double xOffset = 0;
    double yOffset = 0;

    //divide up the full canvas into x/yDimension increments, any remainder, make that size

    int currentX = 0, currentY = 0;
    int testX = 0, testY = 0;
    int testDimensionX = 0, testDimensionY = 0;

    // y outer
    while (currentY < maxY) {

        testY += yDimension;
        testDimensionY = yDimension;

        if (testY >= maxY) {
            testY = maxY;
            //update yDimension
            testDimensionY = maxY - currentY;
        }

        testDimensionY = min(yDimension, testDimensionY);

        //x inner
        while (currentX < maxX) {

            testX += xDimension;

            testDimensionX = min(xDimension, testDimensionX);

            if (testX >= maxX) {
                testX = maxX;

                //update xDimension
                testDimensionX = maxX - currentX;

            }

            printf("x: %d y: %d xD: %d yD: %d \n",currentX,currentY,testDimensionX,testDimensionY);

            //we would call threaded draw function here?

            currentX = testX;

        }

        currentY = testY;

        testDimensionX = 0;
        currentX = 0;
        testX = 0;

        printf("returning\n");

    }

    return malloc(sizeof(int));

}


void createSquare(int maxX, int maxY, int originX, int originY, int dimensionX, int dimensionY, int r, int g, int b){

    printf("will create a square at x:%d y:%d, with dimension x: %d, y:%d, r %d, g %d b %d\n", originX, originY, dimensionX, dimensionY, r, g, b);
    printf("the entire set is contained withing width: %d, height:%d\n",maxX,maxY);
    printf("x:%d to %d, y:%d to %d\n", originX, originX+dimensionX, originY, originY+dimensionY);

    //create ppm with dimensions

    white[0] = 255;  /* red */
    white[1] = 255;  /* green */
    white[2] = 255;  /* blue */

    black[0] = 0;  /* red */
    black[1] = 0;  /* green */
    black[2] = 0;  /* blue */

    FILE *fp = fopen("test.ppm", "wb");
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimensionX, dimensionY);

    int dimensionXMax = originX + dimensionX;
    int dimensionYMax = originY + dimensionY;

    for (int row = originY; row < dimensionYMax; row++) {
        for (int col = originX; col < dimensionXMax; col++) {
            double c_re = (col - maxX / 2.0) * 4.0 / maxX;
            double c_im = (row - maxY / 2.0) * 4.0 / maxX;
            double x = 0, y = 0;
            int iteration = 0;
            while (x*x+y*y <= 4 && iteration < ITERATION_MAX) {
                double x_new = x*x - y*y + c_re;
                y = 2*x*y + c_im;
                x = x_new;
                iteration++;
            }
            if (iteration < ITERATION_MAX) {
                int increase = iteration * 100;
                static unsigned char other[3];

                other[0] = r * increase;  /* red */
                other[1] = g * increase;  /* green */
                other[2] = b * increase;  /* blue */

                //printf("iteration: %d other: r:%d, g:%d, b:%d\n",iteration,other[0],other[1],other[2]);
                (void) fwrite(other, 1, 3, fp);
            } else {
                (void) fwrite(black, 1, 3, fp);
            }
        }
    }

    (void) fclose(fp);
    //render mandelbrot, in the dimensions specified, with offset

}