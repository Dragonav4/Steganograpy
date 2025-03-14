#ifndef STEGANOGRAPHY_CHECKFILESIZECOMMANDHANDLER_H
#define STEGANOGRAPHY_CHECKFILESIZECOMMANDHANDLER_H


#include <iostream>
#include "CommandHandler.h"
#include "../Image/Image.h"
#include "../encryptors/Encryptor.h"

class CheckFileSizeCommandHandler : public CommandHandler {
    bool canHandle(const std::vector<std::string> &params) override {
        return !params.empty() && (
                params[0] == "-c" ||
                params[0] == "-check"
        );
    }

    int getAmountOfParams() override {
        return 3; // -c fileName textToEncode
    }

    void handleWithoutParamsCheck(const std::vector<std::string> &params) override {
        const string& fileName = params[1];
        const string& text = params[2];
        Image image;
        image.open(fileName);
        auto encryptor = Encryptor::getEncryptor(&image, text);
        if (encryptor == nullptr) {
            cout<<"Image is too small to fit given text";
        }
        else {
            cout<<"Image size is enough to fit given text with "<<encryptor->getPixelsPerByte()<<" pixels per byte encoding";
        }
    }
};


#endif //STEGANOGRAPHY_CHECKFILESIZECOMMANDHANDLER_H
