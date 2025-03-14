#ifndef STEGANOGRAPHY_HELPCOMMANDHANDLER_H
#define STEGANOGRAPHY_HELPCOMMANDHANDLER_H

#include <iostream>
#include "CommandHandler.h"

using namespace std;

class HelpCommandHandler : public CommandHandler{
    bool canHandle(const std::vector<std::string> &params) override {
        return params.empty() ||
                params[0] == "-h" ||
                params[0] == "-help"
        ;
    }

    int getAmountOfParams() override {
        return 1; // -h
    }

    void handleWithoutParamsCheck(const std::vector<std::string> &params) override {
        cout<<"Stenography usage:"<<endl
            <<"  -i %filename% to get image file info"<<endl
            <<"  -e %filename% %text% to encode text into file"<<endl
            <<"  -d %filename% to decode text from file"<<endl
            <<"  -c %filename% %text% to check whether specified text fits into given file"<<endl
            <<"  -h to print this text";

    }
};


#endif //STEGANOGRAPHY_HELPCOMMANDHANDLER_H
