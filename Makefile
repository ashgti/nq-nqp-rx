LEX=flex
YACC=bison -Wall -t -v -Lc++
CC=gcc
CXX=g++
CFLAGS=-Wall -g -DNDEBUG -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -DYYERROR_VERBOSE -O3  -fno-common 
CXXFLAGS=$(CFLAGS) -Woverloaded-virtual
SRC=src
LIBS=-lfl -lLLVMX86AsmParser -L/opt/local/lib  -lpthread -lffi -lm -lLLVMX86AsmPrinter -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMX86Info -lLLVMJIT -lLLVMExecutionEngine -lLLVMCodeGen -lLLVMScalarOpts -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMMC -lLLVMCore -lLLVMSupport -lLLVMSystem
INCLUDES=-I./include -I/opt/local/include -I./build
BUILD_DIR=build
RM=rm
OBJECTS=$(BUILD_DIR)/main.o $(BUILD_DIR)/tokens.o $(BUILD_DIR)/grammar.tab.o $(BUILD_DIR)/node_builder.o $(BUILD_DIR)/codegen.o

all: test

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/main.o: $(SRC)/main.cpp $(BUILD_DIR)/grammar.tab.hh
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/node_builder.o: $(SRC)/node_builder.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/codegen.o: $(SRC)/codegen.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/grammar.tab.cpp: $(SRC)/grammar.yy
	$(YACC) -d -o $@ $^

$(BUILD_DIR)/grammar.tab.hh: $(BUILD_DIR)/grammar.tab.cpp

$(BUILD_DIR)/tokens.c: $(SRC)/tokens.l $(BUILD_DIR)/grammar.tab.hh
	$(LEX) -o $@ $<

parser: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

test: parser
	./parser t/basics.nqp

clean:
	$(RM) parser $(BUILD_DIR)/*
