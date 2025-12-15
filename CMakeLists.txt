cmake_minimum_required(VERSION 3.10)
project(Heap VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(HeapTest TestHeap.cpp)
target_link_libraries(HeapTest gtest gtest_main)
target_include_directories(HeapTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(HeapExample example.cpp)
target_include_directories(HeapExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
