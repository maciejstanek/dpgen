cmake_minimum_required(VERSION 3.3)
project(dpgen)

file(GLOB RESOURCES "*.dpd")
foreach(RESOURCE ${RESOURCES})
  get_filename_component(RESOURCE_FILE ${RESOURCE} NAME)
  configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_FILE})
  install(FILES ${RESOURCE} DESTINATION /usr/share/dpgen)
endforeach(RESOURCE)
