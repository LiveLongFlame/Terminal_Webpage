# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses

# Default target
all:
	@echo "Usage: make <filename (without .cpp)>"
	@echo "Example: make code"

# Pattern rule: make <filename>
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
	@echo "---------- RUNNING $@ ----------"
	./$@

# Optional clean rule
clean:
	rm -f *.o *.out *.exe *.gch code

