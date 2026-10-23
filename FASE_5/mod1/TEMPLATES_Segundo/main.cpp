#include "pareja.hpp"
#include <iostream>

struct Articulo{
    std::string nombre;
    float precio;

    bool operator==(const Articulo& otro_articulo) const{
        if(otro_articulo.precio == precio) { return true; } else { return false; }
    }
};

int main(){
    Pairs<std::string, int> p1("Temperatura", 25);

    Pairs<float, int> p2(1.2, 5);
    Pairs<float, int> p3(1.2, 5);

    if(p2.es_igual(p3)){
        std::cout << "Son iguales\n";
    } else{
        std::cout << "Son diferentes\n";
    }

    Pairs<Articulo, int> p4(Articulo{"Laptop", 1799.75}, 101);
    Pairs<Articulo, int> p5(Articulo{"iPhone", 1800.00}, 102);

    if(p4.es_igual(p5)){
        std::cout << "Son iguales\n";
    } else{
        std::cout << "Son diferentes\n";
    }

    return 0;
}