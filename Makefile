CXX = g++
CXXFLAGS = -Iinclude -Wall

SRC = src/main.cpp \
      src/matrix.cpp \
      src/system_of_linear_equation.cpp \
      src/gaussian_elimination.cpp \
      src/lu_decomposition.cpp \
      src/gauss_jacobi.cpp \
      src/gauss_seidel.cpp

TARGET = solver

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) output/*.txt