#include "DiagnosticReading.hpp"
#include <iostream>
#include <string>
#include <vector>

std::vector<ReadingData> VehicleDiagnosis = {};

void addReading(){
    ReadingData data;

    std::cin.clear();
    std::cin.ignore();

    std::cout << "Parameter name: ";
    std::getline(std::cin, data.parameterName);
    while(data.parameterName == ""){
        std::cout << "Invalid entry. Retype: ";
        std::getline(std::cin, data.parameterName);
    }

    std::cout << "Value: ";
    std::cin >> data.value;
    while(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid entry. Retype: ";
        std::cin >> data.value;
    }

    std::cin.clear();
    std::cin.ignore();

    std::cout << "Unit: ";
    std::getline(std::cin, data.unit);
    while(data.unit == ""){
        std::cout << "Invalid entry. Retype: ";
        std::getline(std::cin, data.unit);
    }

    std::cout << "\n";

    VehicleDiagnosis.push_back(data);
}

void displayReadings(){
    std::cout << "\n";
    if(VehicleDiagnosis.empty()){
        std::cout << "\nThere are no readings in this vehicle.\n\n";
        return;
    }
    for(size_t i = 0; i < VehicleDiagnosis.size(); i++){
        std::cout << i+1 << ". " << VehicleDiagnosis[i].parameterName << ": " << VehicleDiagnosis[i].value << " " << VehicleDiagnosis[i].unit << std::endl;
    }
    std::cout << "\n";
}

void searchReading(){
    
}