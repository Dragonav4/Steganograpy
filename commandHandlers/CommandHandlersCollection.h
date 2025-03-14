#ifndef STEGANOGRAPHY_COMMANDHANDLERSCOLLECTION_H
#define STEGANOGRAPHY_COMMANDHANDLERSCOLLECTION_H


#include "CommandHandler.h"
#include "EncryptCommandHandler.h"
#include "DecryptCommandHandler.h"
#include "FileInfoCommandHandler.h"
#include "CheckFileSizeCommandHandler.h"
#include "HelpCommandHandler.h"

using namespace std;

class CommandHandlersCollection {
private:
    static inline EncryptCommandHandler encryptCommandHandler;
    static inline DecryptCommandHandler decryptCommandHandler;
    static inline FileInfoCommandHandler fileInfoCommandHandler;
    static inline CheckFileSizeCommandHandler checkFileSizeCommandHandler;
    static inline HelpCommandHandler helpCommandHandler;
public:
    static vector<CommandHandler*> getCommandHandlers() {
        vector<CommandHandler*> result={
            &encryptCommandHandler,
            &decryptCommandHandler,
            &fileInfoCommandHandler,
            &checkFileSizeCommandHandler,
            &helpCommandHandler};
        return result;
    }

    static CommandHandler* getDefaultCommandHandler() {
        return &helpCommandHandler;
    }
};

#endif //STEGANOGRAPHY_COMMANDHANDLERSCOLLECTION_H
