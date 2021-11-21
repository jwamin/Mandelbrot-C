//
// Created by Joss Manger on 11/15/21.
//

#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

//https://codereview.stackexchange.com/questions/196084/read-and-write-bmp-file-in-c

unsigned char* _createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
            0,0,     /// signature
            0,0,0,0, /// image file size in bytes
            0,0,0,0, /// reserved
            0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* _createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
            0,0,0,0, /// header size
            0,0,0,0, /// image width
            0,0,0,0, /// image height
            0,0,     /// number of color planes
            0,0,     /// bits per pixel
            0,0,0,0, /// compression
            0,0,0,0, /// image size
            0,0,0,0, /// horizontal resolution
            0,0,0,0, /// vertical resolution
            0,0,0,0, /// colors in color table
            0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return infoHeader;
}

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
    myColor->blue = 255;
    myColor->green = 100;
    myColor->red = 255;

    uint8_t b = myColor->blue;
    uint8_t g = myColor->green;
    uint8_t r = myColor->red;

    uint8_t *addr = &myColor;
    int val = addr[0];
    printf("blue: %d green: %d red: %d\n",b,g,r);
    printf("bitmap char: %c\n", header->type);



    //fwrite((char*)&header, 54,1, outBMP);

    printf("so we're going to write %lu things\n",*numberOfPixels);
    printf("so... header is %s \n", (char*)header);
    printf("sizeof mycolor is %lu\n",sizeof(Pixel));
    printf("const char pixel: %s\n",(char*)&myColor);

    printf("will write:\n");
    printf("%s\n",(unsigned char*)header);
    printf("sizeof header is %lu\n",sizeof(BmpHeader));
    printf("value per pixel: %s\n",(unsigned char*)myColor);


    unsigned char padding[3] = {0, 0, 0};

    int height = 300;
    int width = 300;
    int widthInBytes = width * BYTES_PER_PIXEL;
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = width + paddingSize;

    unsigned char* fileHeader = _createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, outBMP);

    unsigned char* infoHeader = _createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, outBMP);

    int i;
    unsigned char* charMyColor = (unsigned char*)myColor;
    for (i = 0; i < header->height; i++) {
        for (int l = 0; l < header->width; ++l) {
            for (int j = 0; j < BYTES_PER_PIXEL; ++j) {
                fwrite((unsigned char*)&charMyColor[j], 1,1,outBMP);
            }
                //fwrite((unsigned char*)myColor, sizeof(Pixel),1,outBMP);
                //printf("%s ",myColor);

        }
        fwrite(padding, 1,paddingSize,outBMP);
    }

    printf("closing file\n");
    fclose(outBMP);

}