# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

# initialize project
project(interpretator)

# find sources
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(../atl)

file(GLOB_RECURSE SOURCES "*.c")
file(GLOB_RECURSE HEADERS "*.h")

# configure project
set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} atl)

# set compiler features
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")
endif()

