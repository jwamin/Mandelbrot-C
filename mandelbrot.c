//
// Created by Jwam3 on 07/09/2020.
//

#include <stdio.h>
#include "mandelbrot.h"

int renderPixel(FILE *fp, int xcol, int yrow, int fullWidth, int fullHeight, double offsetX, double offsetY, int maxInteration) {

    double c_re = (xcol - fullWidth/2.0)*4.0/fullWidth + offsetX;
    double c_im = (yrow - fullHeight/2.0)*4.0/fullWidth + offsetY;
    double x = 0, y = 0;
    int iteration = 0;
    while (x*x+y*y <= 4 && iteration < maxInteration) {
        double x_new = x*x - y*y + c_re;
        y = 2*x*y + c_im;
        x = x_new;
        iteration++;
    }
    if (iteration < maxInteration) {
        return iteration;
    } else {
        return 0;
    }
}
