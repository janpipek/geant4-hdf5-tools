cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(g4hdf5tools)

# Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(include)
add_library(g4hdf5tools SHARED ${sources} ${headers})

# HDF5
set(Hdf5_LIBARIES hdf5 hdf5_cpp hdf5_hl)

target_link_libraries(g4hdf5tools
    ${Geant4_LIBRARIES}
    ${Hdf5_LIBARIES}
)

install(TARGETS g4hdf5tools DESTINATION .)

set(CMAKE_CXX_FLAGS "-std=c++0x")
