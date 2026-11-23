#pragma once
#include <iostream>

void printBanner(); //Funtion to print the initial banner of the program
void printOptions(); //Auxiliar function to print the menu options
int getOption(); //Input function which returns a number between 1 and 5
std::string getParameter(); //Input function that returns the name (parameter name) of a reading
std::string getUnit(); //Input function that return the unit of a value