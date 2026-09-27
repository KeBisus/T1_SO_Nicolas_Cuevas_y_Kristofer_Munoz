# Makefile creado para la T1 -> Planificador Dieciochero en C++ 
# Compilación estricta exigida por la rúbrica para C++

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -lpthread
TARGET = planificador
SRC = planificador.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o *.out