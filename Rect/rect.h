//
// Created by Jwam3 on 06/03/2021.
//

#ifndef BROT_RECT_H
#define BROT_RECT_H

#include <stdlib.h>

typedef struct Point {
    uint x;
    uint y;
} Point;

typedef struct Size {
    uint width;
    uint height;
} Size;

typedef struct Rect{
    struct Point *origin;
    struct Size *size;
} Rect;


/*basic rect helpers*/

struct Rect* makeRect(uint x,uint y,uint width,uint height);

struct Point* getCenter(struct Rect* rect);

#endif //BROT_RECT_H
