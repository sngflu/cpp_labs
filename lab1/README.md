# Лабораторная работа №1: Генерация программы на C++

## Описание
Данная работа демонстрирует принципы работы с вводом/выводом, файловым вводом-выводом, типами данных, а также основы создания и компиляции программ. Цель работы — создать программу-генератор, которая на основе введённых данных и заданных операций автоматически генерирует исходный код функции на C++ и вызывает её.

---

## Содержание

### 1. Программа-генератор `generator.cpp`
Программа принимает на вход два типа данных (например, `int`, `double`) и считывает файл `operations.txt`, содержащий список арифметических операций. На основе этого она генерирует файл `function.cpp`, который содержит функцию `f()`. В этой функции создаются переменные указанных типов, выполняются арифметические операции и выводятся результаты.

**Пример ввода:**
```plaintext
Введите первый тип данных: int
Введите второй тип данных: double
```

**Пример файла `operations.txt`**:
```plaintext
+
-
*
/
```

**Пример сгенерированного файла `function.cpp`**:
```cpp
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
```

### 2. Программа вызова `main.cpp`

Программа подключает сгенерированный файл function.cpp и вызывает функцию f(), чтобы продемонстрировать её работу.

### Запуск программы

**Компиляция генератора**
Скомпилируйте и запустите программу-генератор:
```bash
g++ generator.cpp -o generator
./generator
```

**Компиляция сгенерированного файла**
Скомпилируйте и выполните программу, вызывающую функцию:
```bash
g++ main.cpp -o main
./main
```

### Пример вывода

Для типов `int` и `double` и операций `+`, `-`, `*`, `/`:

```plaintext
Результат операции +: 3
Результат операции -: -1
Результат операции *: 2
Результат операции /: 0.5
```

### Альтернативный запуск

Чтобы не прописывать все команды отдельно можно воспользоваться командой `make run`.

### Недостатки

1. Программа не проверяет совместимость типов данных, что может привести к ошибке.
2. Программа реализует только простые математические операции.
3. Нет проверки деления на 0.