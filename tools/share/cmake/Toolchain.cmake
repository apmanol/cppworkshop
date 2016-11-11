find_program (GCC5_EXE /usr/bin/gcc-5)
if (GCC5_EXE)
    # name of the target system
    set (CMAKE_SYSTEM_NAME Linux)
    # C cross compiler
    set (CMAKE_C_COMPILER /usr/bin/gcc-5)
    # C++ cross compiler
    set (CMAKE_CXX_COMPILER /usr/bin/g++-5)
    # directories to prepend in find_XXX() commands
    set (CMAKE_FIND_ROOT_PATH /usr)
    # find_program(): do not use CMAKE_FIND_ROOT_PATH
    set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    # find_library(): use only CMAKE_FIND_ROOT_PATH
    set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    # find_path()/find_file(): use only CMAKE_FIND_ROOT_PATH
    set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif ()

