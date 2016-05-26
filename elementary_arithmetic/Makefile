CXX = g++
FLAGS = -Wall -o2 -g
LIBS = -lboost_unit_test_framework

SRC = arithmetic.cpp
TARGET = arithmetic

$(TARGET):$(SRC)
	$(CXX) $(FLAGS) $< -o $@ $(LIBS)

.PRONY: clean
clean:
	$(RM) $(TARGET)

