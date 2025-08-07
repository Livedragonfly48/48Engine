#pragma once
#include <cstdlib>  
#include <cstring> 
#include <cassert>  

template <typename T>
class MyVector
{

private:
    T* data;
    size_t capacity;
    size_t size;




    void resize(size_t newCapacity)
    {
        T* newData = (T*)malloc(newCapacity * sizeof(T));
        assert(newData && "Fallo al asignar memoria");

        if (data)
        {
            memcpy(newData, data, size * sizeof(T));
            free(data);
        }

        data = newData;
        capacity = newCapacity;
    }




    void ensureCapacity()
    {
        if (size >= capacity)
        {
            resize(capacity == 0 ? 4 : capacity * 2);
        }
    }




public:
    MyVector()
        : data(nullptr), capacity(0), size(0)
    {
    }




    ~MyVector()
    {
        free(data);
    }

   



    MyVector(const MyVector& other)
        : data(nullptr), capacity(other.capacity), size(other.size)
    {
        if (capacity > 0)
        {
            data = (T*)malloc(capacity * sizeof(T));
            memcpy(data, other.data, size * sizeof(T));
        }
    }




    MyVector& operator=(const MyVector& other)
    {
        if (this != &other)
        {
            if (data)
                free(data);

            capacity = other.capacity;
            size = other.size;
            data = (T*)malloc(capacity * sizeof(T));
            memcpy(data, other.data, size * sizeof(T));
        }
        return *this;
    }

    



    void push_back(const T& value)
    {
        ensureCapacity();
        data[size++] = value;
    }




    void pop_back()
    {
        if (size > 0)
            --size;
    }




    void insert(size_t index, const T& value)
    {
        assert(index <= size && "Índice fuera de rango en insert()");
        ensureCapacity();
        memmove(&data[index + 1], &data[index], (size - index) * sizeof(T));
        data[index] = value;
        ++size;
    }




    void erase(size_t index)
    {
        assert(index < size && "Índice fuera de rango en erase()");
        memmove(&data[index], &data[index + 1], (size - index - 1) * sizeof(T));
        --size;
    }




    void clear()
    {
        size = 0;
    }




    T& operator[](size_t index)
    {
        assert(index < size && "Índice fuera de rango en operator[]");
        return data[index];
    }




    const T& operator[](size_t index) const
    {
        assert(index < size && "Índice fuera de rango en operator[]");
        return data[index];
    }



    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }

    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }
};
