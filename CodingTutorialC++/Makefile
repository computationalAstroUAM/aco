# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -fopenmp

# Target executable
TARGET = ACO_practice

# Source files
SRCS = overflow.cpp MainArgs.cpp openmp-example.cpp pi.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executables
EXECS = overflow MainArgs openmp-example pi

OMP_NUM_THREADS=4
export OMP_NUM_THREADS

all: $(TARGET)

overflow: overflow.o
	$(CXX) $(CXXFLAGS) -o overflow overflow.o

MainArgs: MainArgs.o
	$(CXX) $(CXXFLAGS) -o MainArgs MainArgs.o

openmp-example: openmp-example.o
	$(CXX) $(CXXFLAGS) -o openmp-example openmp-example.o

pi: pi.o
	$(CXX) $(CXXFLAGS) -o pi pi.o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET) $(EXECS)
