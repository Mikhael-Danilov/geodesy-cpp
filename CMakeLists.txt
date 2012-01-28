project (GEODESY) 
cmake_minimum_required (VERSION 2.6)

# order matters, need to set these before adding the subdirectories below

# support building for coverage analysis
SET(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -Werror -O0 -Wall --coverage")
SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -Werror -O0 -Wall --coverage")
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")

# add lcov target
include(${CMAKE_SOURCE_DIR}/cmake/lcov.cmake)


# this needs to be after the coverage setup above
include_directories(${GEODESY_SOURCE_DIR}/src )

add_subdirectory(src)

# tests
add_subdirectory(test)

# need to do doxygen
include(FindDoxygen)
if(DOXYGEN)
  add_custom_target(doxygen ${DOXYGEN} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
else(DOXYGEN)
  message(STATUS "WARNING: Doxygen not found - API documentation will not be created")
endif(DOXYGEN)

find_program(SLOCCOUNT sloccount)
if(SLOCCOUNT)
  # sloccount command
  add_custom_command(OUTPUT "sloccount.sc"
    COMMAND ${SLOCCOUNT} --wide --details ${CMAKE_CURRENT_SOURCE_DIR}/src > sloccount.sc)

  # make sure sloccount is run
  add_custom_target(sloccount DEPENDS "sloccount.sc")
  add_dependencies(sloccount src)
else(SLOCCOUNT)
  message(STATUS "WARNING: sloccount not found - will not generate SLOC count report")
endif(SLOCCOUNT)
