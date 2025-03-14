#ifndef STEGANOGRAPHY_FILEINFOCOMMANDHANDLER_H
#define STEGANOGRAPHY_FILEINFOCOMMANDHANDLER_H

#include <chrono>
#include <iostream>
#include "CommandHandler.h"
#include "../Image/Image.h"

class FileInfoCommandHandler : public CommandHandler {
    bool canHandle(const std::vector<std::string> &params) override {
        return !params.empty() && (
                params[0] == "-i" ||
                params[0] == "-info"
        );
    }

    int getAmountOfParams() override {
        return 2; // -i fileName
    }

    void handleWithoutParamsCheck(const std::vector<std::string> &params) override {
        const auto fileName = params[1];
        Image image;
        image.open(fileName);
        auto fileTime = std::chrono::file_clock::to_sys(image.getLastWriteTime());
        cout << "File name:" << fileName << endl
             << "Last write time: " <<fileTime << endl
             << "File size: " <<image.getFileSize()<<endl
             << "Width: "<<image.getWidth() <<endl
             << "height: "<<image.getHeight()<<endl;

    }
private:
//    auto toTime(std::filesystem::file_time_type fileTime) -> tm* {
//        auto std::chrono::file_clock::to_sys(fileTime);
//        const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
//        const auto cftime = std::chrono::system_clock::to_time_t(systemTime);
////        const auto time1=std::chrono::file_clock::to_sys(time);
////        auto cftime = std::chrono::system_clock::to_time_t((std::chrono::time_point&)time1);
//        auto result = std::localtime(&cftime);
//        return result;
//    }
};


#endif //STEGANOGRAPHY_FILEINFOCOMMANDHANDLER_H
