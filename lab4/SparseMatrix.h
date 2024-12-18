#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <unordered_map> // Для использования std::unordered_map
#include <utility>       // Для использования std::pair
#include <iostream>      // Для использования std::cout и std::endl
#include <cmath>         // Для использования std::abs и std::pow
#include <vector>        // Для использования std::vector
#include "Utilities.h"   // Для использования pair_hash

// Определение шаблонного класса SparseMatrix
template <typename T>
class SparseMatrix
{
private:
    // Используем пару (строка, столбец) как ключ
    std::unordered_map<std::pair<size_t, size_t>, T, pair_hash> elements;
    size_t rows;
    size_t cols;

public:
    // Конструкторы

    // Конструктор по умолчанию, инициализирует матрицу с заданными размерами
    SparseMatrix(size_t rows = 0, size_t cols = 0) : rows(rows), cols(cols) {}

    // Конструктор копирования
    SparseMatrix(const SparseMatrix &other) = default;

    // Установка размеров матрицы
    void setDimensions(size_t newRows, size_t newCols)
    {
        rows = newRows;
        cols = newCols;
    }

    // Добавление или обновление элемента
    void set(size_t row, size_t col, T value)
    {
        // Если значение не равно нулю, добавляем или обновляем элемент
        if (value != T(0))
        {
            elements[{row, col}] = value;
        }
        else
        {
            // Если значение равно нулю, удаляем элемент из матрицы
            elements.erase({row, col});
        }
    }

    // Получение элемента
    T get(size_t row, size_t col) const
    {
        // Ищем элемент в матрице
        auto it = elements.find({row, col});
        if (it != elements.end())
        {
            return it->second;
        }
        // Если элемент не найден, возвращаем 0
        return T(0);
    }

    // Перегрузка оператора + для сложения матриц
    SparseMatrix operator+(const SparseMatrix &other) const
    {
        SparseMatrix result = *this;
        for (const auto &[key, value] : other.elements)
        {
            size_t row = key.first;
            size_t col = key.second;
            result.set(row, col, result.get(row, col) + value);
        }
        return result;
    }

    // Перегрузка оператора - для вычитания матриц
    SparseMatrix operator-(const SparseMatrix &other) const
    {
        SparseMatrix result = *this;
        for (const auto &[key, value] : other.elements)
        {
            size_t row = key.first;
            size_t col = key.second;
            result.set(row, col, result.get(row, col) - value);
        }
        return result;
    }

    // Транспонирование матрицы
    SparseMatrix transpose() const
    {
        SparseMatrix result(cols, rows);
        for (const auto &[key, value] : elements)
        {
            result.set(key.second, key.first, value);
        }
        return result;
    }

    // Умножение матриц
    SparseMatrix operator*(const SparseMatrix &other) const
    {
        // Проверка на совместимость размеров матриц для умножения
        if (cols != other.rows)
        {
            throw std::invalid_argument("Некорректные размеры матриц для умножения.");
        }

        SparseMatrix result(rows, other.cols);
        SparseMatrix otherT = other.transpose();

        for (const auto &[keyA, valA] : elements)
        {
            size_t row = keyA.first;
            size_t col = keyA.second;

            for (const auto &[keyB, valB] : otherT.elements)
            {
                if (keyB.first == col)
                {
                    result.set(row, keyB.second, result.get(row, keyB.second) + valA * valB);
                }
            }
        }

        return result;
    }

    // Умножение матрицы на вектор
    std::unordered_map<size_t, T> multiplyWithVector(const std::unordered_map<size_t, T> &vec) const
    {
        std::unordered_map<size_t, T> result;
        for (const auto &[key, value] : elements)
        {
            size_t row = key.first;
            size_t col = key.second;
            auto it = vec.find(col);
            if (it != vec.end())
            {
                result[row] += value * it->second;
            }
        }
        return result;
    }

    // Умножение матрицы на скаляр
    SparseMatrix operator*(T scalar) const
    {
        SparseMatrix result(rows, cols);
        for (const auto &[key, value] : elements)
        {
            result.set(key.first, key.second, value * scalar);
        }
        return result;
    }

    // Деление матрицы на скаляр
    SparseMatrix operator/(T scalar) const
    {
        SparseMatrix result(rows, cols);
        for (const auto &[key, value] : elements)
        {
            result.set(key.first, key.second, value / scalar);
        }
        return result;
    }

    // Поэлементное возведение в степень
    SparseMatrix powElements(T exponent) const
    {
        SparseMatrix result(rows, cols);
        for (const auto &[key, value] : elements)
        {
            result.set(key.first, key.second, std::pow(value, exponent));
        }
        return result;
    }

    // Обращение матрицы
    SparseMatrix inverse() const
    {
        // Проверка на квадратность матрицы
        if (rows != cols)
        {
            throw std::invalid_argument("Обращение возможно только для квадратных матриц.");
        }

        // Преобразуем разреженную матрицу в плотную для выполнения операции
        std::vector<std::vector<T>> dense(rows, std::vector<T>(cols, T(0)));
        for (const auto &[key, value] : elements)
        {
            dense[key.first][key.second] = value;
        }

        // Инициализируем единичную матрицу
        std::vector<std::vector<T>> inv(rows, std::vector<T>(cols, T(0)));
        for (size_t i = 0; i < rows; ++i)
        {
            inv[i][i] = T(1);
        }

        // Применяем метод Гаусса для обратной матрицы
        for (size_t i = 0; i < rows; ++i)
        {
            // Поиск максимального элемента в столбце
            T maxEl = std::abs(dense[i][i]);
            size_t maxRow = i;
            for (size_t k = i + 1; k < rows; ++k)
            {
                if (std::abs(dense[k][i]) > maxEl)
                {
                    maxEl = std::abs(dense[k][i]);
                    maxRow = k;
                }
            }

            // Проверка на вырожденность
            if (dense[maxRow][i] == T(0))
            {
                throw std::runtime_error("Матрица вырождена и не имеет обратной.");
            }

            // Перестановка строк
            std::swap(dense[i], dense[maxRow]);
            std::swap(inv[i], inv[maxRow]);

            // Приведение к единичной диагонали
            T diag = dense[i][i];
            for (size_t j = 0; j < cols; ++j)
            {
                dense[i][j] /= diag;
                inv[i][j] /= diag;
            }

            // Обнуление остальных элементов в столбце
            for (size_t k = 0; k < rows; ++k)
            {
                if (k != i)
                {
                    T factor = dense[k][i];
                    for (size_t j = 0; j < cols; ++j)
                    {
                        dense[k][j] -= factor * dense[i][j];
                        inv[k][j] -= factor * inv[i][j];
                    }
                }
            }
        }

        // Преобразуем плотную обратную матрицу обратно в разреженную
        SparseMatrix inverseMatrix(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                if (inv[i][j] != T(0))
                {
                    inverseMatrix.set(i, j, inv[i][j]);
                }
            }
        }

        return inverseMatrix;
    }

    // Возведение матрицы степень
    SparseMatrix pow(int exponent) const
    {
        // Проверка на квадратность матрицы
        if (rows != cols)
        {
            throw std::invalid_argument("Возведение в степень возможно только для квадратных матриц.");
        }
        if (exponent < 0)
        {
            SparseMatrix inv = this->inverse();
            return inv.pow(-exponent);
        }
        SparseMatrix result(rows, cols);
        // Инициализация единичной матрицы
        for (size_t i = 0; i < rows; ++i)
        {
            result.set(i, i, T(1));
        }
        SparseMatrix base = *this;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                result = result * base;
            }
            base = base * base;
            exponent /= 2;
        }
        return result;
    }

    // Вывод матрицы
    void print() const
    {
        for (const auto &[key, value] : elements)
        {
            std::cout << "(" << key.first << ", " << key.second << "): " << value << " ";
        }
        std::cout << std::endl;
    }

    // Получение всех ненулевых элементов для итерирования
    const std::unordered_map<std::pair<size_t, size_t>, T, pair_hash> &getElements() const
    {
        return elements;
    }

    // Получить количество строк
    size_t getRows() const
    {
        return rows;
    }

    // Получить количество столбцов
    size_t getCols() const
    {
        return cols;
    }

    // Операции сравнения
    bool operator==(const SparseMatrix &other) const
    {
        return elements == other.elements && rows == other.rows && cols == other.cols;
    }

    bool operator!=(const SparseMatrix &other) const
    {
        return !(*this == other);
    }
};

#endif
