cmake_minimum_required(VERSION 3.0)

project(controle_cpp)

add_executable(tkv_controle main.cpp ./core/tFile.cpp ./core/tSystem.cpp)

install(TARGETS tkv_controle RUNTIME DESTINATION bin)
