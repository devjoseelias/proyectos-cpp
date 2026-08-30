#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>


class BaseDeDatos{
    private:
        std::unordered_map<std::string, std::string> usuarios;
    public:
        BaseDeDatos(){
            usuarios["admin"] = "300826";
        }

        bool registrarUsuario(std::string username, std::string password){
            const auto &iterador = usuarios.find(username);

            if(iterador != usuarios.end()){
                std::cout << "Lo sentimos. El usuario '" << username << "' ya está registrado.\n";
                return false;
            } else{
                if(password == ""){
                    password = "1234";
                    std::cout << "Contraseña ingresada no válida, establecida en '1234'\n";
                }
                usuarios[username] = password;
                std::cout << "\n--- USUARIO REGISTRADO CON ÉXITO ---\n\n";
            }
            return true;
        }

        bool autenticar(std::string username, std::string tryPassword){
            const auto &it = usuarios.find(username);

            if(it == usuarios.end()){
                std::cout << "El usuario no existe.\n";
                return false;
            } else{
                if(tryPassword == it->second){
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