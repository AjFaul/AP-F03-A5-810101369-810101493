CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
TARGET = SheepFight
SRC = main.cpp
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
