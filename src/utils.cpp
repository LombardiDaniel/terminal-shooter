#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>

#include <sstream>
#include <iomanip>

#include "headers/utils.h"

namespace utils {

    bool fileExists(const std::string& filePath) {
        struct stat buffer;
        return (stat (filePath.c_str(), &buffer) == 0);
    }

    // Get current date/time, format is YYYY-MM-DD.HH-mm-ss
    const std::string currentDateTime() {

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();

        return str;
        //
        // time_t rawtime;
        // struct tm * timeinfo;
        // char buffer[200];
        //
        // time(&rawtime);
        // timeinfo = localtime(&rawtime);
        //
        // // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // // for more information about date/time format
        //
        // strftime(buffer, sizeof(buffer),"%Y-%m-%d %H:%M:%S",timeinfo);
        // std::string str(buffer);
        // return str;
    }
}
