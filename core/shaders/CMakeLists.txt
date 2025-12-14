cmake_minimum_required(VERSION 3.23)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/sprite.fs 
  ${CMAKE_CURRENT_BINARY_DIR} 
  COPYONLY
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/sprite.vs 
  ${CMAKE_CURRENT_BINARY_DIR} 
  COPYONLY
)