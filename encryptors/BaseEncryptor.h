#ifndef STEGANOGRAPHY_BASEENCRYPTOR_H
#define STEGANOGRAPHY_BASEENCRYPTOR_H


#include "../Image/Image.h"

class BaseEncryptor {
public:
    void encrypt(Image* image, const string& text) {
        _rowNumber = 0;
        _colNumber = 1; // start from 1st column, because pixel in 0 column is for compression level
        _image = image;
        writeInt(text.size());
        for(auto c:text)
            writeByte(c);
    }

    string decrypt(Image* image) {
        _image = image;
        _rowNumber = 0;
        _colNumber = 1; // start from 1st column, because pixel in 0 column is for compression level
        int length=readInt();
        string result;
        for(int i=0;i<length;i++)
            result.push_back(readByte());
        return result;
    }

    virtual int getPixelsPerByte() = 0;

    virtual int getCompressionLevel() = 0;

protected:

    virtual void writeToPixel(PixelColor* pixel, char value) = 0;

    virtual char readFromPixel(PixelColor* pixel) = 0;

private:
    int _rowNumber, _colNumber;
    Image* _image;

    void writeByte(char value) {
        for(auto i=0; i<getPixelsPerByte(); i++) { // check all bits in byte/char
            auto pixel = _image->getPixel(_rowNumber, _colNumber);
            writeToPixel(pixel, value);
            value = value << (8/getPixelsPerByte());
            _colNumber++;
            if (_colNumber == _image->getWidth()) {
                _colNumber=0;
                _rowNumber++;
            }
        }
    }

    void writeInt(int value) {
        writeByte((value>>24)&0xFF);
        writeByte((value>>16)&0xFF);
        writeByte((value>>8)&0xFF);
        writeByte((value)&0xFF);
    }

    int readInt() {
        return readByte()<<24 |
               readByte()<<16 |
               readByte()<<8  |
               readByte();
    }

    char readByte() {
        char result=0;
        for(auto i=0; i<getPixelsPerByte(); i++) { // check all bits in byte/char
            result = (result<<(8/getPixelsPerByte())) | readFromPixel(_image->getPixel(_rowNumber, _colNumber));
            _colNumber++;
            if (_colNumber == _image->getWidth()) {
                _colNumber=0;
                _rowNumber++;
            }
        }
        return result;
    }

};

#endif //STEGANOGRAPHY_BASEENCRYPTOR_H
