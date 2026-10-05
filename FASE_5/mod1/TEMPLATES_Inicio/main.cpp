#include <iostream>
#include "GestorDual.hpp"

struct Articulo{
    std::string nombre;
    float precio;
    bool operator>(const Articulo& otro) const{ //Aqui enseño al struct a compararse (sobrecarga)
        return precio > otro.precio;
    }
};

int main(){
    //PRUEBA CON LOS TEMPLATES
    //Tipo int
    GestorDual<int> gdi(10, 20);
    std::cout << "El mayor es: " << gdi.obtener_mayor() << "\n";
    gdi.intercambiar();
    std::cout << "Despues de intercambiar, el mayor es: " << gdi.obtener_mayor() << "\n\n";
    //Tipo float
    GestorDual<float> gdf(9.99, 19.90);
    std::cout << "El mayor es: " << gdf.obtener_mayor() << "\n";
    gdf.intercambiar();
    std::cout << "Despues de intercambiar, el mayor es: " << gdf.obtener_mayor() << "\n\n";
    //Tipo string
    GestorDual<std::string> gds("C++", "Assembly");
    std::cout << "El mayor es: " << gds.obtener_mayor() << "\n";
    gds.intercambiar();
    std::cout << "Despues de intercambiar, el mayor es: " << gds.obtener_mayor() << "\n\n";
    //Tipo Articulo (struct)
    Articulo a1{"iPhone 17", 1799.84};
    Articulo a2{"Samsung a32", 690.99};
    GestorDual<Articulo> gda(a1, a2);
    Articulo mas_caro = gda.obtener_mayor();
    std::cout << "El mas caro es: " << mas_caro.nombre << " ($" <<  mas_caro.precio << ")." << "\n";
    gda.intercambiar();
    std::cout << "Despues de intercambiar, el mas caro es: " << mas_caro.nombre << " ($" <<  mas_caro.precio << ")." << "\n\n";
    return 0;
}