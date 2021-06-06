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

    template <typename T>
    class Queue {
    private:
        T _items[50];
        int _nEntriesAmmount;
        void _shiftBack();

    public:
        Queue();

        bool push(T element);
        bool pop(T& element);
        bool empty();
        bool full();
    };

    template <typename T>
    Queue<T>::Queue() {
        this->_nEntriesAmmount = 0;
    }

    template <typename T>
    void Queue<T>::_shiftBack() {
        for (size_t i = 0; i < this->_nEntriesAmmount; i++)
            this->_items[i] = this->_items[i+1];

        this->_nEntriesAmmount--;
    }

    template <typename T>
    bool Queue<T>::push(T element) {

        if (this->_nEntriesAmmount < 50) {
            this->_items[this->_nEntriesAmmount++] = element;
            return (this->_items[this->_nEntriesAmmount-1] == element);
        }

        return false;
    }

    template <typename T>
    bool Queue<T>::pop(T& element) {

        if (!this->empty()) {
            element = this->_items[0];
            this->_shiftBack();
            return (element == this->_items[0]);
        }

        return false;
    }

    template <typename T>
    bool Queue<T>::empty() {
        return (this->_nEntriesAmmount == 0);
    }

    template <typename T>
    bool Queue<T>::full() {
        return (this->_nEntriesAmmount == 50);
    }

}

#endif
