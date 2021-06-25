#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>


namespace utils {

    const float PI = 3.141592f;

    const std::string currentDateTime();

    template <typename T>
    T modulus(T val) {
        if (val >= 0)
            return val;
        return -val;
    }

    bool fileExists(const std::string& filePath);

    int ourDistribution(int min, int max);

    template <typename T = char*>
    void _insert_color(char* original, unsigned int pos, T new_insertion) {
        for (size_t i = 0; i < 6; i++)
            original[i + pos] = new_insertion[i + pos];
    }

    template <typename T>
    void swap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <typename T>
    class Queue {
        static const unsigned short int _ALLOC_BLOCK_SIZE = 5;
    private:
        T* _items;
        int _nEntriesAmmount;
        int _nCurrentSize;

        void _shiftBack();
        bool _allocNewBlock();
        bool _full();

    public:
        Queue();
        ~Queue();

        bool push(T element);
        bool pop(T& element);
        bool empty();
    };

    template <typename T>
    Queue<T>::Queue() {
        this->_items = new T[Queue::_ALLOC_BLOCK_SIZE];
        this->_nCurrentSize = Queue::_ALLOC_BLOCK_SIZE;
        this->_nEntriesAmmount = 0;
    }

    template <typename T>
    Queue<T>::~Queue() {
        delete[] this->_items;
    }

    template <typename T>
    bool Queue<T>::_allocNewBlock() {
        this->_nCurrentSize += Queue::_ALLOC_BLOCK_SIZE;
        this->_items = (T*) realloc(this->_items, this->_nCurrentSize);

        return this->_items != NULL;
    }

    template <typename T>
    void Queue<T>::_shiftBack() {
        for (size_t i = 0; i < this->_nEntriesAmmount; i++)
            this->_items[i] = this->_items[i+1];

        this->_nEntriesAmmount--;
    }

    template <typename T>
    bool Queue<T>::push(T element) {

        if (this->_full())
            if (!this->_allocNewBlock())
                exit(1);

        this->_items[this->_nEntriesAmmount++] = element;
        return true;
    }

    template <typename T>
    bool Queue<T>::pop(T& element) {

        if (!this->empty()) {
            element = this->_items[0];
            this->_shiftBack();

            return true;
        }

        return false;
    }

    template <typename T>
    bool Queue<T>::empty() {
        return this->_nEntriesAmmount == 0;
    }

    template <typename T>
    bool Queue<T>::_full() {
        return this->_nEntriesAmmount == this->_nCurrentSize;
    }



    class Logger {
    public:
        enum logPriority : unsigned short {Debug = 0, Info, Warning, Error, Critical};
        static unsigned short int DEBUG;

    private:
        unsigned short _priority;
        char* _logFilePath;
        char* _prefix;

        template<typename... Args>
        void _appendToFile(const char* priorityStr, const char* message, Args... args) {
            std::ofstream logFile;
            FILE* pFile;

            const char* loggingPath;
            if (Logger::DEBUG)
                loggingPath = this->_logFilePath;
            else
                loggingPath = "TermShooter.log";

            pFile = fopen((const char*) loggingPath, "a+");

            std::fprintf(pFile, "[%s] - %s - %s - ", priorityStr, this->_prefix, currentDateTime().c_str());

            std::fprintf(pFile, message, args...);

            std::fprintf(pFile, ";\n");

            fclose(pFile);
        }

    public:
        Logger() {}
        Logger(char* loggerName, char* logFilePath, unsigned short priority=Info) {
            this->_prefix = loggerName;
            this->_logFilePath = logFilePath;
            this->_priority = priority;
        }

        static void setDebug() {
            DEBUG = 1;
        }

        static void unsetDebug() {
            DEBUG = 0;
        }

        void setPriority(unsigned short priority) {
            this->_priority = priority;
        }

        unsigned short getPriority() {
            return this->_priority;
        }

        // Basic logging funcions:
        template<typename... Args>
        void debug(const char* message, Args... args) {
            if (this->_priority <= Debug)
                this->_appendToFile("DEBUG", message, args...);
        }

        template<typename... Args>
        void info(const char* message, Args... args) {
            if (this->_priority <= Info)
                this->_appendToFile("INFO", message, args...);
        }

        template<typename... Args>
        void warning(const char* message, Args... args) {
            if (this->_priority <= Warning)
                this->_appendToFile("WARNING", message, args...);
        }

        template<typename... Args>
        void error(const char* message, Args... args) {
            if (this->_priority <= Error)
                this->_appendToFile("ERROR", message, args...);
        }

        template<typename... Args>
        void critical(const char* message, Args... args) {
            if (this->_priority <= Critical)
                this->_appendToFile("CRITICAL", message, args...);
        }
    };
}

#endif
