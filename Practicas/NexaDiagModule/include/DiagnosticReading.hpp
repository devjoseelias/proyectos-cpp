#pragma once

#include <iostream>
#include <string>
#include <vector>

struct ReadingData{ //This struct is the base of the vector, it has the main 3 attributes the program needs
    std::string parameterName;
    double value;
    std::string unit;
};

extern std::vector<ReadingData> VehicleDiagnosis; //The public vector

enum class Status{ //The different status to control the iterators all around the files
    NotRegistered = 1,
    NoReadings = 2,
    ReadingFound = 3
};

void addReading(); //Function that pushes a struct to the vector
void displayReadings(); //Function that shows the vector on screen
Status searchReading(std::string parameterName); //Function that search and displays all the reading of a kind
Status calculateAverage(std::string parameterName, std::string unit); //FUntion that calculates and displays the average of a kind of reading, as long as its unit is the usrer's specifid one