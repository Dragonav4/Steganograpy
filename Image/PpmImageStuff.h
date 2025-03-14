#ifndef STEGANOGRAPHY_PPMIMAGESTUFF_H
#define STEGANOGRAPHY_PPMIMAGESTUFF_H
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

void skipCommentLine(ifstream& input) {
    string str;
    auto nextChar = input.peek();
    while (nextChar == '#' || nextChar==10 || nextChar==13) {
        std::getline(input, str);
        nextChar=input.peek();
    }
}

template <class T>
T read(ifstream& input) {
    skipCommentLine(input);
    T result;
    input>>result;
    return result;
}
#endif //STEGANOGRAPHY_PPMIMAGESTUFF_H
