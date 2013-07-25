# cmake_minimum_required (VERSION 2.6)

set( solve_SRCS
	solve.cpp
	process.cpp
	processMkII.cpp
	postprocessing.cpp
	preprocessing.cpp
	ueber9000.cpp
	ObjectFunctions.h
	ObjectFunctions.cpp
	)

add_library( Solve ${solve_SRCS})




