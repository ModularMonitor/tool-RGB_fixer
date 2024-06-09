cmake_minimum_required(VERSION 3.15)

project(RGBConverter VERSION 1.0 DESCRIPTION "565 to 888 and 888 to 565 made easy")

# Release?
set(CMAKE_BUILD_TYPE Release)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "_DEBUG")
else ()
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "NDEBUG")
endif ()


file(GLOB_RECURSE source_list "src/*.cpp")
add_executable(${PROJECT_NAME} ${source_list})

#target_include_directories(${PROJECT_NAME} PRIVATE 
#    #httplib
#    "deps"
#)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
 )