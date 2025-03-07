# Makefile

USE_OPENMP = yes

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11
ifeq ($(USE_OPENMP),yes)
    CXXFLAGS += -fopenmp -DUSE_OPENMP
endif

# Source files
SRCS = main.cpp orbit.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = orbit

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(EXEC)