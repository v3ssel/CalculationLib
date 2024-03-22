cmake_minimum_required(VERSION 3.5)
project(DepositCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    DepositCalculator.cpp
    DepositCalculator.h

    DepositParams.h
    DepositResult.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
