CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O3

SRCS = main.cpp src/quiz.cpp src/enums.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = quiz

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean