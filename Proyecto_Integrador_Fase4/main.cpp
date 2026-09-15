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
#include <unordered_map>

std::mutex mtx;
std::atomic<bool> motor_encendido(true);

class Alumno{
    private:
        std::atomic<int> calificacion;
        std::string nombre;
        std::atomic<int> registro;
    public:
        Alumno(std::string &&_nombre, int &&_registro, int &&_calificacion){
            calificacion = _calificacion;
            nombre = _nombre;
            registro = _registro;
        }
        int get_registro(){
            return registro;
        }
};

class BaseDeDatos{
    private:
        std::unordered_map<std::string, std::unique_ptr<Alumno>> alumnos_registrados;
    public:
        bool registrar_alumno(std::string &&nombre_alumno, int &&registro, int &&calificacion){ // Esta es la funcion de INSERTAR
            std::lock_guard guardia(mtx); //esto es lo primero, que es asegurar que nada ni nadie más modifique mis usuarios

            //paso 1: Crear la variable del nombre de usuario (username) de forma temporal
            std::string nombre_usuario_temp = "usuario";
            //paso 2: Ver el tamaño de mi mapa, para asignar un numero que concatenaré al nombre de usuario
            int numero_usuario = alumnos_registrados.size() + 1;
            //paso 3: Concatenar ambos
            std::string nombre_usuario = nombre_usuario_temp + std::to_string(numero_usuario);
            //paso 3.1: Verificar que no existe un usuariuo con el mismo username
            const auto &vf = alumnos_registrados.find(nombre_usuario);
            if(vf != alumnos_registrados.end()){
                std::cout << "El usuario " << nombre_usuario << " ya está registrado en la base de datos.\n";
                return false;
            }
            //paso 4: Crear el usuario, usando move semantics
            std::string nTemp = nombre_usuario;
            std::string naTemp = nombre_alumno;
            int rTemp = registro;
            int cTemp = calificacion;
            alumnos_registrados[std::move(nombre_usuario)] = std::make_unique<Alumno>(std::move(nombre_alumno), std::move(registro), std::move(calificacion));

            //Imprimo en pantalla todos los datos:
            
            std::cout << "Usuario registardo con exito, recuerda que los siguientes datos son indispensables para futuras modificaciones:\n1. [Usuario] : " << nTemp << "\n2. [Nombre completo] : " << naTemp << "\n3. [Registro] : " << rTemp << "\n4. [Calificacion] : " << cTemp << "\n";
            return true;
        }       

        bool actualizar_alumno(const std::string &nombre_usuario){
            const auto &vf = alumnos_registrados.find(nombre_usuario); // busco si el nombre de usuario existe
            if(vf == alumnos_registrados.end()){
                std::cout << "El nombre de usuario proporcionado no existe.\n";
                return false;
            }
            
            int registroTemp;
            std::cout << "Ingresa tu registro para verificar tu identidad:\n>> ";
            std::cin >> registroTemp;

            if(vf->second->get_registro() != registroTemp){
                std::cout << "El registro no coincide, operacion denegada.\n";
                return false; // aqui me quede. El paso siguiente es terminar la logica para actualizar la informacion del alumno. 
            }
        }
    };



void pedir_ayuda(){
    std::cout << "Los comandos disponibles son:\n1. [--ayuda]\n2. [--version]\n3. [--registrar]\n4. [--actualizar]\n5. [--consultar]\n6. [--forzar]\n7. [ver]\n8. [--apagar]";
}
void verificar_datos(std::string &nombre, int &registro, int &calificacion){
    while(nombre == ""){
        std::cout << "Ingresa un nombre valido:\n>> ";
        std::getline(std::cin, nombre);
    }
    while(registro <= 0){
        std::cout << "Ingresa un No. de registro valido:\n>> ";
        std::cin >> registro;
    }
    while(calificacion < 0){
        std::cout << "Ingresa una calificacion valida:\n>> ";
        std::cin >> calificacion;
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Faltan argumentos.\n";
        pedir_ayuda();
    }

    BaseDeDatos db;
    std::string comando = argv[1];

    std::string nombre;
    int registro;
    int calificacion;

    if(comando == "--ayuda"){
        pedir_ayuda();
    } else if(comando == "--version"){
        std::cout << "CLI++ v.0.0.1" << std::endl;
    } else if(comando == "--registrar"){
        std::cout << "Ingrese el nombre completo del alumno:\n>> ";
        std::getline(std::cin, nombre);
        std::cout << "Ingrese el No. de registro del alumno:\n>> ";
        std::cin >> registro;
        std::cout << "Ingrese la calificacion del alumno:\n >> ";
        std::cin >> calificacion;
        verificar_datos(nombre, registro, calificacion);
        db.registrar_alumno(std::move(nombre), std::move(registro), std::move(calificacion));
    } else{
        std::cout << "Comando no valido.\n";
        pedir_ayuda();
    }
}