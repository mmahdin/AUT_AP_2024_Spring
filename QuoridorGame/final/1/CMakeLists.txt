cmake_minimum_required(VERSION 3.16)

# Project name
project(quoridor)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIE -fopenmp -O3 -I/usr/local/include")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib -fPIE")

# Directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB SRCS "${SRC_DIR}/*.cpp")

# Executable name
set(TARGET quoridor)

# Libraries to link
set(LIBS boost_system boost_json boost_thread boost_filesystem)

# Create bin and obj directories if they don't exist
file(MAKE_DIRECTORY ${OBJ_DIR})
file(MAKE_DIRECTORY ${BIN_DIR})

# Add executable
add_executable(${TARGET} ${SRCS})

# Include directories
include_directories(/usr/local/include)

# Link directories
link_directories(/usr/local/lib)

# Link libraries
target_link_libraries(${TARGET} ${LIBS})

# Output directory for the executable
set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    OUTPUT_NAME ${TARGET}
)

# Custom target for cleaning up
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJ_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR}
)