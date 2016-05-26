CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = quick-sort.cpp quick-sort-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = quick-sort-test

ITER_SRC = quick-sort-iter.cpp quick-sort-iter-test.cpp
ITER_OBJS = $(SRC:.cpp=.o)
ITER_TARGET = quick-sort-iter-test

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET) $(ITER_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

$(ITER_TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(ITER_TARGET)
