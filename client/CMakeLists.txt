cmake_minimum_required(VERSION 3.8.2)

# Project
project(CBORClientExample)

# Include directory
include_directories(include)
include_directories(lib/QCBOR/inc/)

# Include sources 
file(GLOB QCBOR_FILES lib/QCBOR/src/*.c)

# For compilers to find curl you may need to set:
#   export LDFLAGS="-L/usr/local/opt/curl/lib"
#  export CPPFLAGS="-I/usr/local/opt/curl/include"

# Libcurl
link_libraries(curl)

# Executable
add_executable(client main.c src/telemetry_codec.c ${QCBOR_FILES})