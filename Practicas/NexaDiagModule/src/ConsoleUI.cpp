#include "ConsoleUI.hpp"
#include <iostream>
#include <limits>
#include <string>

void printBanner(){
    std::cout << "=============================\n         NEXADIAG PRO         \n  Diagnostic Reading Module  \n=============================\n\n";
}

void printOptions(){
    std::cout << "1. Add reading.\n2. Display readings.\n3. Search reading.\n4. Calculate parameter average.\n5. Exit.\n\n";
}

//This function return the option which can be from 1 to 5, according to the main loop
int getOption(){
    int option;
    std::cout << "Select option: ";
    std::cin >> option;
    while(option <= 0 || option >= 6){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // I didnt know what did nl do, but basically, it ignores the whole wrong entry, instead of ignore(), which only ignores the first character
        std::cout << "Invalid entry. Retype: ";
        std::cin >> option;
    }
    std::cin.clear();
    return option;
}

//This function returns the parameter name, which cant be an empty string
std::string getParameter(){
    std::string parameter;
    std::cin.clear();
    std::cout << "Parameter name: ";
    std::getline(std::cin, parameter);
    while(parameter == ""){
        std::cout << "Invalid entry. Retype: ";
        std::getline(std::cin, parameter);
    }
    std::cout << "\n";
    return parameter;
}

//This function returns the unit of the name, and it is important, because its existece ensures that the units and values dont mix up
std::string getUnit(){
    std::string unit;
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Unit: ";
    std::getline(std::cin, unit);
    while(unit == ""){
        std::cout << "Invalid entry. Retype: ";
        std::getline(std::cin, unit);
    }
    return unit;
}