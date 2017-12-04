cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_BUILD_TYPE Debug)

project("image-tache")

set(TGT "image-tache")
set(${TGT}_VERSION_MAJOR 0)
set(${TGT}_VERSION_MINOR 5)

set(CC_COVERAGE_COMPILE_FLAGS "-pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline")
set(CMAKE_C_FLAGS_DEBUG "${C_COVERAGE_COMPILE_FLAGS} -DDebug -g -pg")
set(CMAKE_CC_FLAGS_RELEASE "${CC_COVERAGE_COMPILE_FLAGS} -O3")

set(GL_LDFLAGS "-lGL -lglut -lGLU")

set(CMAKE_CC_STANDARD 11)
set(CMAKE_CC_STANDARD_REQUIRED YES)
set(CMAKE_CC_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "../debug/")

set(CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} ${CC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CC_COVERAGE_COMPILE_FLAGS} -lm ${GL_LDFLAGS}")

include_directories(include)
file(GLOB SOURCES "src/*")
add_executable(${TGT} ${SOURCES})
