#ifndef STEGANOGRAPHY_ARGUMENT_COUNT_EXCEPTION_H
#define STEGANOGRAPHY_ARGUMENT_COUNT_EXCEPTION_H

#include <exception>

class argument_count_exception : public std::exception {
private:
    long _expected_count;
public:
    argument_count_exception(long expected_count) : _expected_count(expected_count) {
    }

    long get_expected_count() {
        return _expected_count;
    }
};

#endif //STEGANOGRAPHY_ARGUMENT_COUNT_EXCEPTION_H
