#include "headers/ArrayList.h"
#include "iostream"

template<typename T>
ArrayList<T>::ArrayList() 
{ 
    this->m_arr = nullptr;
    this->m_size = 0;
    this->m_capacity = 10;
}

template<typename T>
ArrayList<T>::~ArrayList()
{
    delete [] this->m_arr;
}

template<typename T>
void ArrayList<T>::push_back(T* value)
{
    if (this->m_size >= this->m_capacity)
    {
        this->m_capacity = this->m_capacity * 2;
        T* temp = new int[this->m_capacity];
        for (int i = 0; i < this->m_size; i++)
        {
            temp[i] = this->m_arr[i];
        }
        delete [] this->m_arr;
        this->m_arr = temp;
    }
    this->m_arr[this->m_size] = value;
    this->m_size++;
}

template<typename T>
void ArrayList<T>::remove(T* value)
{
    int index = -1;
    for (int i = 0; i < this->m_size; i++)
    {
        if (&this->arr[i] == value)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        std::cout << "Value not found in the array!" << "\n";
        return;
    }
    for (int i = index; i < this->m_size - 1; i++)
    {
        this->arr[i] = this->arr[i + 1];
    }
    this->m_size--;
}

template<typename T>
int ArrayList<T>::size()
{
    return this->m_size;
}

template<typename T>
T* ArrayList<T>::operator[](int index) const
{
    return &this->m_arr[index];
}