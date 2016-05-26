CXX = g++
INCS = -I../stack/
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = st-queue-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = st-queue-test

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCS) -c $< -o $@

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
