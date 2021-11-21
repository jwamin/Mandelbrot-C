//
// Created by Joss Manger on 11/16/21.
//

#include "bitmap-copy.h"

//https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

#include <stdio.h>
#include <stdlib.h>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(unsigned char*** image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);


int createTestBMP ()
{
    int height = 100;
    int width = 200;
    size_t sizeOfImage = height * width;

    unsigned char*** image = malloc( sizeof image * height);

    int i, j;
    for (i = 0; i < height; i++)
    {
        image[i] = malloc(sizeof *image[i] * width);
        for (j = 0; j < width; j++) {
            image[i][j] = (unsigned char*)malloc(sizeof(char) * BYTES_PER_PIXEL);
        }

    }

    char* imageFileName = (char*) "bitmapImage.bmp";

    unsigned char* colorAtIndex;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            image[i][j][2] = 255;//(unsigned char) ( i * 255 / height );             ///red
            image[i][j][1] = 0;//(unsigned char) ( j * 255 / width );              ///green
            image[i][j][0] = 255;//(unsigned char) ( (i+j) * 255 / (height+width) ); ///blue
        }
    }
    printf("0 array subscript access\nimage pointer: %p\n",image);
    printf("int cast - first index: b:%d g:%d r:%d\n",(unsigned int)image[0][0][0],(unsigned int)image[0][0][1],(unsigned int)image[0][0][2]);
    printf("pointers - first index: b:%p g:%p r:%p\n",&image[0][0][0],&image[0][0][1],&image[0][0][2]);

    printf("1 array subscript access\nimage pointer: %p\n",image);
    printf("int cast - first index: b:%d g:%d r:%d\n",(unsigned int)image[0][1][0],(unsigned int)image[0][1][1],(unsigned int)image[0][1][2]);
    printf("pointers - first index: b:%p g:%p r:%p\n",&image[0][1][0],&image[0][1][1],&image[0][1][2]);

    printf("pointer address access\n");
    printf("pointer - first index: b:%d g:%d r:%d\n", (unsigned int)*(&***(image)+ sizeof(char) * 0), (unsigned int)*(&***(image)+ sizeof(char) * 1), (unsigned int)*(&***(image)+ sizeof(char) * 2));

    printf("pointers - first index: b:%p g:%p r:%p\n",&***(image) + sizeof(char) * 0, &***(image)+ sizeof(char) * 1, &***(image)+ sizeof(char) * 2);

    printf("Info\nSize of unsigned char: %lu\nSize of unsigned int: %lu\n", sizeof(unsigned char), sizeof(unsigned int));

    printf("loop test\n");

    unsigned char* row;
    for (int k = 0; k < width; ++k) {
        row = &***(image) + (k * (width+1)) ;
        for (int l = 0; l < BYTES_PER_PIXEL; ++l) {
            printf("%d ",(unsigned int)*(&*row+ sizeof(char) * l));
        }
        printf("\n");
        for (int l = 0; l < BYTES_PER_PIXEL; ++l) {
            printf("%p ",&*row+ sizeof(char) * l);
        }
        printf("\n");
    }
    printf("\ndone...\n");


    generateBitmapImage(image, height, width, imageFileName);
    free(image);
    printf("Image generated!!");

    return 0;

}


void generateBitmapImage (unsigned char*** image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(imageFileName, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        for (int l = 0; l < width; ++l) {
            for (int j = 0; j < BYTES_PER_PIXEL; ++j) {
                fwrite((unsigned char*)&image[i][l][j], sizeof(unsigned char), 1, imageFile);
                //printf("%d ",(unsigned int)*&image[i][l][j]);
            }
            printf(" - ");
        }
        printf("\n");
        //fwrite(row, BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader (int height, int stride)
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

unsigned char* createBitmapInfoHeader (int height, int width)
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