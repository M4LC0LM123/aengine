#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#pragma once
#include "iostream"
#include "vector"

template<typename T>
class ObjectPool
{
    private:
        std::vector<T*> objects;

    public:
        ObjectPool();
        ~ObjectPool();
        T* get();
        void release(T* object);
};

#endif