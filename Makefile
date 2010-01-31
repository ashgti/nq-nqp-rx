LEX=flex
YACC=bison
CC=gcc
CXX=g++
CFLAGS=-Wall -DNDEBUG -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -O3  -fno-common 
CXXFLAGS=$(CFLAGS) -Woverloaded-virtual
SRC=src
LIBS=-lfl -lLLVMX86AsmParser -L/opt/local/lib  -lpthread -lffi -lm -lLLVMX86AsmPrinter -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMX86Info -lLLVMJIT -lLLVMExecutionEngine -lLLVMCodeGen -lLLVMScalarOpts -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMMC -lLLVMCore -lLLVMSupport -lLLVMSystem
INCLUDES=-I./include -I/opt/local/include -I./build
BUILD_DIR=build
RM=rm
OBJECTS=$(BUILD_DIR)/main.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/tokens.o

all: test

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/main.o: $(SRC)/main.cpp $(BUILD_DIR)/parser.hpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $(SRC)/main.cpp

$(BUILD_DIR)/parser.cpp: $(SRC)/parser/parser.y
	$(YACC) -d -o $@ $^

$(BUILD_DIR)/parser.hpp: $(BUILD_DIR)/parser.cpp

$(BUILD_DIR)/tokens.cpp: $(SRC)/parser/tokens.l $(BUILD_DIR)/parser.hpp
	$(LEX) -o $@ $^

parser: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

test: parser
	echo "my foo = 5;" | ./parser

clean:
	$(RM) parser $(BUILD_DIR)/*
