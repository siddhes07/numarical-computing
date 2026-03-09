CXX = g++
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