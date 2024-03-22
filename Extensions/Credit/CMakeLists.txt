cmake_minimum_required(VERSION 3.5)
project(CreditMonthlyPayment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    add_compile_options(-fPIC)
endif()

set(SOURCES 
    CreditMonthlyPayment.h
    CreditMonthlyPaymentResult.h

    CreditMonthlyPaymentAnnuity.cpp
    CreditMonthlyPaymentAnnuity.h

    CreditMonthlyPaymentDifferentiated.cpp
    CreditMonthlyPaymentDifferentiated.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
