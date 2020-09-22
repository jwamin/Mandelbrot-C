#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MODULO_MAX 256
#define ITERATION_MAX 100

#define min(a, b) ((a) < (b) ? (a) : (b))

void createSquare(int x, int y, int dimensionX, int dimensionY, int r, int g, int b);

static unsigned char black[3];
static unsigned char white[3];

static int width = 10000;
static int height = 10000;

int main(int argc, const char **argv)
{
    const int width = 301, height = 301;

    const int xDimension = 50, yDimension = 50;



    time_t t;

    //seed random
    srand((unsigned)time(&t));

    //generate random red green and blue sub colors
    int randomR = rand() % MODULO_MAX;
    int randomG = rand() % MODULO_MAX;
    int randomB = rand() % MODULO_MAX;

    //suggested algorithm
    //"dictionary" - if iteration encountered before, get color
    // if not, generate new color

    createSquare(1200,5000,1000,1000,randomR,randomG,randomB);

    //We are returning here
    return EXIT_SUCCESS;


    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", width, height);

    // -4 - 4 range (double) // 0 center
    double xOffset = 0;
    double yOffset = 0;

    //divide up the full canvas into x/yDimension increments, any remainder, make that size

    int currentX, currentY = 0;
    int testX, testY = 0;
    int testDimensionX, testDimensionY = 0;


    // y outer
    while (currentY < height) {

        testY += yDimension;
        testDimensionY = yDimension;

        if (testY >= height) {
            testY = height;
            //update yDimension
            testDimensionY = height - currentY;
        }

        testDimensionY = min(yDimension, testDimensionY);

        //x inner
        while (currentX < width) {

            testX += xDimension;

            testDimensionX = min(xDimension, testDimensionX);

            if (testX >= width) {
                testX = width;

                //update xDimension
                testDimensionX = width - currentX;

            }

            createSquare(currentX,currentY,testDimensionX,testDimensionY,randomR,randomB,randomG);

            currentX = testX;

        }

        currentY = testY;

        testDimensionX = 0;
        currentX = 0;
        testX = 0;

        printf("returning\n");
    }


    (void) fclose(fp);
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


void createSquare(int x,int y,int dimensionX, int dimensionY ,int r, int g, int b){

    printf("will create a square at x:%d y:%d, with dimension x: %d, y:%d, r %d, g %d b %d\n", x, y, dimensionX, dimensionY, r, g, b);

    printf("x:%d to %d, y:%d to %d\n", x, x+dimensionX, y, y+dimensionY);

    //create ppm with dimensions


    white[0] = 255;  /* red */
    white[1] = 255;  /* green */
    white[2] = 255;  /* blue */

    black[0] = 0;  /* red */
    black[1] = 0;  /* green */
    black[2] = 0;  /* blue */

    FILE *fp = fopen("test.ppm", "wb");
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimensionX, dimensionY);

    int dimensionXMax = x + dimensionX;
    int dimensionYMax = y + dimensionY;

    for (int row = y; row < dimensionYMax; row++) {
        for (int col = x; col < dimensionXMax; col++) {
            double c_re = (col - width/2.0)*4.0/width;
            double c_im = (row - height/2.0)*4.0/width;
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