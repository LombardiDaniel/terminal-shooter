#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

namespace utils {

    const float PI = 3.141592f;

    template <typename T = char*>
    void _insert_color(char* original, unsigned int pos, T new_insertion) {
        for (size_t i = 0; i < 6; i++)
            original[i + pos] = new_insertion[i + pos];
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

}

#endif
