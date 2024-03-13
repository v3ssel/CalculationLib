cmake_minimum_required(VERSION 3.5)
project(CalculationAlgorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCES 
    BaseCalculationAlgorithm.cpp
    BaseCalculationAlgorithm.h
    CalculationAlgorithm.cpp
    CalculationAlgorithm.h
    ExpressionPreparator.cpp
    ExpressionPreparator.h
    ExpressionParser.cpp
    ExpressionParser.h
    Calculation.cpp
    Calculation.h

    Handlers/ExpressionHandler.cpp
    Handlers/ExpressionHandler.h
    Handlers/NumberHandler.cpp
    Handlers/NumberHandler.h
    Handlers/BracketsHandler.cpp
    Handlers/BracketsHandler.h
    Handlers/OperatorsHandler.cpp
    Handlers/OperatorsHandler.h
    Handlers/FunctionsHandler.cpp
    Handlers/FunctionsHandler.h
    Handlers/HandleStatus.h

    ExpressionToken.h
    ExpressionTypes.h
    Utils.cpp
    Utils.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
