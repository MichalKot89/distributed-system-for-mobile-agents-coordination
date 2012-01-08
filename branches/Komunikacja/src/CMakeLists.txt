    # This gathers all the .cpp files into the variable 'SRCS'
    FILE( GLOB AGENT_SRCS [^.]*.cpp )
    FILE( GLOB HHS [^.]*.hh )

    # ADD_EXECUTABLE( Agent ${SRCS} )
    # ADD_EXECUTABLE(Common Common.cpp )
    # ADD_EXECUTABLE(Coordinates Coordinates.cpp )
    # ADD_EXECUTABLE(Gnuplot GnuplotInc.cpp )
    # ADD_EXECUTABLE(Segment Segment.cpp )
    #SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ../plugins)    
	
    ADD_LIBRARY(Agent SHARED ${AGENT_SRCS} ${HHS})
    SET_TARGET_PROPERTIES( Agent PROPERTIES COMPILE_FLAGS "-DCREATE_LIBRARY" )
