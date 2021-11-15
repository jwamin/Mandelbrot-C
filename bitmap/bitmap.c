//
// Created by Joss Manger on 11/15/21.
//

#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

#pragma pack(push)  // save the original data alignment
#pragma pack(1)     // Set data alignment to 1 byte boundary

typedef struct BmpHeader {
    uint16_t type;
    uint32_t sizeOfBitmapFile;
    uint32_t reservedBytes;
    uint32_t pixelDataOffset;
} BmpHeader;

typedef struct BmpInfoHeader {
    uint32_t sizeOfThisHeader;
    int32_t width;  // in pixels
    int32_t height; // in pixels
    uint16_t numberOfColorPlanes; // must be 1
    uint16_t colorDepth;
    uint32_t compressionMethod;
    uint32_t rawBitmapDataSize; // generally ignored
    int32_t horizontalResolution; // in pixel per meter
    int32_t verticalResolution; // in pixel per meter
    uint32_t colorTableEntries;
    uint32_t importantColors;
} BmpInfoHeader;

#pragma pack(pop)

typedef struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;



BmpHeader* newTestHeader() {
    BmpHeader *header = malloc(sizeof(BmpHeader));
    header->type = 0x4d42;
    header->sizeOfBitmapFile = 54 + 786432;
    header->reservedBytes = 0;
    header->pixelDataOffset = 54;
    return header;
}

BmpInfoHeader* newInfoHeader() {
    BmpInfoHeader *infoHeader = malloc(sizeof(BmpInfoHeader));
    infoHeader->sizeOfThisHeader = 40;
    infoHeader->width = 512; // in pixels
    infoHeader->height = 512; // in pixels
    infoHeader->numberOfColorPlanes = 1; // must be 1
    infoHeader->colorDepth = 24;
    infoHeader->compressionMethod = 0;
    infoHeader->rawBitmapDataSize = 0; // generally ignored
    infoHeader->horizontalResolution = 3780; // in pixel per meter
    infoHeader->verticalResolution = 3780; // in pixel per meter
    infoHeader->colorTableEntries = 0;
    infoHeader->importantColors = 0;
    return infoHeader;
}

void testBMP(){

    BmpHeader *header = newTestHeader();
    BmpInfoHeader *infoHeader = newInfoHeader();
    FILE *outBMP = fopen("test.bmp","wb");
    size_t pixels = infoHeader->width * infoHeader->height;
    size_t *numberOfPixels = malloc(sizeof pixels);
    size_t success;
    *numberOfPixels = pixels;

    //Magenta color
    Pixel *myColor = malloc(sizeof(Pixel));
    myColor->blue = 254;
    myColor->green = 100;
    myColor->red = 255;

    uint8_t b = myColor->blue;
    uint8_t g = myColor->green;
    uint8_t r = myColor->red;

    uint8_t *addr = &myColor;
    int val = addr[0];
    printf("blue: %d green: %d red: %d\n",b,g,r);
    printf("bitmap char: %c\n", header->type);

    printf("sizeof header is %lu\n",sizeof(BmpHeader));
    printf("sizeof infoheader is %lu\n",sizeof(BmpInfoHeader));

    fwrite((char*)&header, 14,1, outBMP);
    fwrite((char*)&infoHeader, 40,1, outBMP);

    printf("so we're going to write %lu things\n",*numberOfPixels);
    printf("so... header is %s \n", (char*)header);
    printf("sizeof mycolor is %lu\n",sizeof(Pixel));
    printf("const char pixel: %s\n",(char*)&myColor);

    const char* color[3] = {&b,&g,&r};
    printf("color %s\n",*color);
    for (int i = 0; i < *numberOfPixels; ++i) {
        //printf("blue: %s green: %s red: %s\n",(const char*)&b,(const char*)&g,(const char*)&r);
        //success = fwrite((char *)&color,1,3,outBMP);
//        if (success != 3){
//            exit(EXIT_FAILURE);
//        }
        fwrite((char *)&b, 1, 1, outBMP);
        fwrite((char *)&g, 1, 1, outBMP);
        fwrite((char *)&r, 1, 1, outBMP);
    }
    printf("closing file\n");
    fclose(outBMP);

}