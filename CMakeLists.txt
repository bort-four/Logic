# CMakeLists.txt progect Logic

cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME interpretator)
project(${PROJECT_NAME})

#~ set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -g -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

set(ATL_SRC_LIST Sources/atl.c
	Sources/Logic.c				Sources/Model.c			Sources/Parser.c
	Sources/Interpretation.c 	Sources/Expressions.c	Sources/grammar.tab.c)

set(SRC_LIST Sources/interpretator.c ${ATL_SRC_LIST})

set(ATLPP_SRC_LIST Sources/atlpp.cpp
	Sources/Logic.c				Sources/Model.c			Sources/Parser.c
	Sources/Interpretation.c 	Sources/Expressions.c	Sources/grammar.tab.c)	###

set(SRC_LIST_CPP test.cpp ${ATLPP_SRC_LIST})	##

#~ set(HDR_LIST
	#~ Headers/atl.h		Headers/Logic.h				Headers/Model.h
	#~ Headers/Parser.h	Headers/Interpretation.h	Headers/Expressions.h)

include_directories("Headers")

#~ add_library(atl STATIC ${ATL_SRC_LIST})
#~ add_executable(${PROJECT_NAME} ${SRC_LIST})

add_library(atlpp STATIC ${ATLPP_SRC_LIST})	###
add_executable(test_cpp ${SRC_LIST_CPP})

IF (UNIX)
  #~ target_link_libraries(${PROJECT_NAME} m)
ENDIF (UNIX)
