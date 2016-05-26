CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = merge-sort.cpp merge-sort-test.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = merge-sort-test

INSERT_SRC = merge-sort-insert.cpp merge-sort-insert-test.cpp
INSERT_OBJS = $(SRC:.cpp=.o)
INSERT_TARGET = merge-sort-insert-test

EX_SRC = merge-sort-exchange.cpp merge-sort-exchange-test.cpp
EX_OBJS = $(SRC:.cpp=.o)
EX_TARGET = merge-sort-exchange-test

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

all: clean $(TARGET) $(INSERT_TARGET) $(EX_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

$(INSERT_TARGET): $(INSERT_OBJS)
	$(CXX) $(LIBS) $^ -o $@

$(EX_TARGET): $(EX_OBJS)
	$(CXX) $(LIBS) $^ -o $@

.PRONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(INSERT_OBJS) $(INSERT_TARGET) $(EX_TARGET) \
	      $(EX_OBJS)
