//
// Created by Jwam3 on 07/09/2020.
//

#ifndef BROT_MANDELBROT_H
#define BROT_MANDELBROT_H

int renderPixel(FILE *fp, int xcol, int yrow, int fullWidth, int fullHeight, double offsetX, double offsetY, int maxInteration);

void getDimensionsForTile(int tileDimension, int fullWidth, int fullHeight);

#endif //BROT_MANDELBROT_H
