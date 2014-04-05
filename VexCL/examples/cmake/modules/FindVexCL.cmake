# - Finds Vc installation ( the wrapper library to SIMD intrinsics )
# This module sets up Vc information 
# It defines:
# VEXCL_FOUND          If the ROOT is found
# VEXCL_INCLUDE_DIR    PATH to the include directory
# VEXCL_LIBRARIES      Most common libraries
# VEXCL_LIBRARY_DIR    PATH to the library directory 

# look if an environment variable NT2ROOT exists
set(VEXCLROOT $ENV{VEXCLROOT})

find_library(VEXCL_LIBRARIES libtestVexCL.so PATHS ${VEXCLROOT}/lib)
if (VEXCL_LIBRARIES) 
   set(VEXCL_FOUND TRUE)	
   #string(REPLACE "/lib/libwt.so" "" NT2ROOT  ${NT2_LIBRARIES})
   set(VEXCL_INCLUDE_DIRS ${VEXCLROOT}/include)
   set(VEXCL_LIBRARY_DIRS ${VEXCLROOT}/lib)
   message(STATUS "Found VEXCL library in ${VEXCL_LIBRARIES}")		
else()
   message(STATUS "VEXCL library not found; try to set a VEXCLROOT environment variable to the base installation path or add -DVEXCLROOT= to the cmake command")	
endif()



