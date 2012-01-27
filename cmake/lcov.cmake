# - Run lcov
#
# Adds a lcov target and use it to generate a coverage report.
# This will only make sense if you have enabled automated tests.
# You need of course lcov installed at your system. In order to
# generate the reports, use:
#  make lcov
#
# Variables you may define are:
#  LCOV_OUTPUT_DIR - Path where the generated output should be placed.
#  LCOV_SCAN_DIR - Where to find the .gcda files.
#

find_program(LCOV_TOOL "lcov")
find_program(LCOV_HTML "genhtml")

if(LCOV_TOOL AND LCOV_HTML)
    if(NOT DEFINED "LCOV_OUTPUT_DIR")
        set(LCOV_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)
    endif()

    if(NOT DEFINED "LCOV_SCAN_DIR")
        set(LCOV_SCAN_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)
    endif()

    add_custom_target(lcov)
    add_dependencies(lcov check)

    add_custom_command(TARGET lcov POST_BUILD
        COMMAND ${LCOV_TOOL} --capture --directory ${LCOV_SCAN_DIR} --output-file ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov
	#COMMAND ${LCOV_TOOL} --remove ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov '*.h' --output-file ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov
	#COMMAND ${LCOV_TOOL} --remove ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov '/usr/include/*' --output-file ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov
	COMMAND ${LCOV_HTML} ${CMAKE_CURRENT_BINARY_DIR}/coverage.lcov --no-branch-coverage --output-directory ${LCOV_OUTPUT_DIR}/lcov
    )
endif()
