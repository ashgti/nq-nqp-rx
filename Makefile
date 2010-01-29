LEX=flex
YACC=bison
CC=gcc
CXX=g++
CFLAGS=-Wall -I$(INCLUDE_DIR) `llvm-config --libs core jit native --cxxflags --ldflags`
CXXFLAGS=
SRC=src
LIBS=-lfl
INCLUDE_DIR=include
BUILD_DIR=build
RM=rm

all: parser

$(BUILD_DIR)/parser.cpp: $(SRC)/parser/parser.y
	$(YACC) -d -o $@ $^

$(BUILD_DIR)/parser.hpp: $(BUILD_DIR)/parser.cpp

$(BUILD_DIR)/tokens.cpp: $(SRC)/parser/tokens.l $(BUILD_DIR)/parser.cpp
	$(LEX) -o $@ $^

parser: $(BUILD_DIR)/tokens.cpp $(BUILD_DIR)/parser.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) parser $(BUILD_DIR)/*
