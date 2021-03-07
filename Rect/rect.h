//
// Created by Jwam3 on 06/03/2021.
//

#ifndef BROT_RECT_H
#define BROT_RECT_H

#include <stdlib.h>

typedef struct Point {
    unsigned int x;
    unsigned int y;
} Point;

typedef struct Size {
    unsigned int width;
    unsigned int height;
} Size;

typedef struct Rect{
    struct Point *origin;
    struct Size *size;
} Rect;


/*basic rect helpers*/

struct Rect* makeRect(unsigned int x,unsigned int y,unsigned int width,unsigned int height);

struct Point* getCenter(struct Rect* rect);

#endif //BROT_RECT_H
