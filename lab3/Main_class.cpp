#include "Mainclass.hpp"


Mainclass::Mainclass()
    : number(new int(0)), description(new string("Default")), number_vector(new vector<int>()) {
  
}

Mainclass::Mainclass(int num, const string& desc, const vector<int>& number_vec)
    : number(new int(num)), description(new string(desc)), number_vector(new vector<int>(number_vec)) {
   
}

Mainclass::Mainclass(const Mainclass& v)
    : number(new int(*v.number)), 
      description(new string(*v.description)), 
      number_vector(new vector<int>(*v.number_vector)) {
 
}

Mainclass::Mainclass(Mainclass&& v) noexcept
    : number(v.number), description(v.description), number_vector(v.number_vector) {
    v.number = nullptr;
    v.description = nullptr;
    v.number_vector = nullptr;

    }

Mainclass& Mainclass::operator=(const Mainclass& v) {
    if (this != &v) {
        *number = *v.number;
        *description = *v.description;
        *number_vector = *v.number_vector;
    }
    return *this;
}


Mainclass& Mainclass::operator=(Mainclass&& v) noexcept {
    if (this != &v) {
        delete number;
        delete description;
        delete number_vector;
        number = v.number;
        description = v.description;
        number_vector = v.number_vector;
        v.number = nullptr;
        v.description = nullptr;
        v.number_vector = nullptr;
    }
    return *this;
}


Mainclass::~Mainclass() {
    delete number;
    delete description;
    delete number_vector; 
   
}


void Mainclass::show_data() const {
    cout << "Number: " << *number << "\nDescription: " << *description << "\nVector: ";
    for (int num : *number_vector) {
        cout << num << " ";
    }
   
}
