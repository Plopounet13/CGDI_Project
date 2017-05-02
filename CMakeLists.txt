cmake_minimum_required(VERSION 3.7)
project(CGDI_Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Histogramme.cpp
        src/Histogramme.hpp
        src/Image.cpp
        src/Image.hpp
        src/main.cpp
        src/Pixel.cpp
        src/Pixel.hpp
        src/Util.cpp
        src/Util.hpp
        ideas.txt
        Makefile
        README.md src/KNearestNeighbours.cpp src/KNearestNeighbours.h src/ImageClass.cpp src/ImageClass.h)

add_executable(CGDI_Project ${SOURCE_FILES})