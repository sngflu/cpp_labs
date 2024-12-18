#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <unordered_map> // Для использования std::unordered_map
#include <iostream>      // Для использования std::cout и std::endl
#include <cmath>         // Для использования std::pow
#include <algorithm>     // Для использования std::max и std::min
#include "Utilities.h"   // Для использования pair_hash

// Определение шаблонного класса SparseVector
template <typename T>
class SparseVector
{
private:
    // Хранение индексов и значений
    std::unordered_map<size_t, T> elements;

public:
    // Конструкторы

    // Конструктор по умолчанию
    SparseVector() = default;

    // Конструктор копирования (по умолчанию)
    SparseVector(const SparseVector &other) = default;

    // Добавление или обновление элемента
    void set(size_t index, T value)
    {
        // Если значение не равно нулю, добавляем или обновляем элемент
        if (value != T(0))
        {
            elements[index] = value;
        }
        else
        {
            // Если значение равно нулю, удаляем элемент из вектора
            elements.erase(index);
        }
    }

    // Получение элемента
    T get(size_t index) const
    {
        // Ищем элемент в векторе
        auto it = elements.find(index);
        if (it != elements.end())
        {
            return it->second;
        }
        // Если элемент не найден, возвращаем 0
        return T(0);
    }

    // Перегрузка оператора + для сложения векторов
    SparseVector operator+(const SparseVector &other) const
    {
        SparseVector result = *this;
        for (const auto &[index, value] : other.elements)
        {
            result.set(index, result.get(index) + value);
        }
        return result;
    }

    // Перегрузка оператора - для вычитания векторов
    SparseVector operator-(const SparseVector &other) const
    {
        SparseVector result = *this;
        for (const auto &[index, value] : other.elements)
        {
            result.set(index, result.get(index) - value);
        }
        return result;
    }

    // Скалярное произведение векторов
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

    // Умножение вектора на скаляр
    SparseVector operator*(T scalar) const
    {
        SparseVector result;
        for (const auto &[index, value] : elements)
        {
            result.set(index, value * scalar);
        }
        return result;
    }

    // Деление вектора на скаляр
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

    // Получение всех ненулевых элементов для итерирования
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
