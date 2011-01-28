cmake_minimum_required (VERSION 2.6)

FILE(GLOB SOURCES "*.cpp")

add_library(geo SHARED ${SOURCES})

include_directories(.)

# install information
file(GLOB INCLUDES "*.hpp")
install(FILES ${INCLUDES} DESTINATION include/geo)
install(TARGETS geo DESTINATION lib)
