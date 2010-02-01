#include "node.h"
#include "codegen.h"
#include "parser.hpp"


/* Executes the AST by running the main function */
GenericValue CodeGenContext::runCode() {
    std::cout << "Running code...\n";
    ExistingModuleProvider *mp = new ExistingModuleProvider(module);
    ExecutionEngine *ee = ExecutionEngine::create(mp, false);
    vector<genericvalue> noargs;
    GenericValue v = ee->runFunction(mainFunction, noargs);
    std::cout << "Code was run.\n";
    return v;
}


CodeGenContext::CodeGenContext() {
  Context = getGlobalContext();
  module = new Module("main", Context); 
}
