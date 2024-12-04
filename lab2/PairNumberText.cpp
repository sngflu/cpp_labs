#include "PairNumberText.hpp"

// конструктор по умолчанию
PairNumberText::PairNumberText() : number(0), text("zero")
{
    std::cout << "Default constructor" << std::endl;
}

// конструктор с параметрами
PairNumberText::PairNumberText(int num, const std::string &str) : number(num), text(str)
{
    std::cout << "Parameterized constructor" << std::endl;
}

// конструктор копирования
PairNumberText::PairNumberText(const PairNumberText &other) : number(other.number), text(other.text)
{
    std::cout << "Copy constructor" << std::endl;
}

// конструктор перемещения
PairNumberText::PairNumberText(PairNumberText &&other) noexcept : number(other.number), text(std::move(other.text))
{
    std::cout << "Move constructor" << std::endl;
    other.number = 0;
}

// оператор присваивания (копирование)
PairNumberText &PairNumberText::operator=(const PairNumberText &other)
{
    if (this != &other)
    {
        number = other.number;
        text = other.text;
        std::cout << "Copy assignment operator" << std::endl;
    }
    return *this;
}

// оператор присваивания (перемещение)
PairNumberText &PairNumberText::operator=(PairNumberText &&other) noexcept
{
    if (this != &other)
    {
        number = other.number;
        text = std::move(other.text);
        other.number = 0;
        std::cout << "Move assignment operator" << std::endl;
    }
    return *this;
}

// деструктор
PairNumberText::~PairNumberText()
{
    std::cout << "Destructor" << std::endl;
}

// геттер для числа
int PairNumberText::getNumber() const
{
    return number;
}

// геттер для текста
std::string PairNumberText::getText() const
{
    return text;
}

// сеттер для числа
void PairNumberText::setNumber(int num)
{
    number = num;
}

// сеттер для текста
void PairNumberText::setText(const std::string &str)
{
    text = str;
}
