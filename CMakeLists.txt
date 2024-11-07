cmake_minimum_required(VERSION 3.5.0)
project(newton-fractals)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

set(SOURCES
  ./src/Color.cpp
  ./src/BMP.cpp
  ./src/Polynomial.cpp
  ./src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")

