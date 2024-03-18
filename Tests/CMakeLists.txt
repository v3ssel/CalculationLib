cmake_minimum_required(VERSION 3.5)
project(CalculationAlgorithmTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)

set(SOURCES 
    main_test.cpp
    ExpressionPreparatorTests.cpp
    ExpressionParserTests.cpp
    ShuntingYardTests.cpp
    CalculationAlgorithmTests.cpp
    CalculationAlgorithmWithXWrapperTests.cpp
    CreditMonthlyPaymentTests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    CalculationAlgorithm
    CreditMonthlyPayment
    ${GTEST_LIBRARIES}
)
