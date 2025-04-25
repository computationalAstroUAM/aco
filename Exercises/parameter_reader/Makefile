CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

PARAMETERS_OBJ = parameters.o
MAIN_OBJ = main.o
PARAMETERS_CPP = parameters.c++
MAIN_CPP = main.c++
PARAMETERS_H = parameters.h

all: parameter_reader

parameter_reader: $(PARAMETERS_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(PARAMETERS_OBJ): $(PARAMETERS_CPP) $(PARAMETERS_H)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_CPP) $(PARAMETERS_H)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f parameter_reader *.o

.PHONY: all clean