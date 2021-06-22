#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <ctime>
#include <sstream>

#include "headers/utils.h"

namespace utils {
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    const std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }

    Logger::Logger(std::string loggerName, std::string logFilePath, logPriority priority) {
        this->_prefix = loggerName;
        this->_logFilePath = logFilePath;
        this->_priority = priority;
    }

    template<typename... Args>
    void Logger::_appendToFile(std::string priorityStr, const char* message, Args... args) {
        std::ofstream logFile;
        logFile.open(this->_logFilePath, std::ios_base::app);

        std::stringstream tmpSSMessage;
        tmpSSMessage << "[%s] %s" << message << ';';

        std::string formattedMessage = tmpSSMessage.str();

        fprintf(formattedMessage, priorityStr, currentDateTime(), args...);

        logFile.close();
    }

    template<typename... Args>
    void Logger::debug(const char* message, Args... args) {
        if (this->_priority <= DEBUG)
            this->_appendToFile(message, args...);
    }

    template<typename... Args>
    void Logger::info(const char* message, Args... args) {
        if (this->_priority <= INFO)
            this->_appendToFile("INFO", message, args...);
    }

    template<typename... Args>
    void Logger::warning(const char* message, Args... args) {
        if (this->_priority <= WARNING)
            this->_appendToFile("WARNING", message, args...);
    }

    template<typename... Args>
    void Logger::error(const char* message, Args... args) {
        if (this->_priority <= ERROR)
            this->_appendToFile("ERROR", message, args...);
    }

    template<typename... Args>
    void Logger::critical(const char* message, Args... args) {
        if (this->_priority <= CRITICAL)
            this->_appendToFile("CRITICAL", message, args...);
    }
}
