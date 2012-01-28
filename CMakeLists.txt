project (GEODESY) 
cmake_minimum_required (VERSION 2.6)

# order matters, need to set these before adding the subdirectories below

# turn on some more warnings
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Werror -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror -Wall -Wextra")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Werror -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror -Wall -Wextra")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")

# support building for coverage analysis
SET(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -O0 --coverage")
SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -O0 --coverage")
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

find_program(CPPCHECK cppcheck)
if(CPPCHECK)
  # cppcheck command
  add_custom_command(OUTPUT "cppcheck.xml"
    COMMAND ${CPPCHECK} --enable=all --xml ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test 2> cppcheck.xml)

  # make sure cppcheck is run
  add_custom_target(cppcheck DEPENDS "cppcheck.xml")
  add_dependencies(cppcheck src test)
endif(CPPCHECK)
