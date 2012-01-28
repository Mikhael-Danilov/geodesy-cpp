# Run cppcheck
#
# Creates 2 targets:
#  cppcheck - runs cppcheck and outputs to stdout
#  cppcheck.xml - runs cppcheck and outputs an XML file
#
# Variables you may define are:
#  CPPCHECK_OUTPUT - file where the XML file should be generated

find_program(CPPCHECK cppcheck)
if(CPPCHECK)

  if(NOT DEFINED "CPPCHECK_OUTPUT")
    set(CPPCHECK_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cppcheck.xml)
  endif()
  set(CPPCHECK_FLAGS --enable=all)
  
  add_custom_target(cppcheck.xml)
  add_custom_command(TARGET cppcheck.xml POST_BUILD
    COMMAND ${CPPCHECK} ${CPPCHECK_FLAGS} --xml ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test 2> ${CPPCHECK_OUTPUT})

  add_custom_target(cppcheck)
  add_custom_command(TARGET cppcheck POST_BUILD
    COMMAND ${CPPCHECK} ${CPPCHECK_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test)
  
endif(CPPCHECK)
