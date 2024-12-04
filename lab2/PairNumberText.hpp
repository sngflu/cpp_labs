#ifndef PAIRNUMBERTEXT_HPP
#define PAIRNUMBERTEXT_HPP

#include <string>
#include <iostream>

class PairNumberText
{
private:
    int number;
    std::string text;

public:
    // конструктор по умолчанию
    PairNumberText();

    // конструктор с параметрами
    PairNumberText(int num, const std::string &str);

    // конструктор копирования
    PairNumberText(const PairNumberText &other);

    // конструктор перемещения
    PairNumberText(PairNumberText &&other) noexcept;

    // оператор присваивания (копирование)
    PairNumberText &operator=(const PairNumberText &other);

    // оператор присваивания (перемещение)
    PairNumberText &operator=(PairNumberText &&other) noexcept;

    // деструктор
    ~PairNumberText();

    // геттер для числа
    int getNumber() const;

    // геттер для текста
    std::string getText() const;

    // сеттер для числа
    void setNumber(int num);

    // сеттер для текста
    void setText(const std::string &str);
};

#endif
