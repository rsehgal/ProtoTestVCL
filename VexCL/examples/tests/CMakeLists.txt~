cmake_minimum_required(VERSION 2.8)
set(OUTDIR ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR}/bin)

set(CMAKE_MODULE_PATH /home/raman/cmake/modules)

set(BOOST_COMPONENTS
    date_time
    filesystem
    system
    unit_test_framework
    program_options
    )

find_package(Boost COMPONENTS ${BOOST_COMPONENTS})
include_directories( ${Boost_INCLUDE_DIRS} )

find_package(OpenCL REQUIRED)
include_directories( ${OPENCL_INCLUDE_DIRS} )
message(STATUS "===========================")
message(STATUS ${OPENCL_INCLUDE_DIRS})
message(STATUS "---------------------------")
message(STATUS ${OPENCL_LIBRARY_DIRS})
message(STATUS "---------------------------")
message(STATUS ${OPENCL_LIBRARIES})
message(STATUS "===========================")

find_package(VexCL REQUIRED)
include_directories(${VEXCL_INCLUDE_DIRS})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wclobbered -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter -Wno-comment -Wno-type-limits -Wno-strict-aliasing")
endif ()

#file(GLOB testsources *.cpp)
#foreach( test ${testsources} )
#        get_filename_component( TESTEXEC ${test} NAME_WE)
#        add_executable(${TESTEXEC} ${test})
#	target_link_libraries(${TESTEXEC} ${OPENCL_LIBRARIES} ${Boost_LIBRARIES})
#endforeach( test )

#add_executable(first first.cpp)
#target_link_libraries(first ${OPENCL_LIBRARIES} ${Boost_LIBRARIES})


function(add_vexcl_example example)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} ${BACKEND_LIBS} ${Boost_LIBRARIES})
    #target_link_libraries(${example} ${OPENCL_LIBRARIES} ${Boost_LIBRARIES})
endfunction()

#----------------------------------------------------------------------------
# General examples
#----------------------------------------------------------------------------
if ("${VEXCL_BACKEND}" STREQUAL "OpenCL")
    message(STATUS "++++++++++++++++++")
    message(STATUS "Going for OpenCL")
    message(STATUS "++++++++++++++++++")
    add_definitions(-DVEXCL_BACKEND_OPENCL)
    set(BACKEND_LIBS ${OPENCL_LIBRARIES})
    message(STATUS ${BACKEND_LIBS})
    add_vexcl_example(devlist)
endif()

if ("${VEXCL_BACKEND}" STREQUAL "CUDA")
    message(STATUS "++++++++++++++++++")
    message(STATUS "Going for CUDA")
    message(STATUS "++++++++++++++++++")
    add_definitions(-DVEXCL_BACKEND_CUDA)
    find_package(CUDA REQUIRED)
    include_directories(${CUDA_INCLUDE_DIRS})
    set(BACKEND_LIBS ${CUDA_LIBRARIES})
    message(STATUS ${BACKEND_LIBS})
    add_vexcl_example(devlist)
endif()

#add_vexcl_example(first)
#add_vexcl_example(devlist)
