cmake_minimum_required(VERSION 3.5)
project(CreditLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    add_compile_options(-fPIC)
endif()

set(SOURCES
    CreditLib.cpp
    CreditLib.h
)

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    CreditMonthlyPayment
)
