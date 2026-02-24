cmake_minimum_required(VERSION 3.20)
project(secure_random LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(secure_random INTERFACE)
add_library(secure_random::secure_random ALIAS secure_random)

target_include_directories(secure_random INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(secure_random INTERFACE /W4 /permissive-)
else()
  target_compile_options(secure_random INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(secure_random_basic_test tests/test_basic.cpp)
target_link_libraries(secure_random_basic_test PRIVATE secure_random::secure_random)
add_test(NAME secure_random.basic COMMAND secure_random_basic_test)
