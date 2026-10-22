cmake_minimum_required(VERSION 3.20)
project(MLIRChapter09Exercises LANGUAGES C CXX)

find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using MLIR from ${MLIR_DIR}")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(chapter09_exercises main.cpp)
target_compile_features(chapter09_exercises PRIVATE cxx_std_17)
target_link_libraries(chapter09_exercises PRIVATE
  MLIRArithDialect
  MLIRFuncDialect
  MLIRIR
  MLIRParser
  MLIRSupport
  LLVM
)
