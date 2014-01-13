cmake_minimum_required(VERSION 2.8.7)
project(PercolationCpp)

set(PercolationCpp_VERSION_MAJOR 0)
set(PercolationCpp_VERSION_MINOR 1)

set(EXECUTABLE_OUTPUT_PATH ../bin/)

set(percolation_SRCS PercolationVisualizer/PercolationVisualizer.cpp lib/Percolation.cpp lib/QuickUnion.cpp)

#Executable 
add_executable(PercolationVisualizer  ${percolation_SRCS})

#include Allegro
include_directories(./include)
link_directories(./lib)
#connect all the libraries
set(allegro5_LIBS ${CMAKE_SOURCE_DIR}/lib/allegro5/liballegro-5.0.10-monolith-mt.a)

target_link_libraries(PercolationVisualizer ${allegro5_LIBS})
