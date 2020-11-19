cmake_minimum_required(VERSION 3.8.2)

# Project
project(CBORClientExample)

# Include directory
include_directories(include)
include_directories(lib/QCBOR/inc/)

# Include sources 
file(GLOB QCBOR_FILES lib/QCBOR/src/*.c)

# Libcurl
link_libraries(curl)

# Executable
add_executable(client main.c src/telemetry_codec.c ${QCBOR_FILES})