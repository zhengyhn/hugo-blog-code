CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = bilist-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = bilist-test

%.o: %.cpp
	$(CXX) $(LIBS) $(FLAGS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
