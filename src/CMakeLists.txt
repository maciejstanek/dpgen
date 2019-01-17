cmake_minimum_required(VERSION 3.3)
project(dpgen)

file(GLOB SOURCES "*.c")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
add_library(dpgen STATIC ${SOURCES})
find_library(mraa 1.0.0 REQUIRED)
target_link_libraries(dpgen PUBLIC mraa)
target_include_directories(dpgen PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
set_property(TARGET dpgen PROPERTY C_STANDARD 99)

add_executable(dpgen_exe "main.c")
set_target_properties(dpgen_exe PROPERTIES OUTPUT_NAME "dpgen")
set_property(TARGET dpgen_exe PROPERTY C_STANDARD 99)
target_link_libraries(dpgen_exe PRIVATE dpgen)
