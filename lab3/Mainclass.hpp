#ifndef MAINCLASS_HPP
#define MAINCLASS_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Mainclass {
private:
    int* number;                
    string* description;          
    vector<int>* number_vector;   

public:
    int* get_number() const {
        return number;
    }
    Mainclass();
    Mainclass(int num, const string& desc, const vector<int>& number_vec);
    Mainclass(const Mainclass& v);
    Mainclass(Mainclass&& v) noexcept;
    Mainclass& operator=(const Mainclass& v);
    Mainclass& operator=(Mainclass&& v) noexcept;
    ~Mainclass();
    void show_data() const;
};

#endif
