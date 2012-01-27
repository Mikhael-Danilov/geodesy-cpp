project (GEODESY) 
cmake_minimum_required (VERSION 2.6)

include_directories(${GEODESY_SOURCE_DIR}/src )

# FIXME remove coverage commands from this once I get it working right with
# build types
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Werror -O0 -Wall --coverage")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror -O0 -Wall --coverage")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")


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

# support for coverage checking
# product options
OPTION(BUILD_WITH_COVERAGE "Build with coverage analysis support" OFF)
IF(BUILD_WITH_COVERAGE)
IF (CMAKE_COMPILER_IS_GNUCC)
  #SET(CMAKE_BUILD_TYPE coverage)
  SET(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
  message(STATUS "Coverage is on ${BUILD_WITH_COVERAGE}")
  ENDIF(CMAKE_COMPILER_IS_GNUCC)
ENDIF(BUILD_WITH_COVERAGE)


# add lcov target
include(${CMAKE_SOURCE_DIR}/cmake/lcov.cmake)
