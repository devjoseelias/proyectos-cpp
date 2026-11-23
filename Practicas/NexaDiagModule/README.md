# NexaDiagModule
## What is it?
**NexaDiagModule** is a console program designed for the automotive industry, and its main purpose is to be an easy way to register different types of vehicle data readings, each with its own name, value and unit. The user can insert many entries of different lectures, or the same -with different units-, and then the program offers some options, which are:
1. Add reading - Then asks for the name, the value and unit.
2. Display readings - Displays on screen alll the readings that've been made to the car
3. Search reading - Asks for the name, then displays, but it doesnt differentiate from the multiple units (if apply)
4. Calculate the average of some readings - It asks for both the name and the unit, so it doesn't mix the values without casting them.
5. Exit - Stops the program execution

## The standard
In the CMakeLists.txt, the declared standard is C++20, which is the functional version which aims for a potential scalablity, the minimun version declared for the CMake politics is 3.28, and the newest is 3.31, decision made based on the cpp standard.

g++ version used in this project is: 16.1.0
CMake version is: 4.3.3
The used generator is Ninja, so the executable will be inside build/

## Compiling and execution
To compile, follow the upcoming steps, and consider the command execution process must be done in the root of the project (in the following example, 'NexaDiagModule'):
    NexaDiagModule/
        | build/
        | include/
        | src/
        | CMakeLists.txt
        | README.md
    
This are the compilation steps:
1. cmake -S . -B build
2. cmake --build build (this is the compiling command, the following ones are to execute)
3. cd build
4. .\NexaDiagModule

## Responsabilities
The fuction definitios are inside the .cpp files `ConsoleUI.cpp`, `DiagnosticRead.cpp`. And therefore, the documentation of their own funtions is inside those files, in the format of comments. For an efficient explanation, I will refer to the header files, which declare the functions. 
- The `CounsoleUI.hpp` is a library made to make the console outputs and inputs more efficient, and save some memory by avoiding variables (might be 1 btye, but in the future could save more). It uses C++ libraries such as \<iostream\>, to control the input, output behavior, \<string\>, to compare strings with the operator ==, and \<limits\>, to use the numeric_limits and streamsize, allowing me to handle properly the wrong inputs.
- The `DiagnosticRead.cpp` is a library designed to do all the reading related work, it uses the parameters to create new reads, and it pushes them to a vector (see the **Tecnichal detail** section), where everything is storaged. Other functions (more detailed in the .cpp files) are display everything, search a specific parameter, or search and display just the average values from the same parameter and the same unit to ensure consistent data flow.

## Limitations and Scalability
There are a couple of things that can be improved about this program, listed below:
- The encapsulation can be improved with OOP
- The usage of C++20 standars could be better, for example using `ranges` combined with `find_if` for better searches
- The scalability is present, for example, combined with .txt files, the program could save the readings.
- There's an option to make a `class Car` and have multiple readings of multiple cars.

## Tecnichal detail
The current program is using an `extern std::<vector>`, which should be a private vector to be controled and control which functuions can access it, not all the functions of all the program.