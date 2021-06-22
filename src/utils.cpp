#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdarg.h>

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

    Logger::Logger(std::string loggerName, std::string logFilePath, unsigned short priority) {
        this->_prefix = loggerName;
        this->_logFilePath = logFilePath;
        this->_priority = priority;
    }

    Logger::Logger() {}

    void Logger::setPriority(unsigned short priority) {
        this->_priority = priority;
    }

    unsigned short Logger::getPriority() {
        return this->_priority;
    }

    template<typename... Args>
    void Logger::_appendToFile(const char* priorityStr, const char* message, Args... args) {
        std::ofstream logFile;
        logFile.open(this->_logFilePath, std::ios_base::app);

        std::stringstream tmpSSMessage;
        tmpSSMessage << "[%s] %s" << message << ';';

        std::string formattedMessage = tmpSSMessage.str();

        fprintf(formattedMessage, priorityStr, currentDateTime(), args...);

        logFile.close();
    }

    template<typename... Args>
    void Logger::debug(const std::string message, Args... args) {
        if (this->_priority <= Debug)
            this->_appendToFile(message, args...);
    }

    template<typename... Args>
    void Logger::info(const std::string message, Args... args) {
        if (this->_priority <= Info)
            this->_appendToFile("INFO", message, args...);
    }

    template<typename... Args>
    void Logger::warning(const std::string message, Args... args) {
        if (this->_priority <= Warning)
            this->_appendToFile("WARNING", message, args...);
    }

    template<typename... Args>
    void Logger::error(const std::string message, Args... args) {
        if (this->_priority <= Error)
            this->_appendToFile("ERROR", message, args...);
    }

    template<typename... Args>
    void Logger::critical(const std::string message, Args... args) {
        if (this->_priority <= Critical)
            this->_appendToFile("CRITICAL", message, args...);
    }
}
