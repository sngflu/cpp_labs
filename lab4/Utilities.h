#ifndef UTILITIES_H
#define UTILITIES_H

#include <utility>

// Определение структуры pair_hash, которая используется для хеширования пары значений
struct pair_hash
{
    // Перегрузка оператора () для выполнения хеширования пары
    std::size_t operator()(const std::pair<size_t, size_t> &pair) const
    {
        // Простая комбинация хешей для пары
        // Используется побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ (^) и побитовый сдвиг влево (<<)
        // std::hash<size_t>()(pair.first) - хеш первого элемента пары
        // std::hash<size_t>()(pair.second) - хеш второго элемента пары
        // (std::hash<size_t>()(pair.second) << 16) - сдвиг хеша второго элемента на 16 бит влево
        // ^ - побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ между хешем первого элемента и сдвинутым хешем второго элемента
        return std::hash<size_t>()(pair.first) ^ (std::hash<size_t>()(pair.second) << 16);
    }
};

#endif
