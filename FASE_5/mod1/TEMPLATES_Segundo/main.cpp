#include "pareja.hpp"
#include <iostream>

struct Articulo{
    std::string nombre;
    float precio;

    bool operator==(const Articulo& otro_articulo){
        if(otro_articulo.precio == precio) { return true; } else { return false; }
    }
};

int main(){

    return 0;
}