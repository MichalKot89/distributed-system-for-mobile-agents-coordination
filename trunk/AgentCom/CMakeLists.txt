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

include_directories(./)
include_directories(../src)
include_directories(../interfejs)
include_directories(../Spectator_src)
FILE(GLOB AGENTCOM_SRCS ../src/*.cpp)

#find_package(LibGSL REQUIRED)
#libfind_pkg_check_modules(orocos-ocl-timer_PKGCONF ImageMagick++)

#message("!!!!!!!!!!!!!${AGENT_SRCS}")

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)


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
#find_package(Qt4 REQUIRED)
pkg_check_modules(OCL_TIMER ocl-timer-gnulinux)
pkg_check_modules(OCL orocos-ocl-gnulinux)

  #INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/../src/" ${CMAKE_BINARY_DIR} ${OCL_TIMER_INCLUDE_DIRS} ${OCL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
  FIND_PACKAGE( Qt4 REQUIRED )
  
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)


  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
	SET( QT_USE_QTGUI TRUE )
	SET( QT_USE_QTCORE TRUE )
  SET( QT_USE_QT3SUPPORT TRUE )   
  SET( QT_USE_QTXML TRUE )
	SET( QT_USE_QTDESIGNER TRUE )
	SET( QT_USE_QTXMLPATTERNS TRUE )
	SET( QT_USE_QTUITOOLS TRUE )

  INCLUDE( ${QT_USE_FILE} )

set(LIBS ${LIBS} ${OCL_TIMER_LIBRARIES} ${OCL_LIBRARIES})
include_directories(${OCL_TIMER_INCLUDE_DIRS} ${OCL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OCL_TIMER_LIBRARY_DIRS} ${OCL_LIBRARY_DIRS} ${QT_LIBRARIES})

  # with SET() command you can change variables or define new ones
  # here we define SAMPLE_SRCS variable that contains a list of all .cpp files
  # note that we don't need \ at the end of line
  SET( AGENTCOM_SRCS
			 #AgentCom-component.hpp
			 #${AGENTCOM_MOC_SRCS}
			 #Spectator-component.cpp
			 AgentCom-component.cpp
			 ../src/Coordinates.cpp 
			 ../src/Common.cpp 
			 ../src/Segment.cpp  
			 ../interfejs/Plansza.cpp
			 #../Spectator_src/SpectBase.cpp
       ../interfejs/mainwindow.cpp
       ../interfejs/simulationwindow.cpp
       ../interfejs/agentwindow.cpp
       ../interfejs/scenewindow.cpp
       ../interfejs/viewscene.cpp
  )

  # another list, this time it includes all header files that should be treated with moc
  SET( AGENTCOM_HDRS
			 #AgentCom-component.hpp
			 Spectator-component.hpp
       ../interfejs/mainwindow.h
       ../interfejs/simulationwindow.h
       ../interfejs/agentwindow.h
       ../interfejs/scenewindow.h
       ../interfejs/viewscene.h    
  )
#QT4_AUTOMOC( ${AGENTCOM_MOC_HDRS} )
QT4_WRAP_CPP( AGENTCOM_HDRS_MOC ${AGENTCOM_HDRS} )
  
  # some .ui files
  SET( AGENTCOM_UIS
       ../interfejs/mainwindow.ui
       ../interfejs/simulationwindow.ui
       ../interfejs/agentwindow.ui
       ../interfejs/scenewindow.ui
  )

  QT4_WRAP_UI( AGENTCOM_UIS_HDRS ${AGENTCOM_UIS} ) #OK

  # and finally an resource file
  #SET( SAMPLE_RCS
   #    ./src/rc/sample.qrc
  #)
  
  # enable warnings
  ADD_DEFINITIONS( -Wall -DRTT_COMPONENT -DQT_GUI_LIBS -DQT_CORE_LIB )#${QT4_DEFINITIONS})#-shared 
  
SET_SOURCE_FILES_PROPERTIES(${QSERIES_TO_VOLUME_QT_SRCS} PROPERTIES   
OBJECT_DEPENDS "${QSERIES_TO_VOLUME_UI_HDRS}") 
  
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
#  FIND_PACKAGE( Qt4 REQUIRED )
  
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
#  INCLUDE( ${QT_USE_FILE} )
  

  INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/../src/" ${CMAKE_BINARY_DIR} ${OCL_TIMER_INCLUDE_DIRS} ${OCL_INCLUDE_DIRS})
  # this command will generate rules that will run rcc on all files from SAMPLE_RCS
  # in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
  #QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )
  
  # this will run uic on .ui files:
 # QT4_WRAP_UI( AGENTCOM_MOC_SRCS ${AGENTCOM_UIS} ) #OK
  #QT4_WRAP_UI( AGENTCOM_MOC_UIS ${AGENTCOM_UIS} ) #OK
  
# and finally this will run moc:
  #QT4_WRAP_CPP( AGENTCOM AGENTCOM_MOC_SRCS {AGENTCOM_MOC_HDRS )#${AGENTCOM_SRCS})
#  QT4_AUTOMOC( ${AGENTCOM_MOC_HDRS} )
  #QT4_GENERATE_MOC(inputfile outputfile )
  # we need this to be able to include headers produced by uic in our code
  # (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)


#qt4_wrap_cpp (FOO_MOC_OUTFILES ${FOO_MOC_HEADERS})
#add_library (foo SHARED ${FOO_SOURCE_FILES} ${FOO_MOC_OUTFILES})

include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
message("!!!!!!!!!!!!!!!!!!!!!!!!! ${OCL_LIBDIR}")

  
  # here we instruct CMake to build "sample" executable from all of the source files
  ADD_EXECUTABLE( AGENTCOM ${AGENTCOM_SRCS} ${AGENTCOM_HDRS_MOC} ${AGENTCOM_UIS_HDRS})#${AGENTCOM_RC_SRCS}  )${AGENTCOM_UI_HDRS}

  # last thing we have to do is to tell CMake what libraries our executable needs,
  # luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
  #TARGET_LINK_LIBRARIES( AGENTCOM ${QT_LIBRARIES} )




# Defines the orocos_* cmake macros. See that file for additional
# documentation.

		
    TARGET_LINK_LIBRARIES( AGENTCOM ${OROCOS-RTT_LIBRARIES} ${QT_LIBRARIES} ${LIBS} )
    SET_TARGET_PROPERTIES( AGENTCOM PROPERTIES DEFINE_SYMBOL OCL_DLL_EXPORT )


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

