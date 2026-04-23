CXX      = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall

SRCS = src/main.cpp              \
       src/matrix.cpp            \
       src/system_of_linear_equation.cpp \
       src/gaussian_elimination.cpp      \
       src/lu_decomposition.cpp          \
       src/gauss_jacobi.cpp              \
       src/gauss_seidel.cpp              \
       src/gershgorin.cpp                \
       src/interpolation.cpp             \
       src/least_squares.cpp

TARGET = solver

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) output/*.txt