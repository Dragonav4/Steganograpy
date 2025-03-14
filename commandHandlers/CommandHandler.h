#ifndef STEGANOGRAPHY_COMMANDHANDLER_H
#define STEGANOGRAPHY_COMMANDHANDLER_H

#include <vector>
#include <string>
#include <exception>
//#include "../exceptions/argument_count_exception.h"


class CommandHandler {
public:
    virtual bool canHandle(const std::vector<std::string>& params) = 0; // pure abstract method
    void handleWithParamsCheck(const std::vector<std::string>& params){
        if (params.size() != getAmountOfParams()) {
            throw argument_count_exception(getAmountOfParams());
        }
        handleWithoutParamsCheck(params);
    }
    virtual void handleWithoutParamsCheck(const std::vector<std::string>& params) = 0; // pure abstract method
protected:
    virtual int getAmountOfParams() = 0; // pure abstract method
};


#endif //STEGANOGRAPHY_COMMANDHANDLER_H
