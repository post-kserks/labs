#include "helpers.h"
#include <cstdlib>

int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double randomDoubleInRange(double min, double max) {
    return min + (rand() % 10001) * (max - min) / 10000.0;
}

char randomChar() {
    const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return chars[rand() % (sizeof(chars) - 1)];
}

char randomLetter() {
    const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return letters[rand() % (sizeof(letters) - 1)];
}

char randomDigit() {
    return '0' + rand() % 10;
}
