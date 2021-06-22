#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace utils {

    const float PI = 3.141592f;

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
        this->_items = new T[_ALLOC_BLOCK_SIZE];
        this->_nCurrentSize = _ALLOC_BLOCK_SIZE;
        this->_nEntriesAmmount = 0;
    }

    template <typename T>
    Queue<T>::~Queue() {
        delete[] this->_items;
    }

    template <typename T>
    bool Queue<T>::_allocNewBlock() {
        this->_nCurrentSize += _ALLOC_BLOCK_SIZE;
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

        if (this->_full)
            if (this->_allocNewBlock() == NULL)
                exit(1);

        this->_items[this->_nEntriesAmmount++] = element;
        return this->_items[this->_nEntriesAmmount-1] == element;

        return false;
    }

    template <typename T>
    bool Queue<T>::pop(T& element) {

        if (!this->empty()) {
            element = this->_items[0];
            this->_shiftBack();

            return element == this->_items[0];
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

    // class Logger {
    //     private:
    //         char _prefix;
    //         char _path;
    //         static const unsigned short int _lvl;
    //     public:
    //         Logger(char prefix, char path, const int lvl);
    //         ~Logger();
    //         void log(char msg, int lvl=2);
    //         static int lvl_str(int lvl);
    //         static void stdout_log(char msg, int lvl=INFO, **kwargs);
    // };
    //
    // Logger::Logger(char prefix, char path, int lvl) {
    //     this->_prefix = prefix;
    //     //this->_path = f'./logs/{prefix}.log';
    //     this->_lvl = lvl;
    // }
    //
    // Logger::~Logger(){
    //     delete[] this->_prefix;
    //     delete[] this->_path;
    //     delete[] this->_lvl;
    // }
    //
    // void Logger::log(char msg, int lvl=2){
    //     if (lvl >= this->_lvl){
    //         if (this->_path !=NULL){
    //            // with open(self.path, 'a+') as log_file:
    //                 //log_file.write(f"{self._lvl_str(lvl)}; {str(datetime.now())[:-3]}; {msg};\n");
    //         }
    //         //Logger::stdout_log(msg, lvl=this->lvl_str(lvl), prefix=this->_prefix);
    //     }
    // }
    //
    // static int Logger::lvl_str(int lvl){
    //     int lst_lvl[4] = {INFO,WARNING,ERROR,CRITICAL};
    //
    //     return lst_lvl[lvl - 1];
    // }
    /*static void Logger::stdout_log(char msg, int lvl=INFO, **kwargs){
        struct tm *data_hora_atual;
        time_t segundos;
        time(&segundos);
        data_hora_atual = localtime(&segundos);

        //char log = f'{lvl.upper()}; {str(datetime.now())[:-3]}; {msg};'
        char* result
        if (strstr(kwargs, "prefix")!=NULL){
            //log = f"{lvl}; {kwargs.get('prefix')}; {str(datetime.now())[:-3]}; {msg};";
            delete kwargs['prefix'];
        }
        else
            //log = f"{lvl}; {str(datetime.now())[:-3]}; {msg};"

        for (size_t key = 0; key<strlen(kwargs.items()); key++)
           // log += f"{key}: {value}; "

        //printf(log);
    }*/

        // abstrair abrir arquivo e dar um append nele com (\n) no comeco da linha
        // colocar infos: LVL - HORA - MSG
    // };

}

#endif
