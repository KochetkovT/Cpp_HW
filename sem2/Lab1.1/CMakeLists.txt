cmake_minimum_required(VERSION 3.20)
project(MatrixLabLib)

# Опция для включения/выключения тестов
option(BUILD_TESTS "Build test executable" ON)

set(LIB_SOURCES
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set(LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/subvector.hpp
)

# не получится сделать STATIC, потому что есть только хедер файлы
add_library(${PROJECT_NAME} INTERFACE ${LIB_HEADERS})
# add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE # PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(BUILD_TESTS)
    set(TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_base.cpp
    )

    foreach(TEST_FILE ${TEST_SOURCES})
        get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
        
        # Имя исполняемого файла PROJECT_NAME + TEST_FILE_NAME
        add_executable(${PROJECT_NAME}_${TEST_FILE_NAME} ${TEST_FILE})

        target_link_libraries(${PROJECT_NAME}_${TEST_FILE_NAME} ${PROJECT_NAME})

        add_custom_target(test_${TEST_FILE_NAME}
            COMMAND ${PROJECT_NAME}_${TEST_FILE_NAME}
            DEPENDS ${PROJECT_NAME}_${TEST_FILE_NAME}
        )
        list(APPEND ALL_TESTS test_${TEST_FILE_NAME})
    endforeach()

    add_custom_target(test_all DEPENDS ${ALL_TESTS})
endif()
