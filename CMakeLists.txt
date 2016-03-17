cmake_minimum_required (VERSION 3.0)
include (CheckIncludeFiles)
project (BulletUnity C CXX)

if (NOT MSVC)
	# Force C++14 standard on compilers, MSVC already does this by default
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
	# Force multiple processors to be used to compile visual studio builds.
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)
	
	# Enable Static Linking the C++ ABI directly into the executables and libraries
	#---BEGIN COPY FROM BULLET CMAKE---
	#We statically link to reduce dependancies
	FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO )
		IF(${flag_var} MATCHES "/MD")
			STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MD")
		IF(${flag_var} MATCHES "/MDd")
			STRING(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
		ENDIF(${flag_var} MATCHES "/MDd")
	ENDFOREACH(flag_var)
	#---END COPY FROM BULLET CMAKE---
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bullet" Bullet)

# Includes for main project
set (BULLETPLUGIN_INCLUDEDIR
	src
	thirdparty/bullet
	thirdparty/bullet/src
)

# Main project source
set (BULLETPLUGIN_SRC
	src/physicsEngine.cpp
	src/physicsEngine.h
	src/physicsEngine_api.h
)

set (BULLETPLUGIN_LIBRARIES
	# Bullet
	BulletCollision
	BulletDynamics
	BulletSoftBody
	LinearMath
)

include_directories(include ${BULLETPLUGIN_INCLUDEDIR})
add_library(BulletPlugin SHARED ${BULLETPLUGIN_SRC})
target_link_libraries(BulletPlugin ${BULLETPLUGIN_LIBRARIES})