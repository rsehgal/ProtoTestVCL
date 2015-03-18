cmake_minimum_required(VERSION 2.8)
project(VexCL)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(VexCL REQUIRED)
include_directories(${VEXCL_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

#find_package(OpenCL REQUIRED)
#    include_directories( ${OPENCL_INCLUDE_DIRS} )
#    set(BACKEND_LIBS ${OPENCL_LIBRARIES})
#    add_definitions(-DVEXCL_BACKEND_OPENCL)

#Selecting Backend and including corresponding library
if ("${VEXCL_BACKEND}" STREQUAL "OpenCL")
    #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
    message(STATUS "Selected Library : OPENCL")
    find_package(OpenCL REQUIRED)
    include_directories( ${OPENCL_INCLUDE_DIRS} )
    message(STATUS "OPENCL LIBRARIES : ${OPENCL_LIBRARIES}")
    set(BACKEND_LIBS ${OPENCL_LIBRARIES})
    add_definitions(-DVEXCL_BACKEND_OPENCL)
	add_definitions(-DVEXCL_BACKEND)
elseif ("${VEXCL_BACKEND}" STREQUAL "CUDA")
    message(STATUS "Selected Library : CUDA")
    find_package(CUDA REQUIRED)
    message(STATUS "CUDA INCLUDE DIR : ${CUDA_INCLUDE_DIRS}")
    message(STATUS "CUDA LIBRARIES : ${CUDA_LIBRARIES}")
    include_directories( ${CUDA_INCLUDE_DIRS} )
    #set(BACKEND_LIBS ${CUDA_LIBRARIES})
    set(BACKEND_LIBS "/usr/lib64/nvidia/libcuda.so")
    message(STATUS "CUDA LIBRARIES : ${BACKEND_LIBS}")
    add_definitions(-DVEXCL_BACKEND_CUDA)
	add_definitions(-DVEXCL_BACKEND)
endif()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
#find_package(VexCL REQUIRED)
#include_directories(${VEXCL_INCLUDE_DIRS})


set(BOOST_COMPONENTS
    date_time
    filesystem
    system
    thread
    unit_test_framework
    program_options
    )

find_package(Boost COMPONENTS ${BOOST_COMPONENTS})
include_directories( ${Boost_INCLUDE_DIRS} )
message(STATUS "BOOST found : ${Boost_LIBRARIES}")


#----------------------------------------------------------------------------
# Enable C++11 support, set compilation flags
#----------------------------------------------------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wclobbered -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter -Wno-comment -Wno-type-limits -Wno-strict-aliasing")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wno-comment -Wno-tautological-compare")

    option(USE_LIBCPP "Use libc++ with Clang" OFF)
    if (USE_LIBCPP)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif ()

#----------------------------------------------------------------------------


function(add_vexcl_example example)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} ${BACKEND_LIBS} ${Boost_LIBRARIES})

    #list(APPEND binaries "${CMAKE_CURRENT_BINARY_DIR}/${example}")
    #list(APPEND sources  "${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp")
endfunction()

#----------------------------------------------------------------------------
# General examples
#----------------------------------------------------------------------------
#add_vexcl_example(devlist)
add_vexcl_example(myDevList)
#add_vexcl_example(benchmark)

#add_vexcl_example(backends) //Working
#add_vexcl_example(add)
#add_vexcl_example(first)
