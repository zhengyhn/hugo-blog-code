CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = heap-sort.cpp heap-sort-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = heap-sort-test

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
