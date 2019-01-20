cmake_minimum_required(VERSION 3.3)
project(dpgen)

find_program(BASH_PROGRAM bash)
add_test(test ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh)

file(GLOB RESOURCES "*.dpd")
foreach(RESOURCE ${RESOURCES})
  get_filename_component(RESOURCE_FILE ${RESOURCE} NAME)
  configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_FILE})
endforeach(RESOURCE)
