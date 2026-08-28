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

        string getNombre(){
            return nombre;
        }
        int getDiasRestantes(){
            return diasRestantes;
        }
        int getPrioridad(){
            return prioridad;
        }


        void mostarTarea(){
            cout << "Tarea: " << nombre << "\tDias restantes: " << diasRestantes << "\n";
        }
        bool tareaCompletada(){
            return completada;
        }
};

class gestorTareas{
    private:
        vector<Tarea> ListaTareas;
    public:
        gestorTareas(){
            cout << "\n--- BIENVENIDO AL SISTEMA ---\n¡Hola! Te doy la bienvenida al gestor de tareas GTC++, con este gestor puedes crear, ver, administrar y eliminar tus tareas del día. Así mismo, nosotros nos encargamos de que todos tus pendientes permanezcan guardados en tu computadoras en archivos completamente seguros de formato .bin para asegurar una velocidad extraordinaria. A continuación, te muestro un menú con opciones para que comiences. (Recuerda que para elegir, debes: (1: SI, 2: NO)).\n" << endl;
        }

        void agregarTarea(){
            string n;
            int d, p;
            cout << "\nIngrese el nombre de la tarea: ";
            getline(cin, n);
            cout << "Ingrese los días restantes: ";
            cin >> d;
            cout << "Ingrese la prioridad de la tarea (1-10): ";
            cin >> p;
            cin.ignore();
            Tarea t(n, d, p);
            ListaTareas.push_back(t);
        }

        bool listarTareas(){
            cout << "\n----- LISTANDO TAREAS -----" << endl;
            if(ListaTareas.empty()){
                cout << "Lista de pendientes vacía." << endl;
                return false;
            }
            for(size_t i = 0; i < ListaTareas.size(); i++){
                cout << "\n" << i+1 << ".- " << ListaTareas[i].getNombre() << "\nDías Restantes: " << ListaTareas[i].getDiasRestantes() << "\nPrioridad: " << ListaTareas[i].getPrioridad() << "\n";
                if(ListaTareas[i].tareaCompletada()){
                    cout << "Completada" << endl;
                } else{
                    cout << "No completada" << endl;
                }
            }
            return true;
        }

        void completarUnaTarea(){
            int t;
            cout << "¿Qué tarea quieres completar?: ";
            cin >> t;
            while(t < 0 || t > ListaTareas.size()){
                cout << "tarea no encontrada. Ingresar de nuevo: ";
                cin >> t;
            }
            cout << "¿Deseas completar la tarea '" << ListaTareas[t-1].getNombre() << "'?: ";
            int decision;
            cin >> decision;
            while(decision < 1 || decision > 2){
                cin >> decision;
            }
            if(decision == 1){
                ListaTareas[t-1].completarTarea();
                cout << "Tarea completada." << endl;
            }
        }
        
};

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    gestorTareas g;
    bool activo = true;
    do{
        int seleccion;
        cout << "\n1. Ver tareas pendientes\n2. Agregar nueva tarea\n3. Completar tarea\n4. Salir\n\n>>  ";
        cin >> seleccion;
        cin.ignore();
        switch(seleccion){
            case 1:
                g.listarTareas();
                break;
            case 2:
                g.agregarTarea();
                break;
            case 3:
                g.completarUnaTarea();
                break;
            default:
                activo = false;
        }
    } while(activo);
    return 0;
}