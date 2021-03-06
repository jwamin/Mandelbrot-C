//
// Created by Jwam3 on 06/03/2021.
//

#include "brot.h"

#define ITERATION_MAX 100

#define min(a, b) ((a) < (b) ? (a) : (b))

static unsigned char black[3] = {0,0,0};
static unsigned char white[3] = {255,255,255};

/// drawEntireSet - draw mandelbrot set within the bounds provided
/// \param fp output file pointer writable binary
/// \param width the width of the set in px
/// \param height the height of the set in px
/// \param r the red color base for this rendering 0-255
/// \param g the green color base for this rendering 0-255
/// \param b the blue color base for this rendering 0-255
void drawEntireSet(FILE *fp, int width, int height, uint r, uint g, uint b){

    (void) fprintf(fp, "P6\n%d %d\n255\n", width, height);

    int randomR = r;
    int randomB = b;
    int randomG = g;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
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

                other[0] = randomR * increase;  /* red */
                other[1] = randomG * increase;  /* green */
                other[2] = randomB * increase;  /* blue */

                (void) fwrite(other, 1, 3, fp);
            } else {
                (void) fwrite(black, 1, 3, fp);
            }
        }
    }

}

void* generateSquareDimensions(int xDimension, int yDimension){

    int maxX = 100;
    int maxY = 100;

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

/// createSquare
/// creates a PPM string for given dimensions
/// \param maxX the the width of the full mandelbrot set image
/// \param maxY the height of the full mandelbrot set image
/// \param originX the origin horizontal pixel of the sub rect of mandelbrot set we are rendering
/// \param originY the origin vertical pixel of the sub rect of mandelbrot set we are rendering
/// \param dimensionX the width of the drawing region of mandelbrot set
/// \param dimensionY the height of the drawing region of mandelbrot set
/// \param r the red color base for this rendering 0-255
/// \param g the green color base for this rendering 0-255
/// \param b the blue color base for this rendering 0-255
void createSquare(int maxX, int maxY, int originX, int originY, int dimensionX, int dimensionY, uint r, uint g, uint b){

    printf("will create a square at x:%d y:%d, with dimension x: %d, y:%d, r %d, g %d b %d\n", originX, originY, dimensionX, dimensionY, r, g, b);
    printf("the entire set is contained withing width: %d, height:%d\n",maxX,maxY);
    printf("x:%d to %d, y:%d to %d\n", originX, originX+dimensionX, originY, originY+dimensionY);

    //create ppm with dimensions

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