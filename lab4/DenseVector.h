#ifndef DENSEVECTOR_H
#define DENSEVECTOR_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T>
class DenseVector
{
private:
    std::vector<T> elements;

public:
    // Конструкторы
    DenseVector() = default;
    DenseVector(size_t size) : elements(size, T(0)) {}
    DenseVector(const DenseVector &other) = default;

    // Установка элемента
    void set(size_t index, T value)
    {
        if (index >= elements.size())
        {
            elements.resize(index + 1, T(0));
        }
        elements[index] = value;
    }

    // Получение элемента
    T get(size_t index) const
    {
        if (index >= elements.size())
        {
            return T(0);
        }
        return elements[index];
    }

    // Перегрузка оператора +
    DenseVector operator+(const DenseVector &other) const
    {
        size_t maxSize = std::max(elements.size(), other.elements.size());
        DenseVector result(maxSize);
        for (size_t i = 0; i < maxSize; ++i)
        {
            T val1 = (i < elements.size()) ? elements[i] : T(0);
            T val2 = (i < other.elements.size()) ? other.elements[i] : T(0);
            result.set(i, val1 + val2);
        }
        return result;
    }

    // Перегрузка оператора -
    DenseVector operator-(const DenseVector &other) const
    {
        size_t maxSize = std::max(elements.size(), other.elements.size());
        DenseVector result(maxSize);
        for (size_t i = 0; i < maxSize; ++i)
        {
            T val1 = (i < elements.size()) ? elements[i] : T(0);
            T val2 = (i < other.elements.size()) ? other.elements[i] : T(0);
            result.set(i, val1 - val2);
        }
        return result;
    }

    // Скалярное произведение
    T dotProduct(const DenseVector &other) const
    {
        T result = T(0);
        size_t minSize = std::min(elements.size(), other.elements.size());
        for (size_t i = 0; i < minSize; ++i)
        {
            result += elements[i] * other.elements[i];
        }
        return result;
    }

    // Умножение на скаляр
    DenseVector operator*(T scalar) const
    {
        DenseVector result(*this);
        for (auto &val : result.elements)
        {
            val *= scalar;
        }
        return result;
    }

    // Деление на скаляр
    DenseVector operator/(T scalar) const
    {
        DenseVector result(*this);
        for (auto &val : result.elements)
        {
            val /= scalar;
        }
        return result;
    }

    // Поэлементное возведение в степень
    DenseVector powElements(T exponent) const
    {
        DenseVector result(*this);
        for (auto &val : result.elements)
        {
            val = std::pow(val, exponent);
        }
        return result;
    }

    // Вывод вектора
    void print() const
    {
        for (size_t i = 0; i < elements.size(); ++i)
        {
            std::cout << "(" << i << ": " << elements[i] << ") ";
        }
        std::cout << std::endl;
    }

    // Получение всех элементов (для итерации)
    const std::vector<T> &getElements() const
    {
        return elements;
    }

    // Операции сравнения
    bool operator==(const DenseVector &other) const
    {
        return elements == other.elements;
    }

    bool operator!=(const DenseVector &other) const
    {
        return !(*this == other);
    }
};

#endif
