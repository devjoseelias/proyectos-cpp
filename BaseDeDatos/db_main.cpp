#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <memory>

 struct Perfil{
    std::string email, password;
    int calificacion;

    Perfil(std::string &&_email, std::string &&_password, int _calificacion) : email(std::move(_email)), password(std::move(_password)), calificacion(_calificacion){};

};

void verificarDatos(std::string &email, std::string &password, int &calificacion){
    while(email == "" ){
        std::cout << "Ingrese un email válido:\n>> ";
        std::cin >> email;
    }

    while(password == ""){
        std::cout << "Ingrese una contraseña válida:\n>> ";
        std::cin >> password;
    }

    while(calificacion < 1 || calificacion > 100){
        std::cout << "Ingrese una calificación válida:\n>> ";
        std::cin >> calificacion;
    }
}

class BaseDeDatos{
    private:
        std::unordered_map<std::string, std::unique_ptr<Perfil>> usuarios;
    public:
        BaseDeDatos(){
            usuarios["admin"] = std::make_unique<Perfil>("bmjoseelias@gmail.com", "Dalis26264#", 98);
        }

        bool registrarUsuario(std::string &&username, std::string &&password, std::string &&email, int calificacion){
            const auto &iterador = usuarios.find(username);

            if(iterador != usuarios.end()){
                std::cout << "Lo sentimos. El usuario '" << username << "' ya está registrado.\n";
                return false;
            } else{
                verificarDatos(email, password, calificacion);

                usuarios[std::move(username)] = std::make_unique<Perfil>(std::move(email), std::move(password), calificacion);

                std::cout << "\n--- USUARIO REGISTRADO CON ÉXITO ---\n\n";
            }
            return true;
        }

        bool autenticar(std::string &username, std::string &tryPassword){
            const auto &it = usuarios.find(username);

            if(it == usuarios.end()){
                std::cout << "El usuario no existe.\n";
                return false;
            } else{
                if(tryPassword == it->second->password){
                    std::cout << "Autenticación exitosa.\n";
                    return true;
                } else{
                    std::cout << "Contraseña erronea. Fallo en la autenticación.\n";
                    return false;
                }
            }
        }

        bool eliminar(std::string username){
            const auto &it = usuarios.find(username);

            if(it != usuarios.end()){
                usuarios.erase(username);
                std::cout << "Usuario eliminado exitosamente.\n";
                return true;
            } else{
                std::cout << "Usuario no encontrado. No se pudo eliminar.\n";
                return false;
            }
        }


    };

int main(){
    return 0;
}