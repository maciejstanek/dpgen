cmake_minimum_required(VERSION 3.3)
project(dpgen)

file(GLOB SOURCES "*.c")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
add_library(dpgen STATIC ${SOURCES})
# SET_TARGET_PROPERTIES(dpgen PROPERTIES PREFIX "")

# find_package(Boost 1.65 COMPONENTS program_options REQUIRED)
find_library(mraa 1.0.0 REQUIRED)
# message("mraa_FOUND = '${mraa_FOUND}'")
# message("mraa_LIBRARIES = '${mraa_LIBRARIES}'")
# message("mraa_INCLUDE_DIR = '${mraa_INCLUDE_DIR}'")
# target_include_directories(mpask PUBLIC ${Boost_INCLUDE_DIR})
# target_link_libraries(mpask LINK_PUBLIC ${Boost_LIBRARIES})

target_include_directories(dpgen PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
# target_compile_features(mpask PUBLIC c_std_99)
set_property(TARGET dpgen PROPERTY C_STANDARD 99)
# target_compile_options(mpask PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)

target_link_libraries(dpgen PUBLIC mraa)
# target_link_libraries(mpask PUBLIC stdc++fs) # experimental/filesystem
# target_link_libraries(mpask LINK_PUBLIC ${Boost_LIBRARIES})

### EXECUTABLE ###

add_executable(dpgen_exe "main.c")
set_target_properties(dpgen_exe PROPERTIES OUTPUT_NAME "dpgen")
# target_compile_features(dpgen_exe PUBLIC c_std_99)
# target_include_directories(dpgen_exe PUBLIC ${Boost_INCLUDE_DIR})
# target_link_libraries(dpgen_exe LINK_PUBLIC ${Boost_LIBRARIES})

set_property(TARGET dpgen_exe PROPERTY C_STANDARD 99)
target_link_libraries(dpgen_exe PRIVATE dpgen)
