#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "SparseVector.h"
#include "SparseMatrix.h"
#include "DenseVector.h"
#include "DenseMatrix.h"

int main()
{
    // Пример работы с разреженным вектором
    SparseVector<double> sparseVec1;
    sparseVec1.set(0, 1.5);
    sparseVec1.set(3, 2.5);
    sparseVec1.set(10, 3.5);

    SparseVector<double> sparseVec2;
    sparseVec2.set(3, 4.5);
    sparseVec2.set(5, 5.5);
    sparseVec2.set(10, -3.5);

    std::cout << "Разреженный Вектор 1: ";
    sparseVec1.print();

    std::cout << "Разреженный Вектор 2: ";
    sparseVec2.print();

    SparseVector<double> sparseVecSum = sparseVec1 + sparseVec2;
    std::cout << "Сумма Разреженных Векторов: ";
    sparseVecSum.print();

    double sparseDot = sparseVec1.dotProduct(sparseVec2);
    std::cout << "Скалярное произведение Разреженных Векторов: " << sparseDot << std::endl;

    SparseVector<double> sparseVecScaled = sparseVec1 * 2.0;
    std::cout << "Разреженный Вектор 1, умноженный на 2: ";
    sparseVecScaled.print();

    SparseVector<double> sparseVecPow = sparseVec1.powElements(2.0);
    std::cout << "Разреженный Вектор 1, возведенный в квадрат: ";
    sparseVecPow.print();

    // Пример работы с плотным вектором
    DenseVector<double> denseVec1;
    denseVec1.set(0, 1.5);
    denseVec1.set(3, 2.5);
    denseVec1.set(10, 3.5);

    DenseVector<double> denseVec2;
    denseVec2.set(3, 4.5);
    denseVec2.set(5, 5.5);
    denseVec2.set(10, -3.5);

    std::cout << "\nПлотный Вектор 1: ";
    denseVec1.print();

    std::cout << "Плотный Вектор 2: ";
    denseVec2.print();

    DenseVector<double> denseVecSum = denseVec1 + denseVec2;
    std::cout << "Сумма Плотных Векторов: ";
    denseVecSum.print();

    double denseDot = denseVec1.dotProduct(denseVec2);
    std::cout << "Скалярное произведение Плотных Векторов: " << denseDot << std::endl;

    DenseVector<double> denseVecScaled = denseVec1 * 2.0;
    std::cout << "Плотный Вектор 1, умноженный на 2: ";
    denseVecScaled.print();

    DenseVector<double> denseVecPow = denseVec1.powElements(2.0);
    std::cout << "Плотный Вектор 1, возведенный в квадрат: ";
    denseVecPow.print();

    // Пример работы с разреженной матрицей
    SparseMatrix<double> sparseMat1(3, 3);
    sparseMat1.set(0, 0, 1.0);
    sparseMat1.set(0, 2, 2.0);
    sparseMat1.set(1, 1, 5.0);
    sparseMat1.set(2, 2, 4.0);

    SparseMatrix<double> sparseMat2(3, 3);
    sparseMat2.set(0, 0, 4.0);
    sparseMat2.set(2, 2, 5.0);
    sparseMat2.set(1, 1, -3.0);

    std::cout << "\nРазреженная Матрица 1: ";
    sparseMat1.print();

    std::cout << "Разреженная Матрица 2: ";
    sparseMat2.print();

    SparseMatrix<double> sparseMatSum = sparseMat1 + sparseMat2;
    std::cout << "Сумма Разреженных Матриц: ";
    sparseMatSum.print();

    SparseMatrix<double> sparseMatProduct = sparseMat1 * sparseMat2;
    std::cout << "Произведение Разреженных Матриц: ";
    sparseMatProduct.print();

    SparseMatrix<double> sparseMatTransposed = sparseMat1.transpose();
    std::cout << "Транспонированная Разреженная Матрица 1: ";
    sparseMatTransposed.print();

    // Обращение матрицы
    try
    {
        SparseMatrix<double> sparseMatInverse = sparseMat1.inverse();
        std::cout << "Обратная Разреженная Матрица 1: ";
        sparseMatInverse.print();
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка при обращении Разреженной Матрицы 1: " << e.what() << std::endl;
    }

    // Возведение матрицы в степень
    try
    {
        SparseMatrix<double> sparseMatPow = sparseMat1.pow(2);
        std::cout << "Разреженная Матрица 1 в квадрате: ";
        sparseMatPow.print();
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка при возведении Разреженной Матрицы 1 в степень: " << e.what() << std::endl;
    }

    // Пример работы с плотной матрицей
    DenseMatrix<double> denseMat1(3, 3);
    denseMat1.set(0, 0, 1.0);
    denseMat1.set(0, 2, 2.0);
    denseMat1.set(1, 1, 2.0);
    denseMat1.set(2, 2, 4.0);

    DenseMatrix<double> denseMat2(3, 3);
    denseMat2.set(0, 0, 4.0);
    denseMat2.set(2, 0, 5.0);
    denseMat2.set(1, 1, -3.0);

    std::cout << "\nПлотная Матрица 1: \n";
    denseMat1.print();

    std::cout << "Плотная Матрица 2: \n";
    denseMat2.print();

    DenseMatrix<double> denseMatSum = denseMat1 + denseMat2;
    std::cout << "Сумма Плотных Матриц: \n";
    denseMatSum.print();

    DenseMatrix<double> denseMatProduct = denseMat1 * denseMat2;
    std::cout << "Произведение Плотных Матриц: \n";
    denseMatProduct.print();

    DenseMatrix<double> denseMatTransposed = denseMat1.transpose();
    std::cout << "Транспонированная Плотная Матрица 1: \n";
    denseMatTransposed.print();

    // Обращение матрицы
    try
    {
        DenseMatrix<double> denseMatInverse = denseMat1.inverse();
        std::cout << "Обратная Плотная Матрица 1: \n";
        denseMatInverse.print();
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка при обращении Плотной Матрицы 1: " << e.what() << std::endl;
    }

    // Возведение матрицы в степень
    try
    {
        DenseMatrix<double> denseMatPow = denseMat1.pow(2);
        std::cout << "Плотная Матрица 1 в квадрате: \n";
        denseMatPow.print();
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка при возведении Плотной Матрицы 1 в степень: " << e.what() << std::endl;
    }

    // Сравнение производительности
    const size_t largeSize = 100000;
    const size_t numNonZero = 1000;

    // Инициализация разреженного вектора
    SparseVector<double> largeSparseVec;
    for (size_t i = 0; i < numNonZero; ++i)
    {
        largeSparseVec.set(i * 100, 1.0);
    }

    // Инициализация плотного вектора
    DenseVector<double> largeDenseVec;
    for (size_t i = 0; i < numNonZero; ++i)
    {
        largeDenseVec.set(i * 100, 1.0);
    }

    // Тестирование сложения векторов
    auto start = std::chrono::high_resolution_clock::now();
    SparseVector<double> largeSparseSum = largeSparseVec + largeSparseVec;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSparse = end - start;
    std::cout << "\nВремя сложения разреженных векторов: " << durationSparse.count() << " секунд." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    DenseVector<double> largeDenseSum = largeDenseVec + largeDenseVec;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationDense = end - start;
    std::cout << "Время сложения плотных векторов: " << durationDense.count() << " секунд." << std::endl;

    // Тестирование скалярного произведения
    start = std::chrono::high_resolution_clock::now();
    double largeSparseDot = largeSparseVec.dotProduct(largeSparseVec);
    end = std::chrono::high_resolution_clock::now();
    durationSparse = end - start;
    std::cout << "\nВремя скалярного произведения разреженных векторов: " << durationSparse.count() << " секунд." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    double largeDenseDot = largeDenseVec.dotProduct(largeDenseVec);
    end = std::chrono::high_resolution_clock::now();
    durationDense = end - start;
    std::cout << "Время скалярного произведения плотных векторов: " << durationDense.count() << " секунд." << std::endl;

    // Тестирование умножения на скаляр
    start = std::chrono::high_resolution_clock::now();
    SparseVector<double> largeSparseScaled = largeSparseVec * 2.0;
    end = std::chrono::high_resolution_clock::now();
    durationSparse = end - start;
    std::cout << "\nВремя умножения разреженного вектора на скаляр: " << durationSparse.count() << " секунд." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    DenseVector<double> largeDenseScaled = largeDenseVec * 2.0;
    end = std::chrono::high_resolution_clock::now();
    durationDense = end - start;
    std::cout << "Время умножения плотного вектора на скаляр: " << durationDense.count() << " секунд." << std::endl;

    // Аналогичные тесты можно добавить для матриц

    // Тестирование возведения в степень матриц
    SparseMatrix<double> largeSparseMat(1000, 1000);
    // Заполнение разреженной матрицы
    for (size_t i = 0; i < 1000; ++i)
    {
        largeSparseMat.set(i, i, 2.0);
    }

    DenseMatrix<double> largeDenseMat(1000, 1000);
    // Заполнение плотной матрицы
    for (size_t i = 0; i < 1000; ++i)
    {
        largeDenseMat.set(i, i, 2.0);
    }

    // Возведение разреженной матрицы в степень
    start = std::chrono::high_resolution_clock::now();
    SparseMatrix<double> largeSparseMatPow = largeSparseMat.pow(3);
    end = std::chrono::high_resolution_clock::now();
    durationSparse = end - start;
    std::cout << "\nВремя возведения разреженной матрицы в степень 3: " << durationSparse.count() << " секунд." << std::endl;

    // Возведение плотной матрицы в степень
    start = std::chrono::high_resolution_clock::now();
    DenseMatrix<double> largeDenseMatPow = largeDenseMat.pow(3);
    end = std::chrono::high_resolution_clock::now();
    durationDense = end - start;
    std::cout << "Время возведения плотной матрицы в степень 3: " << durationDense.count() << " секунд." << std::endl;

    return 0;
}
