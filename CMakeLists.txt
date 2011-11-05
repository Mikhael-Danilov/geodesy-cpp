project (GEODESY) 
cmake_minimum_required (VERSION 2.6)

include_directories(${GEODESY_SOURCE_DIR}/src )

# turn on debugging
add_definitions(-g)

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
