PROJECT(nq-nqp)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(LLVM_MIN_VERSION_TEXT  "2.6")
set(LLVM_MIN_VERSION       "2006000")

Find_Package(LLVM REQUIRED)

ENABLE_TESTING()

find_package(BISON)
find_package(FLEX)

# set(CMAKE_CXX_COMPILER "clang++")

BISON_TARGET(NQPParser src/parser/grammar.yy src/parser/grammar.cpp COMPILE_FLAGS "-Wall -t -v -Lc++")
FLEX_TARGET(NQPScanner src/parser/tokens.l  src/parser/tokens.cpp)
ADD_FLEX_BISON_DEPENDENCY(NQPScanner NQPParser)

link_directories(${LLVM_LIB_DIR})
include_directories(src/Parser src ${LLVM_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${LLVM_COMPILE_FLAGS} -g -I/opt/local/include")
# SET(CMAKE_SHARED_LINKER_FLAGS ${LLVM_LDFLAGS})

add_executable(nq-nqp src/main.cpp src/node.cpp src/codegen.cpp src/node_builder.cpp src/runtime_support.cpp src/ast_pass.cpp src/vm.cpp ${BISON_NQPParser_OUTPUTS} ${FLEX_NQPScanner_OUTPUTS})

add_executable(runtime_test src/test_main.cpp src/runtime_support.cpp src/vm.cpp)

target_link_libraries(nq-nqp ${LLVM_LIBS_JIT} ${LLVM_LDFLAGS} "-L/opt/local/lib -lgc")
target_link_libraries(runtime_test ${LLVM_LIBS_JIT} ${LLVM_LDFLAGS} "-L/opt/local/lib -lgc")

add_test(junk nq-nqp "t/simple.nqp")

