cmake_minimum_required(VERSION 3.20)
project(LabTask3)

find_package(VTK REQUIRED)

# Если библиотеки нет, то её нужно собрать руками
# Затем необходимо прописать пути, где лежит бинарник и хедера
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/mnt/e/C++/Cpp_HW/sem2/gmsh-4.13.1-Linux64-sdk/lib/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/mnt/e/C++/Cpp_HW/sem2/gmsh-4.13.1-Linux64-sdk/include"
)
set(GMSH_LIBRARY gmsh)

set(FILE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challengind.cpp
)

# your executable
add_executable(${PROJECT_NAME} ${FILE_SOURCES})

# link to required VTK libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE
   ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS ${PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${GMSH_LIBRARY})




