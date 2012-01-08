#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.6.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(AgentCom)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ../plugins) 
add_subdirectory( src )
add_subdirectory( Spectator_src )
#add_subdirectory( AgentCom )
