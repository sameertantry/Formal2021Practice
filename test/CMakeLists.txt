cmake_minimum_required(VERSION 3.17)
project(TestLR)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(TestLR "../src/Grammar.cpp" "../headers/Grammar.hpp" "../src/LR0.cpp" "../headers/LR0.hpp" "../headers/Parser.hpp" "test.cpp")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${GTEST_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        GTest::GTest
        Threads::Threads)
