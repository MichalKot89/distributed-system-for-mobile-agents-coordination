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

include_directories(../src)
include_directories(../Spectator_src)
FILE(GLOB AGENT_SRCS ../src/*.cpp)

#find_package(LibGSL REQUIRED)
#libfind_pkg_check_modules(orocos-ocl-timer_PKGCONF ImageMagick++)

#message("!!!!!!!!!!!!!${AGENT_SRCS}")

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)


#
# Do setup in case of ros package, If ROS_ROOT is set, it is
# recommended to use RTT/OCL through the ros packages.
#
set (ROS_ROOT $ENV{ROS_ROOT} )
if (ROS_ROOT)
  include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
  rosbuild_init()
  rosbuild_find_ros_package( rtt )
  set( RTT_HINTS HINTS ${rtt_PACKAGE_PATH}/install )
endif()

# Set the CMAKE_PREFIX_PATH in case you're not using Orocos through ROS
# for helping these find commands find RTT.
find_package(OROCOS-RTT REQUIRED ${RTT_HINTS})
find_package(PkgConfig)

pkg_check_modules(OCL_TIMER ocl-timer-gnulinux)
pkg_check_modules(OCL orocos-ocl-gnulinux)
set(LIBS ${LIBS} ${OCL_TIMER_LIBRARIES} ${OCL_LIBRARIES})
include_directories(${OCL_TIMER_INCLUDE_DIRS} ${OCL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OCL_TIMER_LIBRARY_DIRS} ${OCL_LIBRARY_DIRS})


# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
message("!!!!!!!!!!!!!!!!!!!!!!!!! ${OCL_LIBDIR}")
    ADD_EXECUTABLE( AgentsCommunication AgentCom-component.hpp AgentCom-component.cpp ../src/Coordinates.cpp ../src/Common.cpp)
    TARGET_LINK_LIBRARIES( AgentsCommunication ${OROCOS-RTT_LIBRARIES} ${LIBS})
    SET_TARGET_PROPERTIES( AgentsCommunication PROPERTIES DEFINE_SYMBOL OCL_DLL_EXPORT)


#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#

# Creates a component library libAgentCom-<target>.so
# and installs in the directory lib/orocos/AgentCom/
#
#orocos_component(AgentCom AgentCom-component.hpp AgentCom-component.cpp ${AGENT_SRCS})
#SET_TARGET_PROPERTIES( AgentCom PROPERTIES COMPILE_FLAGS "-DOCL_COMPONENT_ONLY" )
# ...you may add multiple source files
#
# You may add multiple orocos_component statements.

#
# Additional headers:
#
# Installs in the include/orocos/AgentCom/ directory
#
#orocos_install_headers( AgentCom-component.hpp ) # ...you may add multiple header files
#
# You may add multiple orocos_install_headers statements.

#
# Building a Plugin
#
# Creates a plugin library libAgentCom-plugin-<target>.so
# and installs in the directory lib/orocos/AgentCom/plugins/
#
# Be aware that a plugin may only have the loadRTTPlugin() function once defined in a .cpp file.
# This function is defined by the plugin and service CPP macros.
#
#orocos_plugin(AgentCom-plugin AgentCom-plugin.cpp) # ...only one plugin function per library !
#
# You may add multiple orocos_plugin statements.


#
# Building a Service:
#
# Creates a plugin library libAgentCom-service-<target>.so
# and installs in the directory lib/orocos/AgentCom/plugins/
#
#orocos_service(AgentCom-service AgentCom-service.cpp) # ...only one service per library !
#
# You may add multiple orocos_service statements.


#
# Building a typekit (recommended):
#
# Creates a typekit library libAgentCom-types-<target>.so
# and installs in the directory lib/orocos/AgentCom/types/
#
#orocos_typegen_headers(AgentCom-types.hpp) # ...you may add multiple header files
#
# You may only have *ONE* orocos_typegen_headers statement !


#
# Building a normal library (optional):
#
# Creates a library libsupport-<target>.so and installs it in
# lib/
#
#orocos_library(support support.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_library statements.


#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#
#orocos_generate_package()
