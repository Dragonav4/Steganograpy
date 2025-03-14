#ifndef STEGANOGRAPHY_FOURBITENCRYPTOR_H
#define STEGANOGRAPHY_FOURBITENCRYPTOR_H


#include "BaseEncryptor.h"

class FourBitEncryptor : public BaseEncryptor {
public:
    int getPixelsPerByte() override{
        return 2;
    }
    int getCompressionLevel() override {
        return 2;
    }
private:
    const int mask1bit = 0b1;
    const int mask2bit = 0b11;

    void writeToPixel(PixelColor* pixel, char value) override {
        pixel->red = (pixel->red & ~mask1bit) | ((value>>7)&mask1bit);
        pixel->green = (pixel->green & ~mask1bit) | ((value>>6)&mask1bit);
        pixel->blue = (pixel->blue & ~mask2bit) | ((value >> 4)&mask2bit);
    }

    char readFromPixel(PixelColor* pixel) override {
        return (pixel->red & mask1bit) << 3 |
               (pixel->green & mask1bit) << 2 |
               (pixel->blue & mask2bit);
    }
};


#endif //STEGANOGRAPHY_FOURBITENCRYPTOR_H
