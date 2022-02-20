cmake_minimum_required (VERSION 3.0)
project(ImageType)

find_package(OpenCL REQUIRED)

set(CL_TARGET_OPENCL_VERSION "1.1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-deprecated-declarations")

add_executable(imagetypes imagetypes.cpp)
target_link_libraries(imagetypes m ${OpenCL_LIBRARY})


