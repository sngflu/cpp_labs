#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <unordered_map>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Utilities.h"

template <typename T>
class SparseVector
{
private:
    std::unordered_map<size_t, T> elements; // Хранение индексов и значений

public:
    // Конструкторы
    SparseVector() = default;
    SparseVector(const SparseVector &other) = default;

    // Добавление или обновление элемента
    void set(size_t index, T value)
    {
        if (value != T(0))
        {
            elements[index] = value;
        }
        else
        {
            elements.erase(index);
        }
    }

    // Получение элемента
    T get(size_t index) const
    {
        auto it = elements.find(index);
        if (it != elements.end())
        {
            return it->second;
        }
        return T(0);
    }

    // Перегрузка оператора +
    SparseVector operator+(const SparseVector &other) const
    {
        SparseVector result = *this;
        for (const auto &[index, value] : other.elements)
        {
            result.set(index, result.get(index) + value);
        }
        return result;
    }

    // Перегрузка оператора -
    SparseVector operator-(const SparseVector &other) const
    {
        SparseVector result = *this;
        for (const auto &[index, value] : other.elements)
        {
            result.set(index, result.get(index) - value);
        }
        return result;
    }

    // Скалярное произведение
    T dotProduct(const SparseVector &other) const
    {
        T result = T(0);
        // Итерация по меньшему из двух векторов для эффективности
        if (elements.size() < other.elements.size())
        {
            for (const auto &[index, value] : elements)
            {
                result += value * other.get(index);
            }
        }
        else
        {
            for (const auto &[index, value] : other.elements)
            {
                result += value * get(index);
            }
        }
        return result;
    }

    // Умножение на скаляр
    SparseVector operator*(T scalar) const
    {
        SparseVector result;
        for (const auto &[index, value] : elements)
        {
            result.set(index, value * scalar);
        }
        return result;
    }

    // Деление на скаляр
    SparseVector operator/(T scalar) const
    {
        SparseVector result;
        for (const auto &[index, value] : elements)
        {
            result.set(index, value / scalar);
        }
        return result;
    }

    // Поэлементное возведение в степень
    SparseVector powElements(T exponent) const
    {
        SparseVector result;
        for (const auto &[index, value] : elements)
        {
            result.set(index, std::pow(value, exponent));
        }
        return result;
    }

    // Вывод вектора
    void print() const
    {
        for (const auto &[index, value] : elements)
        {
            std::cout << "(" << index << ": " << value << ") ";
        }
        std::cout << std::endl;
    }

    // Получение всех ненулевых элементов (для итерации)
    const std::unordered_map<size_t, T> &getElements() const
    {
        return elements;
    }

    // Операции сравнения
    bool operator==(const SparseVector &other) const
    {
        return elements == other.elements;
    }

    bool operator!=(const SparseVector &other) const
    {
        return !(*this == other);
    }
};

#endif
