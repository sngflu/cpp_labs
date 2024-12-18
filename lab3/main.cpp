#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <random>
#include "Mainclass.hpp"

using namespace std;


void print_list_numbers(const list<Mainclass>& lst, int n, const string& description) {
    cout << description << " (показывается до " << n << " элементов):" << endl;
    auto it = lst.begin();
    for (int i = 0; i < n && it != lst.end(); ++i, ++it) {
        cout << *(it->get_number()) << endl;
    }
    cout << endl;
}
void print_list_pairs(const list<pair<Mainclass, Mainclass>>& lst, int n, const string& description) {
    cout << description << " (показывается до " << n << " пар):" << endl;
    auto it = lst.begin();
    for (int i = 0; i < n && it != lst.end(); ++i, ++it) {
        cout << "(" << *(it->first.get_number()) << ", " << *(it->second.get_number()) << ")" << endl;
    }
    cout << endl;
}





int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // 1. Создать вектор v1
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist_size(500, 1000);
    uniform_int_distribution<> dist_num(0, 1000);
    uniform_int_distribution<> dist_vec_size(0, 10);

    int v1_size = dist_size(gen);
    vector<Mainclass> v1;
    v1.reserve(v1_size);

    generate_n(back_inserter(v1), v1_size, [&]() {
        int random_num = dist_num(gen);
        string random_desc = "Desc" + to_string(v1.size());
        vector<int> random_vec(dist_vec_size(gen));
        generate(random_vec.begin(), random_vec.end(), [&]() { return dist_num(gen); });
        return Mainclass(random_num, random_desc, random_vec);
    });
    cout << "Вектор v1 создан с количеством элементов: " << v1.size() << "." << endl;

    // 2. Создать вектор v2 из последних 200 элементов v1
    int b = uniform_int_distribution<>(0, v1.size() - 200)(gen); // случайное начало диапазона
    int e = b + 200; // конец диапазона
    vector<Mainclass> v2;
    copy(v1.begin() + b, v1.begin() + e, back_inserter(v2));
    cout << "Вектор v2 создан из элементов с позиций " << b << " до " << e - 1 << ". Размер: " << v2.size() << " элементов." << endl;

    // 3. Сформировать список list1 из первых n наибольших элементов вектора v1
    const int n = uniform_int_distribution<>(20, 50)(gen);
    partial_sort(v1.begin(), v1.begin() + n, v1.end(), [](const Mainclass& a, const Mainclass& b) {
        return *(a.get_number()) > *(b.get_number());
    });
    list<Mainclass> list1(v1.begin(), v1.begin() + n);
    cout << "Список list1 создан с " << n << " наибольшими элементами из v1." << endl;
    print_list_numbers(list1, 10, "Первые 10 чисел из List1");

    // 4. Сформировать список list2 из последних n наименьших элементов вектора v2
    partial_sort(v2.begin(), v2.begin() + n, v2.end(), [](const Mainclass& a, const Mainclass& b) {
        return *(a.get_number()) < *(b.get_number());
    });
    list<Mainclass> list2(v2.begin(), v2.begin() + n);
    cout << "Список list2 создан с " << n << " наименьшими элементами из v2." << endl;
    print_list_numbers(list2, 10, "Первые 10 чисел из List2");

    // 5. Удалить перемещенные элементы из векторов v1 и v2
    v1.erase(v1.begin(), v1.begin() + n);
    v2.erase(v2.begin(), v2.begin() + n);
    cout << "Элементы удалены из v1 и v2. Новые размеры: v1 = " << v1.size() << ", v2 = " << v2.size() << "." << endl;

    // 6. Найти среднее значение в list1 и перегруппировать
    double average = accumulate(list1.begin(), list1.end(), 0.0,
        [](double sum, const Mainclass& obj) { return sum + *(obj.get_number()); }) / list1.size();

    list1.sort([average](const Mainclass& a, const Mainclass& b) {
        return *(a.get_number()) > average;
    });
    cout << "Список list1 перегруппирован: элементы больше среднего (" << average << ") размещены первыми." << endl;
    print_list_numbers(list1, 10, "Первые 10 перегруппированных чисел из List1");

    // 7. Удалить из list2 все нечетные элементы
    list2.remove_if([](const Mainclass& obj) { return *(obj.get_number()) % 2 != 0; });
    cout << "Удалены нечетные элементы из list2. Новый размер: " << list2.size() << "." << endl;
    print_list_numbers(list2, 10, "Первые 10 чисел из List2 после удаления нечетных");

    // 8. Создать вектор v3 с общими элементами из v1 и v2
    // ОБЯЗАТЕЛЬНА СОРТИРОВКА
    sort(v1.begin(), v1.end(), [](const Mainclass& a, const Mainclass& b) {
    return *(a.get_number()) < *(b.get_number());
    });
    sort(v2.begin(), v2.end(), [](const Mainclass& a, const Mainclass& b) {
        return *(a.get_number()) < *(b.get_number());
    });
    vector<Mainclass> v3;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3),
        [](const Mainclass& a, const Mainclass& b) { return *(a.get_number()) < *(b.get_number()); });
    cout << "Вектор v3 создан с " << v3.size() << " общими элементами между v1 и v2." << endl;

    // 9. Уравнять размеры list1 и list2, создать list3
    auto it1 = next(list1.begin(), min(list1.size(), list2.size()));
    auto it2 = next(list2.begin(), min(list1.size(), list2.size()));

    list1.erase(it1, list1.end());
    list2.erase(it2, list2.end());

    list<pair<Mainclass, Mainclass>> list3;
    transform(list1.begin(), list1.end(), list2.begin(), back_inserter(list3), [](const Mainclass& a, const Mainclass& b) {
        return make_pair(a, b);
    });
    cout << "Список list3 создан с парами элементов. Размер: " << list3.size() << "." << endl;
    print_list_pairs(list3, 10, "Первые 10 пар из List3");

    // 10. Решить задачу для v1 и v2 без приведения к одному размеру
    vector<pair<Mainclass, Mainclass>> pairs;
    transform(v1.begin(), v1.begin() + min(v1.size(), v2.size()), v2.begin(), back_inserter(pairs), [](const Mainclass& a, const Mainclass& b) {
        return make_pair(a, b);
    });
    cout << "Пары созданы из v1 и v2 без изменения размеров. Всего пар: " << pairs.size() << "." << endl;
    return 0;
}
