//
// Created by Jwam3 on 06/03/2021.
//

#include "rect.h"

struct Rect* makeRect(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {

    struct Rect* newRect = (Rect*)malloc(sizeof(struct Rect));
    struct Point* origin = (Point*)malloc(sizeof(struct Point));
    struct Size* size = (Size*)malloc(sizeof(struct Size));

    origin->x = x;
    origin->y = y;

    size->width = width;
    size->height = height;

    newRect->size = size;
    newRect->origin = origin;

    return newRect;

}

struct Point* getCenter(struct Rect* rect) {

    unsigned int centerY = rect->origin->y + (rect->size->height / 2);
    unsigned int centerX = rect->origin->x + (rect->size->width / 2);

    struct Point *centerPoint = malloc(sizeof(struct Point));
    centerPoint->x = centerX;
    centerPoint->y = centerY;

    return centerPoint;

}

/* basic rect helpers */