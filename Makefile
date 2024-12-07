CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = main
SRC = main.cpp
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
