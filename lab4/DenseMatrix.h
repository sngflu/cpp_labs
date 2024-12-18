#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <vector>    // Для использования std::vector
#include <iostream>  // Для использования std::cout и std::endl
#include <cmath>     // Для использования std::abs и std::pow
#include <algorithm> // Для использования std::max и std::swap

// Определение шаблонного класса DenseMatrix
template <typename T>
class DenseMatrix
{
private:
    // Вектор векторов для хранения элементов матрицы
    std::vector<std::vector<T>> elements;
    // Количество строк в матрице
    size_t rows;
    // Количество столбцов в матрице
    size_t cols;

public:
    // Конструкторы

    // Конструктор по умолчанию, инициализирует матрицу нулями
    DenseMatrix(size_t rows = 0, size_t cols = 0)
        : rows(rows), cols(cols), elements(rows, std::vector<T>(cols, T(0))) {}

    // Конструктор копирования
    DenseMatrix(const DenseMatrix &other) = default;

    // Установка элемента матрицы
    void set(size_t row, size_t col, T value)
    {
        // Если индексы выходят за пределы текущих размеров матрицы, расширяем матрицу
        if (row >= rows || col >= cols)
        {
            if (row >= rows)
            {
                elements.resize(row + 1, std::vector<T>(cols, T(0)));
                rows = row + 1;
            }
            if (col >= cols)
            {
                for (auto &r : elements)
                {
                    r.resize(col + 1, T(0));
                }
                cols = col + 1;
            }
        }
        // Устанавливаем значение элемента
        elements[row][col] = value;
    }

    // Получение элемента матрицы
    T get(size_t row, size_t col) const
    {
        // Если индексы выходят за пределы текущих размеров матрицы, возвращаем 0
        if (row >= rows || col >= cols)
        {
            return T(0);
        }
        // Возвращаем значение элемента
        return elements[row][col];
    }

    // Перегрузка оператора + для сложения матриц
    DenseMatrix operator+(const DenseMatrix &other) const
    {
        // Определяем максимальные размеры результирующей матрицы
        size_t maxRows = std::max(rows, other.rows);
        size_t maxCols = std::max(cols, other.cols);
        DenseMatrix result(maxRows, maxCols);

        // Сложение элементов матриц
        for (size_t i = 0; i < maxRows; ++i)
        {
            for (size_t j = 0; j < maxCols; ++j)
            {
                T val1 = (i < rows && j < cols) ? elements[i][j] : T(0);
                T val2 = (i < other.rows && j < other.cols) ? other.elements[i][j] : T(0);
                result.set(i, j, val1 + val2);
            }
        }
        return result;
    }

    // Перегрузка оператора - для вычитания матриц
    DenseMatrix operator-(const DenseMatrix &other) const
    {
        // Определяем максимальные размеры результирующей матрицы
        size_t maxRows = std::max(rows, other.rows);
        size_t maxCols = std::max(cols, other.cols);
        DenseMatrix result(maxRows, maxCols);

        // Вычитание элементов матриц
        for (size_t i = 0; i < maxRows; ++i)
        {
            for (size_t j = 0; j < maxCols; ++j)
            {
                T val1 = (i < rows && j < cols) ? elements[i][j] : T(0);
                T val2 = (i < other.rows && j < other.cols) ? other.elements[i][j] : T(0);
                result.set(i, j, val1 - val2);
            }
        }
        return result;
    }

    // Транспонирование матрицы
    DenseMatrix transpose() const
    {
        // Создаем результирующую матрицу с транспонированными размерами
        DenseMatrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.set(j, i, elements[i][j]);
            }
        }
        return result;
    }

    // Умножение матриц
    DenseMatrix operator*(const DenseMatrix &other) const
    {
        // Проверка на совместимость размеров матриц для умножения
        if (cols != other.rows)
        {
            throw std::invalid_argument("Некорректные размеры матриц для умножения.");
        }
        DenseMatrix result(rows, other.cols);

        // Умножение матриц
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t k = 0; k < cols; ++k)
            {
                if (elements[i][k] != T(0))
                {
                    for (size_t j = 0; j < other.cols; ++j)
                    {
                        result.elements[i][j] += elements[i][k] * other.elements[k][j];
                    }
                }
            }
        }
        return result;
    }

    // Умножение матрицы на вектор
    std::vector<T> multiplyWithVector(const std::vector<T> &vec) const
    {
        // Проверка на совместимость размеров матрицы и вектора
        if (cols != vec.size())
        {
            throw std::invalid_argument("Некорректные размеры для умножения матрицы на вектор.");
        }
        std::vector<T> result(rows, T(0));

        // Умножение матрицы на вектор
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[i] += elements[i][j] * vec[j];
            }
        }
        return result;
    }

    // Умножение матрицы на скаляр
    DenseMatrix operator*(T scalar) const
    {
        DenseMatrix result(*this);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.elements[i][j] *= scalar;
            }
        }
        return result;
    }

    // Деление матрицы на скаляр
    DenseMatrix operator/(T scalar) const
    {
        DenseMatrix result(*this);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.elements[i][j] /= scalar;
            }
        }
        return result;
    }

    // Поэлементное возведение в степень
    DenseMatrix powElements(T exponent) const
    {
        DenseMatrix result(*this);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.elements[i][j] = std::pow(elements[i][j], exponent);
            }
        }
        return result;
    }

    // Обращение матрицы (только для квадратных матриц)
    DenseMatrix inverse() const
    {
        // Проверка на квадратность матрицы
        if (rows != cols)
        {
            throw std::invalid_argument("Обращение возможно только для квадратных матриц.");
        }

        // Инициализация плотной копии матрицы и единичной матрицы
        std::vector<std::vector<T>> dense = elements;
        std::vector<std::vector<T>> inv(rows, std::vector<T>(cols, T(0)));
        for (size_t i = 0; i < rows; ++i)
        {
            inv[i][i] = T(1);
        }

        // Метод Гаусса для обращения матрицы
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

        // Создание разреженной обратной матрицы
        DenseMatrix inverseMatrix(rows, cols);
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
    DenseMatrix pow(int exponent) const
    {
        // Проверка на квадратность матрицы
        if (rows != cols)
        {
            throw std::invalid_argument("Возведение в степень возможно только для квадратных матриц.");
        }
        if (exponent < 0)
        {
            DenseMatrix inv = this->inverse();
            return inv.pow(-exponent);
        }
        DenseMatrix result(rows, cols);
        // Инициализация единичной матрицы
        for (size_t i = 0; i < rows; ++i)
        {
            result.set(i, i, T(1));
        }
        DenseMatrix base = *this;
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
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                std::cout << elements[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Получение всех элементов для итерирования
    const std::vector<std::vector<T>> &getElements() const
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
    bool operator==(const DenseMatrix &other) const
    {
        return elements == other.elements && rows == other.rows && cols == other.cols;
    }

    bool operator!=(const DenseMatrix &other) const
    {
        return !(*this == other);
    }
};

#endif