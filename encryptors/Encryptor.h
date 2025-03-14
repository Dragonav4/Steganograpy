#ifndef STEGANOGRAPHY_ENCRYPTOR_H
#define STEGANOGRAPHY_ENCRYPTOR_H


#include "OneBitEncryptor.h"
#include "TwoBitEncryptor.h"
#include "FourBitEncryptor.h"
#include "stdexcept"

class Encryptor {
public:
    static void encrypt(Image* image, const string& text) {
        auto encryptor = getEncryptor(image, text);
        if (encryptor == nullptr)
            throw std::logic_error("Message is too big to fit in the given image");
        twoBitEncryptor.writeCompressionLevel(image, encryptor->getCompressionLevel());
        encryptor->encrypt(image, text);
    }

    static string decrypt(Image* image) {
        auto decryptor = getDecryptor(image);
        if (decryptor == nullptr)
            throw std::logic_error("Can't find specific encoder (or file is not encoded)");
        return decryptor->decrypt(image);
    }

    static BaseEncryptor* getEncryptor(Image* image, const string& text) {
        auto textSize = text.size();
        auto messageSize = textSize + sizeof(int);
        auto totalPixels = image->getWidth() * image->getHeight();
        if (totalPixels > messageSize * oneBitEncryptor.getPixelsPerByte()+1)
            return &oneBitEncryptor;
        if (totalPixels > messageSize * twoBitEncryptor.getPixelsPerByte()+1)
            return &twoBitEncryptor;
        if (totalPixels > messageSize * fourBitEncryptor.getPixelsPerByte()+1)
            return &fourBitEncryptor;
        return nullptr;
    }

private:
    static inline OneBitEncryptor oneBitEncryptor;
    static inline TwoBitEncryptor twoBitEncryptor;
    static inline FourBitEncryptor fourBitEncryptor;


    static BaseEncryptor* getDecryptor(Image* image) {
        auto decryptorIndex = twoBitEncryptor.readCompressionLevel(image);
        if (oneBitEncryptor.getCompressionLevel() == decryptorIndex)
            return &oneBitEncryptor;
        if (twoBitEncryptor.getCompressionLevel() == decryptorIndex)
            return &twoBitEncryptor;
        if (fourBitEncryptor.getCompressionLevel() == decryptorIndex)
            return &fourBitEncryptor;
        return nullptr;
    }
};


#endif //STEGANOGRAPHY_ENCRYPTOR_H
