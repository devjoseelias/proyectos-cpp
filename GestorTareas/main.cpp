#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::vector;

void verificarDatos(string &n, int &d, int &p){
    while(n == ""){
        cout << "Ingrese un nombre válido para la tarea: ";
        getline(cin, n);
    }
    while(d < 0){
        cout << "Ingrese un periodo válido: ";
        cin >> d;
    }
    while(p < 1){
        cout << "Ingrese una prioridad válida: ";
        cin >> p;
    }
}

class Tarea{
    private:
        string nombre = "Nueva tarea";
        int diasRestantes = 0, prioridad = 1;
        bool completada = false;
    public:
        Tarea(){
            mostarTarea();
        }
        Tarea(string n, int d, int p){
            verificarDatos(n, d, p);
            nombre = n;
            diasRestantes = d;
            prioridad = p;
        }

        void asignarPrioridad(int p){
            if(p > 0){
                prioridad = p;
            }
        }
        void asignarNombreATarea(string n){
            if(n != ""){
                nombre = n;
            }
        }
        void asignarDiasRestantesATarea(int d){
            if(d >= 0){
                diasRestantes = d;
            } else{
                diasRestantes = 0;
            }
        }
        void completarTarea(){
            completada = true;
        }
        void descompletarTarea(){
            completada = false;
        }


        void mostarTarea(){
            cout << "Tarea: " << nombre << "\nDias restantes: " << diasRestantes << "\n\n";
        }
        bool tareaCompletada(){
            return completada;
        }
};

class gestorTareas{
    private:
        vector<Tarea> ListasTareas;
    public:
        gestorTareas(){
            cout << "\n--- BIENVENIDO AL SISTEMA ---\n¡Hola! Te doy la bienvenida al gestor de tareas GTC++, con este gestor puedes crear, ver, administrar y eliminar tus tareas del día. Así mismo, nosotros nos encargamos de que todos tus pendientes permanezcan guardados en tu computadoras en archivos completamente seguros de formato .bin para asegurar una velocidad extraordinaria. A continuación, te muestro un menú con opciones para que comiences. \n" << endl;
        }

        
};

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    gestorTareas g;
    return 0;
}