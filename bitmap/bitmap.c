//
// Created by Joss Manger on 11/15/21.
//

#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//https://codereview.stackexchange.com/questions/196084/read-and-write-bmp-file-in-c

#pragma pack(push)  // save the original data alignment
#pragma pack(1)     // Set data alignment to 1 byte boundary

typedef struct BmpHeader {
    uint16_t type;
    uint32_t sizeOfBitmapFile;
    uint32_t reservedBytes;
    uint32_t pixelDataOffset;
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
} BmpHeader;

#pragma pack(pop)

typedef struct BmpImage {
    BmpHeader header;
    unsigned char* data;
} BmpImage;



typedef struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;



BmpHeader* newHeader() {
    BmpHeader *header = malloc(sizeof(BmpHeader));
    header->type = 0x4d42;
    header->sizeOfBitmapFile = 54 + 786432;
    header->reservedBytes = 0;
    header->pixelDataOffset = 54;
    header->sizeOfThisHeader = 40;
    header->width = 512; // in pixels
    header->height = 512; // in pixels
    header->numberOfColorPlanes = 1; // must be 1
    header->colorDepth = 24;
    header->compressionMethod = 0;
    header->rawBitmapDataSize = 0; // generally ignored
    header->horizontalResolution = 3780; // in pixel per meter
    header->verticalResolution = 3780; // in pixel per meter
    header->colorTableEntries = 0;
    header->importantColors = 0;
    return header;
}

void testBMP(){

    BmpHeader *header = newHeader();

    FILE *outBMP = fopen("test.bmp","wb");
    char* data = malloc(sizeof(char) * (header->sizeOfBitmapFile * 10));
    size_t pixels = header->width * header->height;
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
    printf("sizeof infoheader is %lu\n",sizeof(BmpHeader));

    fwrite((char*)&header, 54,1, outBMP);

    printf("so we're going to write %lu things\n",*numberOfPixels);
    printf("so... header is %s \n", (char*)header);
    printf("sizeof mycolor is %lu\n",sizeof(Pixel));
    printf("const char pixel: %s\n",(char*)&myColor);

    const char* color[3] = {&b,&g,&r};
    char* test = malloc(sizeof(char) * 3);
    printf("color %s\n",*color);
    for (int i = 0; i < pixels; ++i) {
        sprintf(test,"%s%s%s",(const char*)&b,(const char*)&g,(const char*)&r);
        strcat(data,test);
//        strcat(data,(const char*)&b);
//        strcat(data,(const char*)&g);
//        strcat(data,(const char*)&r);
//        fwrite((char *)&b, 1, 1, outBMP);
//        fwrite((char *)&g, 1, 1, outBMP);
//        fwrite((char *)&r, 1, 1, outBMP);
    }

    BmpImage *image = malloc(sizeof(BmpImage));
    image->header = *header;
    image->data = malloc(sizeof data);
    image->data = *data;

    fwrite(&header, sizeof(BmpHeader),1,outBMP);
    printf("data %c\n",*data);
    printf("sizeof header %lu\n",sizeof &header);
    printf("sizeof data %lu\n", strlen(data) * sizeof(char));
    fwrite(&data, sizeof data,1,outBMP);
    printf("closing file\n");
    fclose(outBMP);

}