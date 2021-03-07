//
// Created by Jwam3 on 06/03/2021.
//

#ifndef BROT_BROT_H
#define BROT_BROT_H

#include <stdlib.h>
#include <stdio.h>

void drawEntireSet(FILE *fp, int width, int height, unsigned int r, unsigned int g, unsigned int b);
void createSquare(int maxX, int maxY, int originX, int originY, int dimensionX, int dimensionY, unsigned int r, unsigned int g, unsigned int b);
void* generateSquareDimensions(int xDimension, int yDimension);

#endif //BROT_BROT_H
