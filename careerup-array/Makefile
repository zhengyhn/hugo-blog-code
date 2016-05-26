CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = careerup-1.5.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = 1.5

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
