cmake_minimum_required (VERSION 2.6)

FILE(GLOB SOURCES "*.cpp")

add_library(geodesy STATIC ${SOURCES})

include_directories(.)

# install information
file(GLOB INCLUDES "*.hpp")
install(FILES ${INCLUDES} DESTINATION include/geodesy)
install(TARGETS geodesy DESTINATION lib)
