# - Finds Vc installation ( the wrapper library to SIMD intrinsics )
# This module sets up Vc information 
# It defines:
# OPENCL_FOUND          If the ROOT is found
# OPENCL_INCLUDE_DIR    PATH to the include directory
# OPENCL_LIBRARIES      Most common libraries
# OPENCL_LIBRARY_DIR    PATH to the library directory 

# look if an environment variable NT2ROOT exists
set(OPENCLROOT $ENV{OPENCLROOT})

find_library(OPENCL_LIBRARIES libOpenCL.so PATHS ${OPENCLROOT}/lib) # ${OPENCLROOT}/lib)
if (OPENCL_LIBRARIES) 
   set(OPENCL_FOUND TRUE)	
   #string(REPLACE "/lib/libwt.so" "" NT2ROOT  ${NT2_LIBRARIES})
   set(OPENCL_INCLUDE_DIRS ${OPENCLROOT}/include)
   set(OPENCL_LIBRARY_DIRS ${OPENCLROOT}/lib)
   message(STATUS "Found OPENCL library in ${OPENCL_LIBRARIES}")		
else()
   message(STATUS "OPENCL library not found; try to set a OPENCLROOT environment variable to the base installation path or add -DOPENCLROOT= to the cmake command")	
endif()



