cmake_minimum_required (VERSION 2.6)

# the right places
include_directories(/opt/local/include)
link_directories(/opt/local/lib)

# For NetBSD, same comment as above
include_directories(/usr/pkg/include)
link_directories(/usr/pkg/lib)

FILE(GLOB SOURCES "*.cpp")

add_executable(geoUnitTests ${SOURCES})

target_link_libraries(geoUnitTests geodesy cppunit m)

add_custom_target(run_tests
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/geoUnitTests
                  DEPENDS geoUnitTests
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# This dependency ensures source is recompiled when the run_tests target is
# called directly after source code modification.
add_dependencies(run_tests geoUnitTests)
