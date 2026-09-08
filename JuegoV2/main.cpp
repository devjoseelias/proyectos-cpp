#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <vector>
#include <memory>
#include <random>

std::atomic<bool> estadoServidor(true); //esta variable atomica, es el estado del servidor
std::mutex mtx; //la llave para hacer modificaciones

int numeroAleatorio(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(377, 3769);
    
    int num = distrib(gen);
    return num;
}

class Jugador{
    private:
        int vida, exp;
        std::string IDunico;
        std::string nombre;
    public:
        Jugador(){
            vida = 100;
            exp = 0;
            nombre = "nuevojugador";
            int n = numeroAleatorio();
            IDunico = "ID-" + std::to_string(nombre.size() * n);
        }

        void bajarVida(){
            vida--;
        }

        void recibirDano(int dano){
            vida -= dano;
        }

        void presentarse(){
            std::cout << "\nNombre: " << nombre << "\nID: " << IDunico << "\nVida: " << vida << "\nEXP: " << exp << "\n\n";
        }
};

std::vector<std::unique_ptr<Jugador>> jugadoresConectados; //aqui tenemos a todos los jugadores conectados.

void motorJuego(){
    while(estadoServidor){
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::lock_guard guardia(mtx);
        if(jugadoresConectados.empty()){
            std::cout << "\n[SISTEMA]: No hay jugadores conectados\n";
            continue;
        } 

        for(size_t i = 0; i < jugadoresConectados.size(); i++){
           jugadoresConectados[i]->bajarVida();
        }
        std::cout << "\n[SISTEMA]: Vida de los jugadores baja 1hp\n";
    }
}

void conectarJugador(){
    std::lock_guard guardia(mtx);
    std::unique_ptr<Jugador> jugadorNuevo = std::make_unique<Jugador>();
    jugadoresConectados.push_back(std::move(jugadorNuevo));
}
void desconectarJugador(int posicion){
    std::lock_guard guardia(mtx);
    if(posicion > jugadoresConectados.size() || posicion < 1){
        std::cout << "Indice no válido.\n";
        return;
    }
    posicion--;
    jugadoresConectados.erase(jugadoresConectados.begin() + posicion);
}
void hacerDano(int posicion, int dano){
    std::lock_guard guardia(mtx);
    if(posicion > jugadoresConectados.size() || posicion < 1){
        std::cout << "Indice no válido.\n";
        return;
    }
    if(dano < 1 || dano > 100){
        dano = 1;
    }
    posicion--;
    jugadoresConectados[posicion]->recibirDano(dano);
}
void listarJugadores(){
    std::lock_guard guardia(mtx);
    for(size_t i = 0; i < jugadoresConectados.size(); i++){
        jugadoresConectados[i]->presentarse();
    }
}


int main(){
    std::thread hiloSecundario(motorJuego);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int accion; 
    int p, d;
    
    do{
        std::cout << "Ingrese una opcion:\n1. Conectar a un jugador\n2. Desconectar a un jugador\n3. Hacer daño a un jugador\n4. Listar jugadores\n5. Salir\n\n>> ";
        std::cin >> accion;
    
        while(accion < 1 || accion > 5){
            std::cout << "\n>> ";
            std::cin >> accion;
        }
        
        switch(accion){
            case 1: 
                conectarJugador();
                break;
            case 2:
                std::cout << "Ingrese la posicion del jugador:\n>> ";
                std::cin >> p;
                desconectarJugador(p);
                break;
            case 3:
                std::cout << "Ingrese la posicion del jugador:\n>> ";
                std::cin >> p;
                std::cout << "Ingrese cuanto daño (1-99):\n>> ";
                std::cin >> d;
                hacerDano(p, d);
                break;
            case 4:
                listarJugadores();
                break;
            default:
                estadoServidor = false;
                break;
        }
    } while(accion != 5);

    hiloSecundario.join();
    return 0;
}