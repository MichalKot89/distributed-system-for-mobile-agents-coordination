    # This gathers all the .cpp files into the variable 'SRCS'
    FILE( GLOB SPECT_SRCS [^.]*.cpp )
    FILE( GLOB SPECT_HHS [^.]*.hh )

    # ADD_EXECUTABLE( Agent ${SRCS} )
    # ADD_EXECUTABLE(Common Common.cpp )
    # ADD_EXECUTABLE(Coordinates Coordinates.cpp )
    # ADD_EXECUTABLE(Gnuplot GnuplotInc.cpp )
    # ADD_EXECUTABLE(Segment Segment.cpp )
    include_directories(../src)
    #   
	
    ADD_LIBRARY(Spect SHARED ${SPECT_SRCS} ${SPECT_HHS})
    SET_TARGET_PROPERTIES( Spect PROPERTIES COMPILE_FLAGS "-DCREATE_LIBRARY" )
