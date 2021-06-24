#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>
#include <sys/time.h>
#include <chrono>

#include <sstream>
#include <iomanip>

#include "headers/utils.h"

namespace utils {

    unsigned short int Logger::DEBUG = 0;

    bool fileExists(const std::string& filePath) {
        struct stat buffer;
        return (stat (filePath.c_str(), &buffer) == 0);
    }

    int ourDistribution(int min, int max) {
        struct timeval time_now{};
        gettimeofday(&time_now, nullptr);

        return ((int) time_now.tv_usec) % (max - min) + min;
    }

    // Get current date/time, format is YYYY-MM-DD.HH-mm-ss
    const std::string currentDateTime() {

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        auto str = oss.str();

        return str;
    }
}
