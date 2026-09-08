#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> contador(0);

void incrementar(){
    for(int i = 0; i < 100000; i++){
        contador++;
    }
}

int main(){
    std::thread hilo1(incrementar);
    std::thread hilo2(incrementar);

    hilo1.join();
    hilo2.join();

    std::cout << contador << std::endl;

    return 0;
}