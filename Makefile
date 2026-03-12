CXX = g++
<<<<<<< HEAD
CXXFLAGS = -Iinclude -Wall

SRC = src/main.cpp src/matrix.cpp src/system_of_linear_equation.cpp \
      src/gaussian_elimination.cpp src/lu_decomposition.cpp

TARGET = solver

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) output/*.txt
=======
CXXFLAGS = -Wall -std=c++11

TARGET = queens

OBJS = main.o board.o queen.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp board.h queen.h
	$(CXX) $(CXXFLAGS) -c main.cpp

board.o: board.cpp board.h queen.h
	$(CXX) $(CXXFLAGS) -c board.cpp

queen.o: queen.cpp queen.h
	$(CXX) $(CXXFLAGS) -c queen.cpp

clean:
	rm -f $(OBJS) $(TARGET)
>>>>>>> d1139b7a3d2e5f2a18aa10bfc981d2a67c789d88
