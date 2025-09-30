#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

struct Task {
    int start_hour;
    int start_minute;
    int duration;
    std::string description;
};

struct Color {
    int red;
    int green;
    int blue;
};

#endif
