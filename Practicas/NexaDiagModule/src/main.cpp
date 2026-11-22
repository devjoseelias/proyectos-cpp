#include <iostream>
#include <string>
#include "DiagnosticReading.hpp"
#include "ConsoleUI.hpp"

int main(){
    int option;
    printBanner();
    do{
        printOptions();
        option = getOption();
        switch(option){
            case 1:
                addReading();
                break;
            case 2:
                displayReadings();
                break;
            case 3:
                if(searchReading(getParameter()) == Status::NotRegistered){ std::cout << "The parameter is not registered.\n\n"; }
                break;
            case 4:

                break;
            case 5:
                break;
        }
    } while(option != 5);

    return 0;
}