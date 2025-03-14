#ifndef STEGANOGRAPHY_ONEBITENCRYPTOR_H
#define STEGANOGRAPHY_ONEBITENCRYPTOR_H


#include "BaseEncryptor.h"

class OneBitEncryptor : public BaseEncryptor  {
public:
    int getPixelsPerByte() override {
        return 8;
    }
    int getCompressionLevel() override {
        return 0;
    }
private:
    const int mask = 1;
    const int invertedMask = ~mask;


    void writeToPixel(PixelColor* pixel, char value) override {
        auto upperBit = (value >> 8) & mask; // put mask to upper bit
        pixel->blue = pixel->blue & invertedMask | upperBit;
    }

    char readFromPixel(PixelColor* pixel) override {
        return pixel->blue & 0b00000001;
    }
};




#endif //STEGANOGRAPHY_ONEBITENCRYPTOR_H
