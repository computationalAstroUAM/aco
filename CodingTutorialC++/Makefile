# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = ACO_practice

# Source files
SRCS = overflow.cpp MainArgs.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executables
EXECS = overflow MainArgs

all: $(TARGET)

overflow: overflow.o
	$(CXX) $(CXXFLAGS) -o overflow overflow.o

MainArgs: MainArgs.o
	$(CXX) $(CXXFLAGS) -o MainArgs MainArgs.o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET) $(EXECS)