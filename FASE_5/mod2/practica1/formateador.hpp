#pragma once

#include <iostream>
#include <concepts>
#include <type_traits>

template <typename T>  //Esto es el CONCEPT, que le dice al compilador que solo acepte tipos que se puedan sumar. Pero esto no es una plantilla, solo el requerimiento.
concept Aritmetico = requires(T a, T b){
    a + b;
};


template <typename T> //Esto es la plantilla, aqui se usa la sintexis en vez de typename, el nombre del concepto que useé. 
//Tambien uedo usar la sintaxis siguiente, en caso de que la restriccion fuese general:
/*
requires Aritmetico<T>
*/
class Formateador{
    public:
        std::string convertir(const T&valor)const requires Aritmetico<T>{
            return "Valor: " + std::to_string(valor);
        }
};


//Nota importante, ante el compilador, las clases que estan especializadas son clases completamente distintas, por ejemplo esta, cuyo tipo es explicito (bool), vavacia por lo mismo.
template <>
class Formateador<bool>{
    public:
        std::string convertir(const bool& valor) const{ // No uso T, porque el tipo que esta clase maneja al ser de especializacion total es bool.
            return valor ? "SI" : "NO";
        }
};

//Otra nota, existen especializaciones parciales, donde se usan familas de tipos, como los punteros, donde no sabes a que estas apuntando, asi quye si se usa T, pero mas adelante especificas T*
template <typename T>
class Formateador<T*>{
    public:
        std::string convertir(const T* valor) const{
            if(!valor) return "Puntero nulo.";
            return "Puntero a [" + std::to_string(*valor) + "]";
        }
};