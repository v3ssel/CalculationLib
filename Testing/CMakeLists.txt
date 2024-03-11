cmake_minimum_required(VERSION 3.5)
project(CalculationAlgorithmTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)

add_subdirectory(../CalculationAlgorithm CalculationAlgorithm)

set(SOURCES 
    main_test.cpp
    ExpressionPreparatorTests.cpp
    ExpressionParserTests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME}
    CalculationAlgorithm
    ${GTEST_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
