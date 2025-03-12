cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
project(ColorUtils)
add_library(ColorUtils ColorUtils.cpp
        Types/Lab.cpp
        Types/Lab.h
        Types/Lch.cpp
        Types/Lch.h
        Types/RGB.cpp
        Types/RGB.h
        Types/XYZ.cpp
        Types/XYZ.h
        Types/HEX.cpp
        Types/HEX.h
        Types/conversions.cpp
        color_difference.h)
target_include_directories(ColorUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
