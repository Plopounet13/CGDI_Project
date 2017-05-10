cmake_minimum_required(VERSION 2.6)
project(CGDI_Project)

#set(CMAKE_CXX_STANDARD 11)

SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
    message(STATUS "Boost and boost_program_options found.")
    include_directories( ${Boost_INCLUDE_DIRS} )
endif( Boost_FOUND )

FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

set(SOURCE_FILES
        src/Image.cpp
        src/Image.hpp
        src/main.cpp
        src/Pixel.cpp
        src/Pixel.hpp
        src/Util.cpp
        src/Util.hpp
        src/DSS.cpp
        src/DSS.hpp
        src/KNearestNeighbours.cpp
        src/KNearestNeighbours.h
        src/ImageClass.cpp
        src/ImageClass.h)

add_executable(CGDI_Project ${SOURCE_FILES})
target_link_libraries (CGDI_Project ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
