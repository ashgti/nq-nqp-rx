LEX=flex
YACC=bison -Wall -t -v -Lc++
CC=gcc
CXX=g++
CFLAGS=-Wall -g -DNDEBUG -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -DYYERROR_VERBOSE -O3  -fno-common 
CXXFLAGS=$(CFLAGS) -Woverloaded-virtual
BUILD_DIR=build
SRC=src
LIBS=-lLLVMX86AsmParser -L/opt/local/lib -lpthread -lffi -lm -lLLVMX86AsmPrinter -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMX86Info -lLLVMJIT -lLLVMExecutionEngine -lLLVMCodeGen -lLLVMScalarOpts -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMMC -lLLVMCore -lLLVMSupport -lLLVMSystem
INCLUDES=-I./$(SRC) -I./$(SRC)/parser -I./$(BUILD_DIR) -I/opt/local/include
RM=rm
OBJECTS=$(BUILD_DIR)/main.o $(BUILD_DIR)/node_builder.o $(BUILD_DIR)/codegen.o $(BUILD_DIR)/grammar.tab.o $(BUILD_DIR)/tokens.o

all: test

# $(BUILD_DIR)/builtins.o: $(SRC)/builtin/%.cpp
#	 $(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/parser/%.c
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/parser/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/main.o: $(SRC)/main.cpp $(SRC)/parser/grammar.tab.hh
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/node_builder.o: $(SRC)/Node_builder.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/codegen.o: $(SRC)/Codegen.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(SRC)/parser/grammar.tab.cpp: $(SRC)/parser/grammar.yy
	$(YACC) -d -o $@ $^

$(SRC)/parser/grammar.tab.hh: $(SRC)/parser/grammar.tab.cpp

$(SRC)/parser/tokens.c: $(SRC)/parser/tokens.l $(SRC)/parser/grammar.tab.hh
	$(LEX) -o $@ $<

nqp-rx: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

test: nqp-rx
	./nqp-rx t/basics.nqp

clean:
	$(RM) nqp-rx $(BUILD_DIR)/*
