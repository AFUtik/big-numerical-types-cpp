cmake_minimum_required(VERSION 3.10.0)
project(BigNTypes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add_library(BigNTypes STATIC ${SOURCES})

if(MSVC)
    if(CMAKE_BUILD_TYPE MATCHES "Release") 
        target_compile_options(${PROJECT_NAME} PRIVATE /W4 /MT /O2)
    else()
        message("debug")
        target_compile_options(${PROJECT_NAME} PRIVATE /Zi /Od /W4 /DEBUG)
    endif()
else()
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Og)
    endif()

    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE -Wall
                -Wextra
                # additional warnings
                -Wformat-nonliteral
                -Wcast-align
                -Wpointer-arith
                -Wundef
                -Wwrite-strings
                -Wno-unused-parameter)
    if(WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()
endif()

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
