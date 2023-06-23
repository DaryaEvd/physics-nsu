# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project("potential hole" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        f23347fca25219d1c42cbb91608b5556814bf572
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
 
include_directories(
    ${PYTHON_INCLUDE_DIRS}
    ${PYTHON_NUMPY_INCLUDE_DIR}
    ${matplotlib_SOURCE_DIR}
)

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 

# add executable
add_executable(solutions 
  src/evdokimova_solutions.cpp)

# link python and numpy
target_link_libraries(
    solutions

    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)

add_executable(levels 
  src/evdokimova_levels.cpp)

# link python and numpy
target_link_libraries(
  levels

  PRIVATE
      ${PYTHON_LIBRARIES}
      Python3::NumPy
)


add_executable(waves 
  src/evdokimova_waves.cpp)

# link python and numpy
target_link_libraries(
  waves

  PRIVATE
      ${PYTHON_LIBRARIES}
      Python3::NumPy
)
