#include <Windows.h>
#include <iostream>
#include <chrono>
#include "math.h"

#include "headers/entity.h"
#include "headers/engine.h"
#include "headers/player.h"
#include "headers/mobs.h"
#include "headers/map.h"
#include "headers/utils.h"

Map::Map() {

    this->nMapWidth = 16;
    this->nMapHeight = 16;

    this->smap += "################";
    this->smap += "#..............#";
    this->smap += "#...........####";
    this->smap += "#..............#";
    this->smap += "#.###..........#";
    this->smap += "#...#..........#";
    this->smap += "#...#..........#";
    this->smap += "#...#..........#";
    this->smap += "#.....#####....#";
    this->smap += "#..............#";
    this->smap += "#...#..........#";
    this->smap += "#...#..........#";
    this->smap += "#...#..#.......#";
    this->smap += "#........#######";
    this->smap += "#..............#";
    this->smap += "################";

    this->smobs += "################";
    this->smobs += "#..............#";
    this->smobs += "#...........####";
    this->smobs += "#..........X...#";
    this->smobs += "#.###..........#";
    this->smobs += "#...#..........#";
    this->smobs += "#...#..........#";
    this->smobs += "#...#..........#";
    this->smobs += "#.....#####....#";
    this->smobs += "#..............#";
    this->smobs += "#...#..........#";
    this->smobs += "#...#..........#";
    this->smobs += "#...#..#.......#";
    this->smobs += "#........#######";
    this->smobs += "#..............#";
    this->smobs += "################";
}
