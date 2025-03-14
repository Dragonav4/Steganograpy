#ifndef STEGANOGRAPHY_ENCRYPTCOMMANDHANDLER_H
#define STEGANOGRAPHY_ENCRYPTCOMMANDHANDLER_H


#include <iostream>
#include "CommandHandler.h"
#include "../Image/Image.h"
#include "../encryptors/Encryptor.h"

class EncryptCommandHandler : public CommandHandler {
    bool canHandle(const std::vector<std::string> &params) override {
        return !params.empty() && (
                params[0] == "-e" ||
                params[0] == "-encrypt"
                );
    }

    int getAmountOfParams() override {
        return 3; // -e fileName textToEncode
    }

    void handleWithoutParamsCheck(const std::vector<std::string> &params) override {
        const auto fileName = params[1];
        const auto textToEncrypt = params[2];
        Image image;
        image.open(fileName);

        Encryptor::encrypt(&image, textToEncrypt);
        image.save(fileName);
        cout << "Opening file " << fileName << endl
             << "Writing text " << textToEncrypt;

    }
};


#endif //STEGANOGRAPHY_ENCRYPTCOMMANDHANDLER_H
