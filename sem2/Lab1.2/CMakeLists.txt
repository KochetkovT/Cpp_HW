cmake_minimum_required(VERSION 3.20)
project(LabTask2)

set(FILE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Cloud.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Cow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Field.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ASCIIPicture.cpp
)

add_executable(${PROJECT_NAME} ${FILE_SOURCES})
