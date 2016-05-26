CXX = g++
FLAGS = -Wall -o2 -g -std=c++11
LIBS = -lboost_unit_test_framework

SRC = binary-search-tree-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = binary-search-tree-test

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
