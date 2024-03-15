cmake_minimum_required(VERSION 3.5)
project(CalculationLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    CalculationLib.cpp
    CalculationLib.h
)

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    CalculationAlgorithm
)
