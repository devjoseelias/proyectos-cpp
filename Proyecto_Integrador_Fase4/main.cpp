#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <fstream>
#include <filesystem>
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
        std::string get_nombre(){
            return nombre;
        }
        int get_calificacion(){
            return calificacion;
        }

        bool set_calificacion(int _calificacion){
            if(_calificacion < 1){
                return false;
            }
            calificacion = _calificacion;
            return true;
        }
        bool set_registro(int _registro){
            if(_registro <= 0){
                return false;
            }
            registro = _registro;
            return true;
        }
        bool set_nombre(std::string _nombre){
            if(nombre == ""){
                return false;
            }
            nombre = _nombre;
            return true;
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

        bool actualizar_alumno(const std::string &nombre_usuario, const std::string &info){ //Esta es la funcion ACTUALIZAR
            std::lock_guard guardia(mtx);
            const auto &vf = alumnos_registrados.find(nombre_usuario); // busco si el nombre de usuario existe
            if(vf == alumnos_registrados.end()){ // SI el usuario con el nombre no  existe
                std::cout << "El nombre de usuario proporcionado no existe.\n";
                return false; //niego la operacion
            }
            
            int registroTemp;
            std::cout << "Ingresa tu registro actual para verificar tu identidad:\n>> ";
            std::cin >> registroTemp;

            if(vf->second->get_registro() != registroTemp){ //Si el registro ingresado no coincide
                std::cout << "El registro no coincide, operacion denegada.\n";
                return false; // niego la operacion 
            }

            std::cout << "Aprobado.\n";
            if(info == "nombre"){
                std::string nombre_actual = vf->second->get_nombre();
                std::string nuevo_nombre = "";
                while(nuevo_nombre == "" || nuevo_nombre == nombre_actual){
                    std::cout << "\nIngrese el nuevo nombre:\n>> ";
                    std::getline(std::cin, nuevo_nombre);
                }
                if(vf->second->set_nombre(nuevo_nombre)){
                    std::cout << "\nExito. Nuevo nombre establecido.\n";
                    return true;
                } else{
                    std::cout << "\nError al establecer nuevo nombre.\n";
                    return false;
                }

            } else if(info == "registro"){
                int registro_actual = vf->second->get_registro();
                int nuevo_registro = 0;
                while(nuevo_registro <= 0 || nuevo_registro == registro_actual){
                    std::cout << "\nIngrese el nuevo No. de registro:\n>> ";
                    std::cin >> nuevo_registro;
                }
                if(vf->second->set_registro(nuevo_registro)){
                    std::cout << "\nExito. Nuevo registro establecido.\n";
                    return true;
                } else{
                    std::cout << "\nError al actualizar el registro.\n";
                    return false;
                }

            } else if(info == "calificacion"){
                int calificacion_actual = vf->second->get_calificacion();
                int nueva_calificacion = 0;
                while(nueva_calificacion == 0 || nueva_calificacion == calificacion_actual){
                    std::cout << "\nIngrese la nueva calificacion:\n>> ";
                    std::cin >> nueva_calificacion;
                }
                if(vf->second->set_calificacion(nueva_calificacion)){
                    std::cout << "\nExito. Nueva calificacion establecida.\n";
                    return true;
                } else{
                    std::cout << "\nError al establecer la nueva calificacion.\n";
                    return false;
                }
            } else{
                std::cout << "\nEl argumento '" << info << "' no es valido. Los argumentos validos para [--actualizar] son:\n 1. [--actualizar nombre]\n2. [--actualizar registro]\n3. [--actualizar calificacion]\n";
                return false;
            }
            return false;
        }
        
        bool consultar_alumno(const std::string &nombre_usuario){ //Esta es la funcion CONSULTAR
            std::lock_guard guardia(mtx);
            const auto &vf = alumnos_registrados.find(nombre_usuario); //paso 1: buscar el nombre nos proporcionan
            if(vf == alumnos_registrados.end()){ //paso 2: si no existe
                std::cout << "\nNombre de usuario no valido. Reintenta o registra al usuario.\n";
                return false;
            }
            std::cout << "\nLos datos del alumno son:\n1. Nombre completo: " << vf->second->get_nombre() << "\n2. Calificacion: " << vf->second->get_calificacion() << "\nEl registro no se puede proporcionar, dado que es informacion privada y requerida para otras operaciones.\n";
            return true;
        }
    
        bool guardar_en_disco(){
            while(motor_encendido){
                std::this_thread::sleep_for(std::chrono::seconds(3)); //paso 1: dormimos 3 segundos mientras el motor este activo
                std::ofstream arch("baseDatos.dat", std::ios::binary); //declaramos el archivo
                if(!arch.is_open()){ //si no esta abierto
                    std::cout << "Error al abrir el archivo de escritura.\n";
                    return false;
                }
                std::lock_guard guardia(mtx); //bloque para evitar data races
                size_t total_alumnos = alumnos_registrados.size(); //leo el tamaño de mi hashmap
                arch.write(reinterpret_cast<const char*>(&total_alumnos), sizeof(total_alumnos));  //escribo el tamaño de mi hashmap (se usa reinterpret cast pq es un size_t, y uso sizeof() por lo mismo, que pesa 8bytes)
                
                for(const auto &alumno : alumnos_registrados){
                    size_t tamano_nombre_usuario = alumno.first.size(); //tomo el TAMAÑO del username
                    arch.write(reinterpret_cast<const char*>(&tamano_nombre_usuario), sizeof(tamano_nombre_usuario));//Escribo el TAMAÑO del username
                    arch.write(alumno.first.c_str(), tamano_nombre_usuario);//Escribo el USERNAME

                    //paso 2: escribir el nombre
                    size_t tamano_nombre = alumno.second->get_nombre().size(); //calculo el tamaño del username
                    arch.write(reinterpret_cast<const char*>(&tamano_nombre), sizeof(tamano_nombre));//escribo el tamaño del nombre
                    arch.write(alumno.second->get_nombre().c_str(), sizeof(tamano_nombre));

                    //paso 3: escribir el registro
                    //aqui no voy a ocupar el size t porque estoy tratando con un entero
                    size_t rTemp = alumno.second->get_registro();
                    arch.write(reinterpret_cast<const char*>(&rTemp), sizeof(rTemp));
                    //paso 4: escribir la calificacion
                    size_t cTemp = alumno.second->get_calificacion();
                    arch.write(reinterpret_cast<const char*>(&cTemp), sizeof(cTemp));
                }
                arch.close();
                std::cout << "\nGuardado correctamente.\n";
                return true;
            }
            return true;
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
    std::thread guardado_sp(BaseDeDatos::guardar_en_disco, &db); //el hilo que hara el guardado en segundo plano.
    guardado_sp.detach();
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
    } else if(comando == "--actualizar"){
        if(argc < 3){
            std::cout << "Faltan argumentos para la llamada a [--actualizar]\nIntenta con:\n1. [--actualizar nombre]\n2. [--actualizar registro]\n3. [--actualizar calificacion]\n";
            return 1;
        }
        std::string informacion_a_modificar = argv[2];
        std::string nombre_usuario;
        std::cout << "\nIngrese el nombre de usuario:\n>> ";
        std::cin >> nombre_usuario;

        db.actualizar_alumno(nombre_usuario, informacion_a_modificar);
    } else if(comando == "--consultar"){
        if(argc < 3){
            std::cout << "Faltan argmentos para la llamada a [--consultar]. Prueba con [--consultar nombre_usuario]\n";
            return 1;
        }
        db.consultar_alumno(argv[2]);
    } else{
        std::cout << "Comando no valido.\n";
        motor_encendido = false;
        pedir_ayuda();
    }
    guardado_sp.join();
    return 0;
}