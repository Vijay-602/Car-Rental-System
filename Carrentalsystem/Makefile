# Makefile for Car Rental System

CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = 

# Object files
OBJ = Car.o Customer.o Employee.o Manager.o ConfigReader.o User.o main.o  # Added User.o

# Executable name
EXEC = CarRentalSystem

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compiling
Car.o: Car.cpp Car.h
	$(CXX) $(CXXFLAGS) -c Car.cpp

Customer.o: Customer.cpp Customer.h User.h  # Added User.h dependency
	$(CXX) $(CXXFLAGS) -c Customer.cpp

Employee.o: Employee.cpp Employee.h User.h  # Added User.h dependency
	$(CXX) $(CXXFLAGS) -c Employee.cpp

Manager.o: Manager.cpp Manager.h User.h  # Added User.h dependency
	$(CXX) $(CXXFLAGS) -c Manager.cpp

ConfigReader.o: ConfigReader.cpp ConfigReader.h
	$(CXX) $(CXXFLAGS) -c ConfigReader.cpp

User.o: User.cpp User.h  # Added User.cpp compilation rule
	$(CXX) $(CXXFLAGS) -c User.cpp

main.o: main.cpp Car.h Customer.h Employee.h Manager.h ConfigReader.h User.h  # Added User.h dependency
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean target
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
