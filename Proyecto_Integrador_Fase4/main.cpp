#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <fstream>
#include <ctime>
#include <vector>

class Alumno{

};

void registrar_alumno(){ // Esta es la funcion de INSERTAR

}

void pedir_ayuda(){
    std::cout << "Los comandos disponibles son:\n1. [--ayuda]\n2. [--version]\n3. [--insertar]\n4. [--actualizar]\n5. [--consultar]\n6. [--forzar]\n7. [ver]\n8. [--apagar]";
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Faltan argumentos.\n";
        pedir_ayuda();
    }
    std::string comando = argv[1];
    if(comando == "--ayuda"){
        pedir_ayuda();
    } else if(comando == "--version"){
        std::cout << "CLI++ v.0.0.1" << std::endl;
    } else if(comando == "--insertar"){
        registrar_alumno();
    }
}