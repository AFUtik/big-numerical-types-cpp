cmake_minimum_required(VERSION 3.10.0)
project(BigNTypes VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# add_library(BigNTypes STATIC ${SOURCES})

add_executable(BigNTypes src/main.cpp ${HEADERS})

#install(TARGETS BigNTypes
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#    RUNTIME DESTINATION bin
#)
#
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/ DESTINATION include
#    FILES_MATCHING PATTERN "*.hpp"
#)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
