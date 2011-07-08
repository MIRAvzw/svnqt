#
# Configuration
#

# CMake management
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

# Project configuration
set (PROJECT svnqt)
project(${PROJECT})
string(TOUPPER ${PROJECT_NAME} PROJECT_TO_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_TO_LOWER)

# Qt4 inclusion
find_package(Qt4 REQUIRED)
set(QT_DONT_USE_QTGUI 1)
set(QT_USE_QTSQL 1)
include(${QT_USE_FILE})

# Subversion inclusion
INCLUDE(FindSubversionLibs)
INCLUDE_DIRECTORIES (
	${APR_INCLUDE_DIR}
	${APU_INCLUDE_DIR}
	${SUBVERSION_INCLUDE_DIR}
)

# Project version
set(SVNQT_VERSION_MAJOR 1)
set(SVNQT_VERSION_MINOR 6)
set(SVNQT_VERSION_RELEASE 0)
set(SVNQT_VERSION "${SVNQT_VERSION_MAJOR}.${SVNQT_VERSION_MINOR}.${SVNQT_VERSION_RELEASE}")
set(VERSION ${SVNQT_VERSION})
set(SOVERSION ${SVNQT_VERSION})

# Source files and directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
set(SVNQT_HEADERS
	src/apr.h
	src/entry.h
	src/repositorydata.h
	src/version_check.h
	src/info_entry.h
	src/lock_entry.h
	src/repositorylistener.h
	src/url.h
	src/client_update_parameter.h
	src/context.h
	src/pool.h
	src/shared_pointer.h
	src/contextdata.h
	src/revision.h
	src/wc.h
	src/annotate_line.h
	src/path.h
	src/dirent.h
	src/repoparameter.h
	src/conflictdescription.h
	src/stringarray.h
	src/client_parameter_macros.h
	src/log_entry.h
	src/exception.h
	src/client_impl.h
	src/svnqttypes.h
	src/commititem.h
	src/context_listener.h
	src/datetime.h
	src/diff_data.h
	src/status.h
	src/targets.h
	src/svnfilestream.h
	src/client_annotate_parameter.h
	src/svnqt_global.h
	src/repository.h
	src/check.h
	src/client.h
	src/cache/ReposLog.h
	src/cache/DatabaseException.h
	src/cache/conversion_check.h
	src/cache/LogCache.h
	src/cache/ReposConfig.h
	src/client_parameter.h
	src/svnstream.h
	src/helper.h
	src/diffoptions.h
	src/smart_pointer.h
	src/client_commit_parameter.h
	src/conflictresult.h
)  
set(SVNQT_SOURCES
	src/conflictdescription.cpp
	src/url.cpp
	src/client_modify.cpp
	src/commititem.cpp
	src/wc.cpp
	src/client_lock.cpp
	src/version_check.cpp
	src/pool.cpp
	src/log_entry.cpp
	src/revision.cpp
	src/client_update_parameter.cpp
	src/repositorylistener.cpp
	src/client_ls.cpp
	src/apr.cpp
	src/path.cpp
	src/repoparameter.cpp
	src/exception.cpp
	src/repository.cpp
	src/svnfilestream.cpp
	src/targets.cpp
	src/diffoptions.cpp
	src/client_property.cpp
	src/datetime.cpp
	src/repositorydata.cpp
	src/client_diff.cpp
	src/client_annotate_parameter.cpp
	src/stringarray.cpp
	src/client_cat.cpp
	src/client_status.cpp
	src/dirent.cpp
	src/svnstream.cpp
	src/client_merge.cpp
	src/contextdata.cpp
	src/client_parameter.cpp
	src/client_annotate.cpp
	src/entry.cpp
	src/client.cpp
	src/info_entry.cpp
	src/cache/ReposConfig.cpp
	src/cache/LogCache.cpp
	src/cache/ReposLog.cpp
	src/cache/DatabaseException.cpp
	src/lock_entry.cpp
	src/client_impl.cpp
	src/diff_data.cpp
	src/status.cpp
	src/client_commit_parameter.cpp
	src/conflictresult.cpp
	src/context.cpp
)


#
# Compilation
#

 
# Static or shared library
if (SVNQT_BUILD_STATIC)
set(SVNQT_BUILD_CONFIGURATION STATIC)
else (SVNQT_BUILD_STATIC)
set(SVNQT_BUILD_CONFIGURATION SHARED)
endif (SVNQT_BUILD_STATIC)

# Create library
add_library(${PROJECT_NAME} ${SVNQT_BUILD_CONFIGURATION} 
    ${SVNQT_SOURCES}
    ${SVNQT_HEADERS})


#
# Linking
#

# Qt
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

# Subversion
set_target_properties(${PROJECT_NAME} PROPERTIES 
    SOVERSION ${SVNQT_VERSION}
    VERSION ${SVNQT_VERSION}
    DEFINE_SYMBOL ${PROJECT_TO_UPPER}_EXPORTS)


#
# Installation
#

# Configure the installation paths
SET(TARGET_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
SET(TARGET_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")
SET(TARGET_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")

# Install the library
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_TARGETS}
	RUNTIME DESTINATION ${TARGET_BIN_DIR}
	LIBRARY DESTINATION ${TARGET_LIB_DIR}
	ARCHIVE DESTINATION ${TARGET_LIB_DIR})

# Install development headers
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/" DESTINATION "${TARGET_INCLUDE_DIR}" COMPONENT Devel FILES_MATCHING PATTERN "*.h")

