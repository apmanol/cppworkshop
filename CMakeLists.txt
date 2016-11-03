###
### project properties
###
cmake_minimum_required (VERSION 2.6.2)
project (cppworkshop)
set (APPLICATION_NAME "C++11/14 Workshop")
set (APPLICATION_CODENAME "${PROJECT_NAME}")
set (APPLICATION_COPYRIGHT_YEARS "2016")
set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 1)
set (APPLICATION_VERSION_PATCH 0)
set (APPLICATION_VERSION_TYPE RELEASE)
set (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}")
set (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_STRING}.${APPLICATION_VERSION_MINOR}")
set (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_STRING}.${APPLICATION_VERSION_PATCH}")
set (APPLICATION_VERSION "${APPLICATION_VERSION_STRING}")
set (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_STRING}-${APPLICATION_VERSION_TYPE}")
set (APPLICATION_VENDOR_ID "com.intracom-telecom")
set (APPLICATION_VENDOR_NAME "Intracom Telecom")
set (APPLICATION_VENDOR_URL "www.intracom-telecom.com")
set (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${CMAKE_PROJECT_NAME}")

###
### create verbose makefile
###
set (CMAKE_VERBOSE_MAKEFILE 0)

###
### project executable/library/install paths
###
set (MAINFOLDER ${PROJECT_SOURCE_DIR})
set (BINDIR $ENV{BINDIR})
get_filename_component (BINDIR ${BINDIR} ABSOLUTE)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINDIR}")
set (LIBDIR $ENV{LIBDIR})
get_filename_component (LIBDIR ${LIBDIR} ABSOLUTE)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBDIR}")
set (INSTALLDIR $ENV{INSTALLDIR})
get_filename_component (INSTALLDIR ${INSTALLDIR} ABSOLUTE)
set (CMAKE_INSTALL_PREFIX "${INSTALLDIR}")
set (INSTALLDIR_BIN $ENV{INSTALLDIR_BIN})
set (INSTALLDIR_LIB $ENV{INSTALLDIR_LIB})

###
### project cmake search directories
###
set (CMAKE_PREFIX_PATH "${MAINFOLDER}")
set (CMAKE_MODULE_PATH "${MAINFOLDER}/tools/share/cmake")

###
### project include directories
###
include_directories ("${MAINFOLDER}/include")

###
### compiler requirements/options
###
# assert C++14 support (CMAKE_CXX_STANDARD* not working on travis)
#set (CMAKE_CXX_STANDARD 14)
#set (CMAKE_CXX_STANDARD_REQUIRED on)
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG ("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG ("-std=gnu++14" COMPILER_SUPPORTS_GNUXX14)
if (COMPILER_SUPPORTS_CXX14)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif (COMPILER_SUPPORTS_GNUXX14)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
else ()
    message (FATAL_ERROR "${CMAKE_CXX_COMPILER} lacks C++14 support.")
endif ()
# common flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Werror -g")
# address sanitizer for debug builds
find_package (ASan)
if (HAVE_ADDRESS_SANITIZER)
    set (CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_ASAN}")
    set (CMAKE_EXE_LINKER_FLAGS_DEBUG
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${CMAKE_EXE_LINKER_FLAGS_ASAN}")
endif ()
# add -fstack-protector-strong
CHECK_CXX_COMPILER_FLAG ("-fstack-protector-strong" COMPILER_SUPPORTS_FSP)
if (COMPILER_SUPPORTS_FSP)
    set (CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -fstack-protector-strong")
endif ()
# add -D_FORTIFY_SOURCE=2
CHECK_CXX_COMPILER_FLAG ("-D_FORTIFY_SOURCE=2" COMPILER_SUPPORTS_FORTIFY_SRC)
if (COMPILER_SUPPORTS_FORTIFY_SRC)
    set (CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -D_FORTIFY_SOURCE=2")
endif ()
# generate compile_commands.json
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

###
### visibility of library symbols
###
#set (CMAKE_CXX_VISIBILITY_PRESET hidden)
#set (CMAKE_VISIBILITY_INLINES_HIDDEN ON)

###
### find required packages
###
find_package (Threads REQUIRED)

###
### add build targets
###
enable_testing ()
add_subdirectory (src)

###
### uninstall targets
###
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/tools/share/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target (uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

