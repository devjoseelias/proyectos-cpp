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
            
            cout << "Ingrese el nombre de la tarea: ";
            getline(cin, n);

            while(true){
                cout << "Ingrese los días restantes para completar la tarea: ";
                cin >> d;

                if(cin.fail() || d < 0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Periodo de tiempo no válido. Ingrese un numero mayor o igual que 0." << endl;
                } else{
                    break;
                }
            }

            while(true){
                cout << "Ingrese la prioridad de la tarea (1-10): ";
                cin >> p;
                
                if(cin.fail() || p < 1 || p > 10){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Prioridad no válida. Ingrese un numero del 1 al 10." << endl;
                } else{
                    break;
                }
            }

            cin.ignore(10000, '\n');
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
            if(ListaTareas.empty()){
                cout << "No hay tareas para completar." << endl;
                return;
            }
            int t;
            cout << "¿Qué tarea quieres completar?: ";
            cin >> t;

            if(cin.fail() || t < 1 ||  t > ListaTareas.size()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Indice no válido." << endl;
                return;
            }

            cout << "¿Deseas completar la tarea '" << ListaTareas[t-1].getNombre() << "'?: ";
            int decision;
            cin >> decision;

            if(cin.fail() || decision != 1){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Acción cancelada." << endl;
                return;
            }
            ListaTareas[t-1].completarTarea();
            cout << "Tarea completada con éxito." << endl;
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