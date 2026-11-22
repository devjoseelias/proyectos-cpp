#include <iostream>
#include <vector>
#include "datos.h"
using namespace std;

float AbrirCaja();
float CobrarCliente();
string ObtenerCodigoProducto();
int ProductoEncontrado(string codigoProducto);
void ImprimirEncabezadoTicket();
bool Pagar(int metodoDePago, float saldoPendiente, float& dineroFinalCaja);
void CerrarCaja(float& gananciaNeta, float dineroFinalCaja);

float dineroPagadoConEfectivo, dineroPagadoConTarjeta, dineroPagadoConVales;

int main(){
    string respuestaUsuario;
    float dineroInicialCaja, dineroFinalCaja, gananciaNeta;
    
    cout << "Bienvenido al sistema de caja de cobro. Para responder preguntas de si o no, use 's/n'.\n==== INICIANDO SISTEMA ====\n\n";
    cout << "Abrir caja?:\n>> ";
    cin >> respuestaUsuario;
    
    if(respuestaUsuario == "s"){
        dineroInicialCaja = AbrirCaja();
        do{
            float saldoPendiente = CobrarCliente();
            int metodoDePago;

            cout << "El cliente va a pagar con?:\n1. Efectivo\n2. Credito\n3. Vales\n(1-3)>> ";

            do{
                cin >> metodoDePago;
            } while(metodoDePago <= 0 || metodoDePago >= 4);

            Pagar(metodoDePago, saldoPendiente, dineroFinalCaja);
            cout << "Siguiente cliente?\n>> ";
            cin >> respuestaUsuario;
        } while(respuestaUsuario == "s");
        CerrarCaja(gananciaNeta, dineroFinalCaja);
    } else{
        return 0;
    }
    return 0;
}

float AbrirCaja(){
    float dinero;
    cout << "Ingresa el dinero en efectivo disponible para dar cambio:\n>> ";
    cin >> dinero;
    return dinero;
}

string ObtenerCodigoProducto(){
    string codigo;
    cout << "Ingresa el codigo:\n>> ";
    getline(cin, codigo);
    return codigo;
}

int ProductoEncontrado(string codigoProducto){
    for(int i = 0; i < TAMAÑO; i++){
        if(codigoProducto == CODIGO_PRODUCTOS[i]){
            return i;
        }
    }
    cout << "Producto no enocntrado.\n";
    return -1;
}

void ImprimirEncabezadoTicket(){
    cout << "==============\nPunto de venta\n     CETI     \n==============\n\n";
}

float CobrarCliente(){
    string codigoProducto = "1";
    float montoTotal = 0; 
    ImprimirEncabezadoTicket();
    do{
        codigoProducto = ObtenerCodigoProducto();
        if(codigoProducto == "0") break;
        
        int encontrado = ProductoEncontrado(codigoProducto);
        if(encontrado != -1){
            cout << NOMBRE_PRODUCTOS[encontrado] << "\t" << CANTIDAD_PRODUCTOS[encontrado] << "\t" << PRECIO_PRODUCTOS[encontrado] << endl;
            montoTotal += PRECIO_PRODUCTOS[encontrado];
        }
    } while(codigoProducto != "0");
    return montoTotal;
}

bool Pagar(int metodoDepago, float saldoPendiente, float& dineroFinalCaja){
    float dineroRecibido, valorDelVale;
    switch(metodoDepago){
        case 1:
            cout << "Dinero recibido?\n>> ";
            do{
                cin >> dineroRecibido;
            } while(dineroRecibido <= 0 || dineroRecibido < saldoPendiente);
            if(dineroRecibido > saldoPendiente){
                cout << "El cambio es de: $" << dineroRecibido - saldoPendiente << endl;
                dineroPagadoConEfectivo += saldoPendiente;
            }
            if(dineroRecibido == saldoPendiente){
                dineroPagadoConEfectivo += dineroRecibido;
            }
            dineroFinalCaja += saldoPendiente;
            break;
            
        case 2:
            cout << "Pago con tarjeta aprobado.\n";
            dineroFinalCaja += saldoPendiente;
            dineroPagadoConTarjeta += saldoPendiente;
            break;
            
        case 3:
            cout << "Valor del vale?\n>> ";
            do{
                cin >> valorDelVale;
            } while(valorDelVale <= 0);

            if(valorDelVale >= saldoPendiente){
                if(valorDelVale > saldoPendiente){
                    cout << "El cambio es de: $" << valorDelVale - saldoPendiente << endl;
                }
                dineroPagadoConVales += saldoPendiente;
                dineroFinalCaja += saldoPendiente;
            }

            if(valorDelVale < saldoPendiente){
                float faltante = saldoPendiente - valorDelVale;
                cout << "El vale es insuficiente, pagar con efectivo la cantidad de: $" << faltante << endl; 
                dineroPagadoConVales += valorDelVale;
                
                cout << "Dinero recibido?\n>> ";
                do{
                    cin >> dineroRecibido;
                } while(dineroRecibido <= 0 || dineroRecibido < faltante);
                
                if(dineroRecibido > faltante){
                    cout << "El cambio es de: $" << dineroRecibido - faltante << endl;
                    dineroPagadoConEfectivo += faltante;
                }
                if(dineroRecibido == faltante){
                    dineroPagadoConEfectivo += dineroRecibido;
                }
                dineroFinalCaja += saldoPendiente;
            }
            break;
    }
    return true;
}

void CerrarCaja(float& gananciaNeta, float dineroFinalCaja){
    cout << "Cerrando caja...\n\n";
    gananciaNeta = dineroFinalCaja;
    cout << "Ganancia del dia: $" << gananciaNeta << endl;
}