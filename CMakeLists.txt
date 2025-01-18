cmake_minimum_required(VERSION 3.10)

project(MSiM)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

#Cabeceras /include
include_directories(${CMAKE_SOURCE_DIR}/include)

#Código /src
file(GLOB_RECURSE SOURCES src/*.cpp)

#Cabeceras Box2D
include_directories(${CMAKE_SOURCE_DIR}/third_party/Box2D_v2.1.2/Box2D)

# Directorios de encabezados de SFML
include_directories(${CMAKE_SOURCE_DIR}/third_party/SFML/include)

# Directorios de bibliotecas de SFML
link_directories(${CMAKE_SOURCE_DIR}/third_party/SFML/lib)

# Verificación de la ruta de inclusión para SFML
message(STATUS "Ruta de SFML: ${CMAKE_SOURCE_DIR}/third_party/SFML")

# Verificación de la ruta de inclusión para Box2D
message(STATUS "Ruta de Box2D: ${CMAKE_SOURCE_DIR}/third_party/Box2D_v2.1.2/Box2D/Box2D")

#Librería
add_library(MSiM STATIC ${SOURCES})

# Vincula la biblioteca externa Box2D
add_library(Box2D STATIC IMPORTED)
set_target_properties(Box2D PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/Box2D_v2.1.2/Box2D/Build/Box2D/libBox2D.a
)

# Vincula SFML a tu proyecto
# Dependiendo de los módulos que utilices de SFML, necesitarás algunos o todos los siguientes:
target_link_libraries(MSiM PRIVATE Box2D sfml-graphics sfml-window sfml-system)

# Instala la biblioteca y los encabezados
install(TARGETS MSiM
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

# Configuración para el ejecutable de prueba
set(TEST_EXECUTABLE_NAME test_MSiM)

set(TEST_MAIN ${CMAKE_SOURCE_DIR}/testing/main.cpp)

# Crea el ejecutable de prueba
add_executable(${TEST_EXECUTABLE_NAME} ${TEST_MAIN})

# Vincula el ejecutable con las librerías necesarias (MSiM, Box2D, SFML)
target_link_libraries(${TEST_EXECUTABLE_NAME} MSiM Box2D sfml-graphics sfml-window sfml-system)

set_target_properties(${TEST_EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
