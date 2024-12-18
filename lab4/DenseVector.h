#ifndef DENSEVECTOR_H
#define DENSEVECTOR_H

#include <vector>    // Для использования std::vector
#include <iostream>  // Для использования std::cout и std::endl
#include <cmath>     // Для использования std::pow
#include <algorithm> // Для использования std::max и std::min

// Определение шаблонного класса DenseVector
template <typename T>
class DenseVector
{
private:
    // Вектор для хранения элементов
    std::vector<T> elements;

public:
    // Конструкторы

    // Конструктор по умолчанию
    DenseVector() = default;

    // Конструктор, инициализирующий вектор нулями заданного размера
    DenseVector(size_t size) : elements(size, T(0)) {}

    // Конструктор копирования
    DenseVector(const DenseVector &other) = default;

    // Установка элемента
    void set(size_t index, T value)
    {
        // Если индекс выходит за пределы текущего размера вектора, расширяем вектор
        if (index >= elements.size())
        {
            elements.resize(index + 1, T(0));
        }
        // Устанавливаем значение элемента
        elements[index] = value;
    }

    // Получение элемента
    T get(size_t index) const
    {
        // Если индекс выходит за пределы текущего размера вектора, возвращаем 0
        if (index >= elements.size())
        {
            return T(0);
        }
        // Возвращаем значение элемента
        return elements[index];
    }

    // Перегрузка оператора + для сложения векторов
    DenseVector operator+(const DenseVector &other) const
    {
        // Определяем максимальный размер результирующего вектора
        size_t maxSize = std::max(elements.size(), other.elements.size());
        DenseVector result(maxSize);

        // Сложение элементов векторов
        for (size_t i = 0; i < maxSize; ++i)
        {
            T val1 = (i < elements.size()) ? elements[i] : T(0);
            T val2 = (i < other.elements.size()) ? other.elements[i] : T(0);
            result.set(i, val1 + val2);
        }
        return result;
    }

    // Перегрузка оператора - для вычитания векторов
    DenseVector operator-(const DenseVector &other) const
    {
        // Определяем максимальный размер результирующего вектора
        size_t maxSize = std::max(elements.size(), other.elements.size());
        DenseVector result(maxSize);

        // Вычитание элементов векторов
        for (size_t i = 0; i < maxSize; ++i)
        {
            T val1 = (i < elements.size()) ? elements[i] : T(0);
            T val2 = (i < other.elements.size()) ? other.elements[i] : T(0);
            result.set(i, val1 - val2);
        }
        return result;
    }

    // Скалярное произведение векторов
    T dotProduct(const DenseVector &other) const
    {
        T result = T(0);
        // Определяем минимальный размер векторов для скалярного произведения
        size_t minSize = std::min(elements.size(), other.elements.size());
        for (size_t i = 0; i < minSize; ++i)
        {
            result += elements[i] * other.elements[i];
        }
        return result;
    }

    // Умножение вектора на скаляр
    DenseVector operator*(T scalar) const
    {
        DenseVector result(*this);
        for (auto &val : result.elements)
        {
            val *= scalar;
        }
        return result;
    }

    // Деление вектора на скаляр
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

    // Получение всех элементов для итерирования
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
