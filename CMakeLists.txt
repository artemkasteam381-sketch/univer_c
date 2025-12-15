cmake_minimum_required(VERSION 3.10)
project(SparseVector VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(SparseVector SparseVector.cpp)
target_include_directories(SparseVector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Тесты
add_executable(SparseVectorTest TestSparseVector.cpp)
target_link_libraries(SparseVectorTest SparseVector gtest gtest_main)
target_include_directories(SparseVectorTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Пример программы
add_executable(ExampleProgram example.cpp)
target_link_libraries(ExampleProgram SparseVector)

# Установка для CI
install(TARGETS SparseVectorTest DESTINATION bin)
