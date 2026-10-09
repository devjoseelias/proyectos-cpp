#pragma once

#include <iostream>

template <typename T, typename U>
class Pairs{
    private:
        T primero;
        U segundo;
    public:
        // Constructor de la clase
        Pairs(const T& p, const U& s) : primero(p), segundo (s){}

        // Getters
        T get_primero() const {}
        U get_segundo() const {}

        // Métodos
        void mostrar() const {}
        bool es_igual(const Pairs<T, U>& otra_pareja) const {}
};

// Getter #1 | Retornar el 'primero'
template <typename T, typename U>
T Pairs<T, U>::get_primero() const{ return primero; }

// Getter #2 | Retornar el 'segundo'
template <typename T, typename U>
U Pairs<T, U>::get_segundo() const { return segundo; }

// Método #1 | Mostrar el par con formato '[primero, segundo]'
template <typename T, typename U>
void Pairs<T, U>::mostrar() const{
    std::cout << "[" << primero << ", " << segundo << "]" << std::endl;
}

// Método #2 | Comparar (==) y devolver falso si alguno de los dos elementos de otra pareja es diferente de uno de los mios.
template <typename T, typename U>
bool Pairs<T, U>::es_igual(const Pairs<T, U>& otra_pareja) const {
    if(otra_pareja->get_primero() == this->get_primero() && otra_pareja->get_segundo() == this->get_segundo()){
                return true;
            }
            return false;
}