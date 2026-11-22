#pragma once

#include <iostream>
#include <string>
#include <vector>

struct ReadingData{
    std::string parameterName;
    double value;
    std::string unit;
};

extern std::vector<ReadingData> VehicleDiagnosis;

void addReading();
void displayReadings();
void searchReading();