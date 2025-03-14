#ifndef STEGANOGRAPHY_BMPIMAGESTUFF_H
#define STEGANOGRAPHY_BMPIMAGESTUFF_H

typedef unsigned char uchar;
typedef unsigned int uint32; //typedef // 32bit = 4bytes like in int
typedef unsigned short int uint16; //some field are 2 bytes that why we cannot use just int(4bytes)
const int BmpMarkLength=2;

struct bmpFileMark
{
    uchar bmpFileMark[BmpMarkLength]; // for "BM" as watermark of BMP file
};

struct bmpFileHeader
{
    uint32 fileSize;
    uint16 creator1;
    uint16 creator2;
    uint32 bmpOffset;
};

struct bmpFileDibInfo
{
    int header_size;
    int width;
    int height;
    uint16 numPlanes;
    uint16 bitsPerPixel;
    uint32 compression;
    uint32 bmpByteSize;
    int hres;
    int vres;
    uint32 numColors;
    uint32 numImportantColors;
};
#endif //STEGANOGRAPHY_BMPIMAGESTUFF_H
