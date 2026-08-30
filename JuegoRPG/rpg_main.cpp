#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Entidad {
// Usamos protected para que las futuras clases hijas puedan acceder a estas variables
protected: 
    string nombre;
    int hp;       // Puntos de vida (Health Points)
    int danoBase; // Daño estándar

public:
    // Constructor de la clase base
    Entidad(string _nombre, int _hp, int _danoBase) {
        nombre = _nombre;
        hp = _hp;
        danoBase = _danoBase;
    }

    virtual ~Entidad(){}

    // Método general que usarán todos los personajes para recibir daño
    void recibirDano(int cantidad) {
        hp -= cantidad;
        if (hp < 0) hp = 0; // Evitamos que la vida baje a números negativos
        
        cout << nombre << " recibe " << cantidad << " de dano. HP restante: " << hp << endl;
    }

    // Usamos 'const' al final de las funciones que solo leen datos y no los modifican.
    // Es una excelente práctica en C++ para evitar errores.
    bool estaVivo() const {
        return hp > 0;
    }

    string getNombre() const {
        return nombre;
    }

    virtual void atacar(Entidad &objetivo){
        cout << nombre << " ataca a " << objetivo.getNombre() << "." << endl;
        objetivo.recibirDano(danoBase);
    }
};

class Heroe : public Entidad{
    private:
        int kendoMastery;
    public:
        Heroe(string _nombre, int _hp, int _danoBase, int _kendoMastery) : Entidad(_nombre, _hp, _danoBase){
            kendoMastery = _kendoMastery;
        }
        
        void atacar(Entidad &objetivo) override{
            cout << nombre << " hiere con su espada a " << objetivo.getNombre() << "." << endl;
            if(kendoMastery > 5){
                objetivo.recibirDano(danoBase*1.2);
                kendoMastery--;
            } else{
                objetivo.recibirDano(danoBase);
            }
        }
};

class Orco : public Entidad{
    public:
        Orco(string _nombre, int _hp, int _danoBase) : Entidad(_nombre, _hp, _danoBase){};

        void atacar(Entidad &objetivo) override{
            cout << nombre << " da una fuerte garrotazo a " << objetivo.getNombre() << "." << endl;
            objetivo.recibirDano(danoBase);
        }
};

class Mago : public Entidad{
    private:
        int mana;
    public: 
        Mago(string _nombre, int _hp, int _danoBase, int _mana) : Entidad(_nombre, _hp, _danoBase){
            mana = _mana;
        }

        void atacar(Entidad &objetivo) override{
            if(mana >= 10){
                cout << nombre << " lanza un hechizo a " << objetivo.getNombre() << "." << endl;
                objetivo.recibirDano(danoBase*1.5);
            } else{
                cout << nombre << " ataca con la mano a " << objetivo.getNombre() << "." << endl;
                objetivo.recibirDano(danoBase*0.8);
            }
        }
};

int main() {
    cout << "--- PRUEBA DEL MOTOR DE ENTIDADES ---\n";

    Heroe hero("Jose", 300, 15, 10);
    vector<Entidad*> enemigos;

    enemigos.push_back(new Orco("Ragnar", 200, 12));
    enemigos.push_back(new Mago("Merlin", 180, 10, 50));

    for(size_t i = 0; i < enemigos.size(); i++){
        enemigos[i]->atacar(hero);
    }
    
    if(hero.estaVivo()){
        cout << "El heroe " << hero.getNombre() << " esta vivo." << endl;
    } else{
        cout << "El heroe ha muerto." << endl;
    }

    for(Entidad *tempPtr : enemigos){
        delete tempPtr;
    }
    enemigos.clear();

    return 0;
}