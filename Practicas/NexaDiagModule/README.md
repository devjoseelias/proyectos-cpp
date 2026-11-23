# NexaDiagModule
## What is it?
Basically, **NexaDiagModule** is a console program designed for the automotive industry, and its main purpose is to work as a easy way to register different types of vehicle data readings, each with its own name, value and unit, so the user can insert as many entries of different lectures, or the same -with different units-, and then the program offers some options, which are:
1. Add reading - Then asks for the name, the value and unit.
2. Display readings - Which is obvious, just displays on screen alll the reading that've been made to the car
3. Search reading - Asks for the name, and then displays, but it doesnt differentiate from the multiple units (if apply)
4. Calculate the average of some readings - it asks for both the name an dthe unit, so it doesnt mix the values without casting them.
5. Exit - stop the program execution

## The standard
In the CMakeLists, the declared standard is C++20, and thats the idea or what the code is searching for, the minimun version declared for it is 3.28, and the biggest is 3.31, decision made based on the cpp standard

Consider that the g++ version used in this project is: 16.1.0
And the CMake version is: 4.3.3
Also, the generator is Ninja, so the executable will be inside build/

## Compiling and execution
To compile, follow the next steps, and consider you have to be in the father directory of all the files:
    NexaDiagModule/
        | build/
        | include/
        | src/
        | CMakeLists.txt
        | README.md
    
So, this are the compilation steps:
1. cmake -S . -B build
2. cmake --build build (this is the compiling command, the following ones are to execute)
3. cd build
4. .\NexaDiagModule
And that should be it. 

## Responsabilities
So, I'll use the .hpp files to reference, despite the functions definitions are in .cpp files in the src/ directory.
- ConsoleUI.hpp | It contains all the UI/UX functions, for example the console outputs and some inputs which dont need to be asked in the main function to keep it clear
-  DiagnosticReading | This one is the most complex of the program, because it contains an enum class, to storage different states, so we can communicate while looking for the parameter name. It also has th vector for the Readings, it's important to know that each element of the vector **isn't** an isolated vehicle, it is a part of the diagnosis of **one vehicle**. Other way to see it, the vector is a vehicle, and its elemets are the readings.

## Limitations
Despite this program works, there are some points that can be improved, such as the responsabilities, the encapsulation (OOP), the persistence and the oportunity to scale up and make a "database" for many vehicles, each one with its reading (again, OOP). Also, the program might have better ways to storage the information, but it's just my theory. 