# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

# initialize project
project(atl)

# find sources
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE SOURCES "*.c")
file(GLOB_RECURSE HEADERS "*.h")

# configure project
set(TARGET_NAME ${PROJECT_NAME})
add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${TARGET_NAME} PROPERTIES VERSION "1.0")

target_link_libraries(${PROJECT_NAME} m)

# set compiler features
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

