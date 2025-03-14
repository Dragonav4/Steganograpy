#ifndef STEGANOGRAPHY_DECRYPTCOMMANDHANDLER_H
#define STEGANOGRAPHY_DECRYPTCOMMANDHANDLER_H

#include <iostream>
#include "CommandHandler.h"
#include "../Image/Image.h"
#include "../encryptors/Encryptor.h"

class DecryptCommandHandler : public CommandHandler {
    bool canHandle(const std::vector<std::string> &params) override {
        return !params.empty() && (
                params[0] == "-d" ||
                params[0] == "-decrypt"
        );
    }

    int getAmountOfParams() override {
        return 2; // -d fileName
    }

    void handleWithoutParamsCheck(const std::vector<std::string> &params) override {
        const auto fileName = params[1];
        Image image;
        image.open(fileName);

        auto result = Encryptor::decrypt(&image);
        cout << "Opening file " << fileName << endl
             << "Decrypted text:" << endl
             << result << endl;
    }
};


#endif //STEGANOGRAPHY_DECRYPTCOMMANDHANDLER_H
