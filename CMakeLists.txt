project (geo) 
cmake_minimum_required (VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# turn on debugging
add_definitions(-g)

add_subdirectory(src)

# tests
add_subdirectory(test)

# need to do doxygen
include(FindDoxygen)
if(DOXYGEN)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/api"
                       COMMAND ${DOXYGEN} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
                       DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    add_custom_target(doxygen
                      DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/api")
else(DOXYGEN)
    message(STATUS "WARNING: Doxygen not found - API documentation will not be created")
endif(DOXYGEN)

