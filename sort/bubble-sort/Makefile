CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = bubble-sort.cpp bubble-sort-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = bubble-sort-test

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
