cmake_minimum_required(VERSION 2.8)

project(g4hdf5tools)

# Necessary variables
# if(DEFINED ENV{G4APP_PATH})
#     set(G4APP_PATH $ENV{G4APP_PATH})
# endif()
# if(DEFINED ENV{G4APP_SOURCE_PATH})
#     set(G4APP_SOURCE_PATH $ENV{G4APP_SOURCE_PATH})
# endif()

# G4APP_PATH 
# if(DEFINED G4APP_PATH)
#     message(STATUS "Using install location: $ENV{G4APP_PATH}" )
#     set(CMAKE_INSTALL_PREFIX ${G4APP_PATH})
# endif()

# Use the FindG4Application.cmake file
#  set(CMAKE_MODULE_PATH "${G4APP_SOURCE_PATH}/cmake/" ${CMAKE_MODULE_PATH} cmake)

# Find the application library & Geant4
# find_package(G4Application REQUIRED)

# Boost
# find_package(Boost 1.49 REQUIRED)
# include_directories(${Boost_INCLUDE_DIR})

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
