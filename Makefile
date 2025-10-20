CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -O3

TARGET := quiz

SRC := main.cpp quiz.cpp enums.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run