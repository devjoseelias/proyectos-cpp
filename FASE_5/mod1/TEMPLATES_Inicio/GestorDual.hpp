#pragma once

template <typename T> 
class GestorDual{
    private:
        T elemento1, elemento2;
    public:
        GestorDual(T _elemento1, T _elemento2);
        T obtener_mayor();
        void intercambiar();
};

template <typename T>
GestorDual<T>::GestorDual(T _elemento1, T _elemento2) : elemento1(_elemento1), elemento2(_elemento2){}

template <typename T>
T GestorDual<T>::obtener_mayor(){
    return (elemento1 > elemento2) ? elemento1 : elemento2;
}

template <typename T>
void GestorDual<T>::intercambiar(){
    T temp;
    temp = elemento1;
    elemento1 = elemento2;
    elemento2 = temp;
}