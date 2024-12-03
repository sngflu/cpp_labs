#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string type1, type2;
    int num1, num2;

    cout << "Введите первый тип данных: ";
    cin >> type1;
    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите второй тип данных: ";
    cin >> type2;
    cout << "Введите второе число: ";
    cin >> num2;

    ifstream fin("operations.txt");

    vector<string> operations;
    string operation;
    while (getline(fin, operation))
    {
        operations.push_back(operation);
    }
    fin.close();

    ofstream fout("function.cpp");
    fout << "#include <iostream>" << endl;
    fout << "int f() {" << endl;
    fout << "    " << type1 << " var1 = " << num1 << ";" << endl;
    fout << "    " << type2 << " var2 = " << num2 << ";" << endl;

    for (size_t i = 0; i < operations.size(); ++i)
    {
        fout << "    std::cout << \"Результат операции " << operations[i]
             << ": \" << (var1 " << operations[i] << " var2) << std::endl;" << endl;
    }

    fout << "    return 0;" << endl;
    fout << "}" << endl;
    fout.close();

    cout << "Файл function.cpp успешно создан!" << endl;
    return 0;
}
