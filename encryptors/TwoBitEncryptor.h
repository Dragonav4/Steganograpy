#ifndef STEGANOGRAPHY_TWOBITENCRYPTOR_H
#define STEGANOGRAPHY_TWOBITENCRYPTOR_H

#include "BaseEncryptor.h"

class TwoBitEncryptor : public BaseEncryptor {
public:
    int getPixelsPerByte() override {
        return 4;
    }

    int getCompressionLevel() override {
        return 1;
    }

    void writeCompressionLevel(Image* image, char compressionLevel) {
        auto pixel = image->getPixel(0,0);
        writeToPixel(pixel, compressionLevel<<6);
    }

    char readCompressionLevel(Image* image) {
        auto pixel = image->getPixel(0,0);
        return readFromPixel(pixel);
    }

private:
    const int mask=1;
    const int invertedMask =0b11111110;


    void writeToPixel(PixelColor* pixel, char value) override {
        pixel->blue = pixel->blue & invertedMask | ((value >>7)&mask);
        pixel->red = pixel->red & invertedMask | ((value >>6)&mask);
    }

    char readFromPixel(PixelColor* pixel) override {
        auto result = ((pixel->blue & mask) << 1) |
                           (pixel->red & mask);
        return result;
    }
};


#endif //STEGANOGRAPHY_TWOBITENCRYPTOR_H
