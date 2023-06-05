#pragma once
#include "iostream"

template<typename T>
class ArrayList
{
    public:
        ArrayList();
        ~ArrayList();
        void push_back(T* value);
        void remove(T* value);
        int size();
        T* operator[](int index) const;

    private:
        T* m_arr; // pointer to dynamically allocated array
        int m_size; // current size
        int m_capacity; // max capacity
};
