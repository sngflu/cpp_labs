#include "PairNumberText.hpp"
#include <vector>
#include <list>

// функция для обработки вектора
void processVector(const std::vector<PairNumberText> &vec)
{
    std::cout << "\nProcessing vector..." << std::endl;
    for (const auto &item : vec)
    {
        std::cout << "Number: " << item.getNumber() << ", Text: " << item.getText() << std::endl;
    }
}

// функция, возвращающая экземпляр класса
PairNumberText createInstance()
{
    return PairNumberText(52, "fifty-two");
}

// функция, изменяющая экземпляр класса
void modifyInstance(PairNumberText &instance)
{
    instance.setNumber(88);
    instance.setText("eighty-eight");
}

int main()
{
    // создание статического экземпляра
    PairNumberText staticInstance(10, "ten");
    std::cout << "\nStatic instance created" << std::endl;

    // создание динамического экземпляра
    PairNumberText *dynamicInstance = new PairNumberText(15, "fifteen");
    std::cout << "\nDynamic instance created" << std::endl;

    // создание и обработка вектора
    std::vector<PairNumberText> vec;
    vec.emplace_back(1, "one");
    vec.emplace_back(2, "two");
    vec.emplace_back(3, "three");
    processVector(vec);

    // создание и изменение экземпляра класса
    PairNumberText newInstance = createInstance();
    modifyInstance(newInstance);

    // работа со списком
    std::list<PairNumberText> lst;
    lst.emplace_back(4, "four");
    lst.emplace_back(5, "five");
    lst.emplace_back(6, "six");

    for (const auto &item : lst)
    {
        std::cout << "List item: " << item.getNumber() << ", " << item.getText() << std::endl;
    }

    // удаление динамического экземпляра
    delete dynamicInstance;
    std::cout << "\nDynamic instance deleted" << std::endl;

    return 0;
}
