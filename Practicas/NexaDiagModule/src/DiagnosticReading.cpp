#include "DiagnosticReading.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<ReadingData> VehicleDiagnosis = {};

//This correspond to the option - add reading - and it's the main functionality of the program, it pushes the read to the vector and also handles a couple of console input errors
void addReading(){
    ReadingData data;

    // I decided to do this because I'll use getline() in the next few lines, made sense in mi mind
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Same than in UI, I investigated and implemented limits
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

//This function allow the program to display the whole vector, however, it doesn't filter anything
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

//This function is another display, but it also filters by the parameter name, showing all the matching registers, despite their units
Status searchReading(std::string parameterName){
    if(VehicleDiagnosis.empty()){
        std::cout << "There are no readings of this vehicle.\n\n";
        return Status::NoReadings;
    }
    Status found = Status::NotRegistered; // I use this to avoid the use of an if statement later
    for(const auto& lecture : VehicleDiagnosis){
        if(lecture.parameterName == parameterName){
            found = Status::ReadingFound;
            std::cout << parameterName << ": " << lecture.value << " " << lecture.unit << std::endl;
        }
    }
    std::cout << "\n";
    return found;
}

//This funtion is the one who acts as a filter, a search and a display, but it doesnt display all the matching reads, it shows the average of those who match in both name and unit
Status calculateAverage(std::string parameterName, std::string unit){
    if(VehicleDiagnosis.empty()){
        std::cout << "There are no readings of this vehicle.\n\n";
        return Status::NoReadings;
    }
    Status found = Status::NotRegistered;
    double sum = 0; // Initialized this two here, because in an earlier version, I just declared, so trash mixed up later with the increment
    int count = 0;
    std::string unitPrintable; //since I already have 'unit', i´ll use this to print, the other one to compare
    for(const auto& lecture : VehicleDiagnosis){ 
        if(lecture.parameterName == parameterName && unit == lecture.unit){
            std::cout << parameterName << ": " << lecture.value << " " << lecture.unit << std::endl;
            sum += lecture.value;
            count++;
            unitPrintable = lecture.unit;
            found = Status::ReadingFound;
        }
    }
    if(count != 0){
        sum = sum / count;
        std::cout << "The average of " << parameterName << " is: " << sum << " " << unitPrintable << "\n\n";
    }
    
    return found;
}
