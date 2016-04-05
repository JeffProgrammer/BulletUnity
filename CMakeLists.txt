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

# http://stackoverflow.com/a/7750816
# Basically just force the output dir to where we give
macro(target_output_directory targetname directory)
	set_target_properties( ${targetname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${directory} )
	set_target_properties( ${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${directory} )
	set_target_properties( ${targetname} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${directory} )
	# Second, for multi-config builds (e.g. msvc)
	foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
		string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
		set_target_properties( ${targetname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${directory} )
		set_target_properties( ${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${directory} )
		set_target_properties( ${targetname} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${directory} )
	endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endmacro()

# Includes for main project
set (BULLETPLUGIN_INCLUDEDIR
	src
	thirdparty/bullet
	thirdparty/bullet/src
)

if (MSVC)
	set (BULLETPLUGIN_INCLUDEDIR
		${BULLETPLUGIN_INCLUDEDIR}
		thirdparty/compat
	)
endif()

# Main project source
set (BULLETPLUGIN_SRC
	src/marshal.h
	src/physicsBody.cpp
	src/physicsBody.h
	src/physicsBody_api.cpp
	src/physicsBody_api.h
	src/physicsBox.cpp
	src/physicsBox.h
	src/physicsBox_api.cpp
	src/physicsBox_api.h
	src/physicsEngine.cpp
	src/physicsEngine.h
	src/physicsEngine_api.cpp
	src/physicsEngine_api.h
	src/physicsInterior.cpp
	src/physicsInterior.h
	src/physicsInterior_api.cpp
	src/physicsInterior_api.h
	src/physicsRigidBody.cpp
	src/physicsRigidBody.h
	src/physicsRigidBody_api.cpp
	src/physicsRigidBody_api.h
	src/physicsSphere.cpp
	src/physicsSphere.h
	src/physicsSphere_api.cpp
	src/physicsSphere_api.h
	src/pluginAPI.h
	src/util.cpp
	src/util.h
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

# Stop OSX from putting "lib" in front of the name
set_target_properties(BulletPlugin PROPERTIES PREFIX "")

# Plugin suffix should be .bundle on OSX, .dll on Windows
if (APPLE)
	set_target_properties(BulletPlugin PROPERTIES SUFFIX ".bundle")
elseif (MSVC)
	set_target_properties(BulletPlugin PROPERTIES SUFFIX ".dll")
endif()

# Make it go to where we want. Default is the plugins directory but you can change
# this if you're not building as a submodule.
set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Assets/Plugins/" CACHE PATH "Path where the built plugin will go")
target_output_directory(BulletPlugin "${OUTPUT_DIRECTORY}")

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()