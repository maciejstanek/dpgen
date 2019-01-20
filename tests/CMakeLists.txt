cmake_minimum_required(VERSION 3.3)
project(dpgen)

find_program(BASH_PROGRAM bash)
add_test(test ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh)
