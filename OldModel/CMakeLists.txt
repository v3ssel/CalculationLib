cmake_minimum_required(VERSION 3.5)
project(CalculationAlgorithmOld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)

set(SOURCES 
    unit-testing.cpp

    Model.h
    ModelCalc.cpp
    ModelCredit.cpp
    ModelDeposit.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
)
