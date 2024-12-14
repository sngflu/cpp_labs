#ifndef UTILITIES_H
#define UTILITIES_H

#include <utility>

// Хеш-функция для пары (используется в SparseMatrix)
struct pair_hash
{
    std::size_t operator()(const std::pair<size_t, size_t> &pair) const
    {
        // Простая комбинация хешей для пары
        return std::hash<size_t>()(pair.first) ^ (std::hash<size_t>()(pair.second) << 16);
    }
};

#endif
