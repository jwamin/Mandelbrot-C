#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mandelbrot.h"

#define MODULO_MAX 256

int main(int argc, const char **argv)
{
    const int width = 300, height = 300;

    int max = 100;

    static unsigned char white[3];
    white[0] = 255;  /* red */
    white[1] = 255;  /* green */
    white[2] = 255;  /* blue */
    static unsigned char black[3];
    black[0] = 0;  /* red */
    black[1] = 0;  /* green */
    black[2] = 0;  /* blue */

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

    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", width, height);

    // -4 - 4 range (double) // 0 center
    double xOffset = 0;
    double yOffset = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            int iteration = renderPixel(fp,col,row,width,height,xOffset,yOffset,max);

            if ( iteration > 0 ) {
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
    (void) fclose(fp);
    return EXIT_SUCCESS;
}
