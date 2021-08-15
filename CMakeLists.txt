cmake_minimum_required(VERSION 3.0)

project(tkv_controle)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -static -static-libgcc -static-libstdc++")
add_executable(tkv_controle main.cpp ./core/tFile.cpp ./core/tSystem.cpp)
link_libraries("-static")
install(TARGETS tkv_controle RUNTIME DESTINATION bin)
target_link_libraries(tkv_controle PUBLIC "-static")
