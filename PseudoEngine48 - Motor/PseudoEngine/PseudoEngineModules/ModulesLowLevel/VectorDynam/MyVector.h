#pragma once
#include <cstdlib>  
#include <cstring> 
#include <cassert>  

/// <summary>
/// Implementacion de un vector dinamico tipo std::vector.
/// </summary>
/// <typeparam name="T">Tipo de datos almacenados en el vector.</typeparam>
template <typename T>
class MyVector
{
private:
    T* data;          ///< Puntero a la memoria del vector.
    size_t capacity;  ///< Capacidad total asignada.
    size_t size;      ///< Numero de elementos actualmente almacenados.

    /// <summary>
    /// Redimensiona el vector a una nueva capacidad.
    /// </summary>
    /// <param name="newCapacity">Nueva capacidad deseada.</param>
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

    /// <summary>
    /// Asegura que haya suficiente espacio para un nuevo elemento.
    /// Si no hay, duplica la capacidad.
    /// </summary>
    void ensureCapacity()
    {
        if (size >= capacity)
        {
            resize(capacity == 0 ? 4 : capacity * 2);
        }
    }

public:
    /// <summary>
    /// Constructor por defecto.
    /// </summary>
    MyVector()
        : data(nullptr), capacity(0), size(0)
    {
    }

    /// <summary>
    /// Destructor.
    /// </summary>
    ~MyVector()
    {
        free(data);
    }

    /// <summary>
    /// Constructor de copia.
    /// </summary>
    /// <param name="other">Vector a copiar.</param>
    MyVector(const MyVector& other)
        : data(nullptr), capacity(other.capacity), size(other.size)
    {
        if (capacity > 0)
        {
            data = (T*)malloc(capacity * sizeof(T));
            memcpy(data, other.data, size * sizeof(T));
        }
    }

    /// <summary>
    /// Operador de asignacion.
    /// </summary>
    /// <param name="other">Vector a asignar.</param>
    /// <returns>Referencia al vector actual.</returns>
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

    /// <summary>
    /// Agrega un elemento al final del vector.
    /// </summary>
    /// <param name="value">Elemento a agregar.</param>
    void push_back(const T& value)
    {
        ensureCapacity();
        data[size++] = value;
    }

    /// <summary>
    /// Elimina el ultimo elemento del vector.
    /// </summary>
    void pop_back()
    {
        if (size > 0)
            --size;
    }

    /// <summary>
    /// Inserta un elemento en la posicion indicada.
    /// </summary>
    /// <param name="index">Indice donde insertar.</param>
    /// <param name="value">Elemento a insertar.</param>
    void insert(size_t index, const T& value)
    {
        assert(index <= size && "Indice fuera de rango en insert()");
        ensureCapacity();
        memmove(&data[index + 1], &data[index], (size - index) * sizeof(T));
        data[index] = value;
        ++size;
    }

    /// <summary>
    /// Elimina el elemento en la posicion indicada.
    /// </summary>
    /// <param name="index">Indice del elemento a eliminar.</param>
    void erase(size_t index)
    {
        assert(index < size && "Indice fuera de rango en erase()");
        memmove(&data[index], &data[index + 1], (size - index - 1) * sizeof(T));
        --size;
    }

    /// <summary>
    /// Vacía todos los elementos del vector.
    /// </summary>
    void clear()
    {
        size = 0;
    }

    /// <summary>
    /// Operador de acceso a elementos.
    /// </summary>
    /// <param name="index">Indice del elemento.</param>
    /// <returns>Referencia al elemento en la posicion indicada.</returns>
    T& operator[](size_t index)
    {
        assert(index < size && "Indice fuera de rango en operator[]");
        return data[index];
    }

    /// <summary>
    /// Operador de acceso a elementos constante.
    /// </summary>
    /// <param name="index">Indice del elemento.</param>
    /// <returns>Referencia constante al elemento en la posicion indicada.</returns>
    const T& operator[](size_t index) const
    {
        assert(index < size && "Indice fuera de rango en operator[]");
        return data[index];
    }

    /// <summary>
    /// Obtiene el numero de elementos almacenados.
    /// </summary>
    /// <returns>Cantidad de elementos en el vector.</returns>
    size_t getSize() const { return size; }

    /// <summary>
    /// Obtiene la capacidad actual del vector.
    /// </summary>
    /// <returns>Capacidad total asignada.</returns>
    size_t getCapacity() const { return capacity; }

    /// <summary>
    /// Verifica si el vector esta vacio.
    /// </summary>
    /// <returns>true si no hay elementos, false en caso contrario.</returns>
    bool empty() const { return size == 0; }

    /// <summary>Iterador al inicio del vector.</summary>
    T* begin() { return data; }

    /// <summary>Iterador al final del vector.</summary>
    T* end() { return data + size; }

    /// <summary>Iterador constante al inicio del vector.</summary>
    const T* begin() const { return data; }

    /// <summary>Iterador constante al final del vector.</summary>
    const T* end() const { return data + size; }
};
