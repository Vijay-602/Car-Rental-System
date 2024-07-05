
# README for Car Rental System

## Overview
The Car Rental System is a C++ project designed to manage car rentals for customers and employees. It includes a variety of classes that handle different aspects of the rental process, such as managing cars, customers, employees, and system configurations. 

## How to Build and Run

### Prerequisites
- C++ Compiler supporting C++20
- GNU Make

### Building the Project
1. Open a terminal in the project directory.
2. Run `make` to compile the project. This will use the `Makefile` provided with the project to compile all the source files and link them into an executable.

### Running the Program
- After building, run the executable generated. For example, if your executable is named `CarRentalSystem`, you can run it by typing `./CarRentalSystem` in your terminal.

### Removing executable files
- Run `make clean`


### Using the CLI
- The program operates through a command-line interface (CLI).
- After starting the program, follow the on-screen prompts to interact with the system.
- You can rent or return cars, manage customer or employee records, and handle car data through various menu options.

## Classes in the Project

### Car
- **Purpose**: Represents a car in the system.
- **Responsibilities**: Keeps track of car details like ID, model, condition, and rental status.

### Customer
- **Purpose**: Represents a customer who can rent cars.
- **Responsibilities**: Manages customer-related information and records of rented cars.

### Employee
- **Purpose**: Represents an employee, with similar capabilities to a customer but with additional privileges like discounts.
- **Responsibilities**: Handles employee-specific data and rented cars.

### Manager
- **Purpose**: Acts as the system administrator with capabilities to add, update, or delete customers, employees, and cars.
- **Responsibilities**: Oversees the entire rental process and maintains the system data.

### ConfigReader
- **Purpose**: Handles reading configuration settings from a file.
- **Responsibilities**: Provides a utility to read and interpret system configurations like fee rates, discounts, etc., from an external file.

## Configuration Management
- The `ConfigReader` class is used to manage system settings loaded from a configuration file.
- This allows for easy adjustments to key parameters like late fees or discount rates without altering the codebase.
- Configuration files should be structured in a key-value format for easy reading and parsing by `ConfigReader`.

## Final Notes
- This project demonstrates object-oriented programming principles in C++.
- For detailed usage instructions or to report issues, refer to the user guide or contact the development team.
