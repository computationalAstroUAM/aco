# Compiler
CXX = g++

# Program defines
CXXFLAGS = -DHIGH_TIME_PRECISION

# Compiler flags
CXXFLAGS += -pg -ftest-coverage -lgcov -Wall -Wextra -O2 -fopenmp



# Linker flags
LDFLAGS = -fopenmp

# Executable name
EXEC = mandelbrot

# Source files
SRCS = main.cpp write_output.cpp mandelbrot_series.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
