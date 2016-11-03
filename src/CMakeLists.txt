file (GLOB_RECURSE PROJECT_SOURCES *.cpp)

foreach (SOURCE ${PROJECT_SOURCES})
  get_filename_component (TARGET ${SOURCE} NAME_WE)
  # add executable
  add_executable (${TARGET} ${SOURCE})
  target_link_libraries (${TARGET} ${CMAKE_THREAD_LIBS_INIT})
  # add test
  set (TEST_TARGET "test${TARGET}")
  add_test (NAME ${TEST_TARGET}
      COMMAND ${TARGET}
      WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  # add to install targets
  install (TARGETS ${TARGET}
      RUNTIME DESTINATION ${INSTALLDIR_BIN}
      LIBRARY DESTINATION ${INSTALLDIR_LIB})
endforeach ()

