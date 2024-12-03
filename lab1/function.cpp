#include <iostream>
int f() {
    int var1 = 1;
    double var2 = 2;
    std::cout << "Результат операции +: " << (var1 + var2) << std::endl;
    std::cout << "Результат операции -: " << (var1 - var2) << std::endl;
    std::cout << "Результат операции *: " << (var1 * var2) << std::endl;
    std::cout << "Результат операции /: " << (var1 / var2) << std::endl;
    return 0;
}
