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

enum class Status{
    NotRegistered = 1,
    NoReadings = 2,
    ReadingFound = 3
};

void addReading();
void displayReadings();
Status searchReading(std::string parameterName);
Status calculateAverage(std::string parameterName, std::string unit);