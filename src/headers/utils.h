#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string.h>

namespace utils {

    const float PI = 3.141592f;

    template<typename T = char*>
    void _insert_color(char* original, unsigned int pos, T new_insertion) {
        for (size_t i = 0; i < 6; i++)
            original[i + pos] = new_insertion[i + pos];
    }
}

#endif
