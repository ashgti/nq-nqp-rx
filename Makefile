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
OBJECTS=$(BUILD_DIR)/main.o $(BUILD_DIR)/node_builder.o $(BUILD_DIR)/codegen.o $(BUILD_DIR)/Grammar.tab.o $(BUILD_DIR)/Tokens.o

all: test

# $(BUILD_DIR)/builtins.o: $(SRC)/builtin/%.cpp
#	 $(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/Parser/%.c
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/Parser/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/main.o: $(SRC)/main.cpp $(SRC)/Parser/Grammar.tab.hh
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/Node_builder.o: $(SRC)/Node_builder.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(BUILD_DIR)/codegen.o: $(SRC)/Codegen.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $^

$(SRC)/Parser/Grammar.tab.cpp: $(SRC)/Parser/Grammar.yy
	$(YACC) -d -o $@ $^

$(SRC)/Parser/Grammar.tab.hh: $(SRC)/Parser/Grammar.tab.cpp

$(SRC)/Parser/Tokens.c: $(SRC)/Parser/Tokens.l $(SRC)/Parser/Grammar.tab.hh
	$(LEX) -o $@ $<
	
nqp-rx: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

test: nqp-rx
	./nqp-rx t/basics.nqp

clean:
	$(RM) nqp-rx $(BUILD_DIR)/*
