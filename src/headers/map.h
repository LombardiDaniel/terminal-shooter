#ifndef MAP_H
#define MAP_H

#include <iostream>

#include "entity.h"

class Map {
public:
    Map();

    int nMapHeight;
    int nMapWidth;

    std::string smap;
    std::string smobs;
};

#endif
