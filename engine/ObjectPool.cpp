#include "headers/ObjectPool.h"
#include "iostream"
#include "vector"

template<typename T>
ObjectPool<T>::ObjectPool() { }

template<typename T>
ObjectPool<T>::~ObjectPool()
{
    for (T* object : this->objects)
    {   
        delete object;
    }
    this->objects.clear();
}

template<typename T>
T* ObjectPool<T>::get()
{
    if (this->objects.empty())
    {
        return new T();
    }
    else
    {
        T* object = this->objects.back();
        this->objects.pop_back();
        return object;
    }
}

template<typename T>
void ObjectPool<T>::release(T* object)
{
    this->objects.push_back(object);
}