cmake_minimum_required(VERSION 3.5)
project(CalculationAlgorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)

set(SOURCES 
    BaseCalculationAlgorithm.cpp
    BaseCalculationAlgorithm.h
    CalculationAlgorithm.cpp
    CalculationAlgorithm.h
    ExpressionPreparator.cpp
    ExpressionPreparator.h

    Handlers/ExpressionHandler.h

    ExpressionToken.h
    ExpressionTypes.h
    Utils.cpp
    Utils.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
