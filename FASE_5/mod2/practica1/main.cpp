#include <iostream>
#include "formateador.hpp"

int main(){
    Formateador<int> fint;
    Formateador<double> fble;
    Formateador<bool> fool;

    int* ptr1 = nullptr;
    int valor_ptr2 = 21;
    int* ptr2 = &valor_ptr2;

    Formateador<int*> ptrintn;
    Formateador<int*> ptrintv;

    std::cout << fint.convertir(22092011) << std::endl;
    std::cout << fble.convertir(3.14159265) << std::endl;
    std::cout << fool.convertir(true) << std::endl;
    std::cout << fool.convertir(false) << std::endl;
    std::cout << ptrintn.convertir(ptr1) << std::endl;
    std::cout << ptrintv.convertir(ptr2) << std::endl;

    return 0;
}