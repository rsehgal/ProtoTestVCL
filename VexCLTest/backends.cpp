#include <vexcl/vexcl.hpp>
#include <iostream>
#define VEXCL_SHOW_KERNELS
 
int main() {
std::cout
<< "VexCL backend: "
#ifdef VEXCL_BACKEND_OPENCL
<< "OpenCL"
#else
<< "CUDA"
#endif
<< std::endl;
 
//vex::Context ctx(vex::Filter::Type(CL_DEVICE_TYPE_GPU) && vex::Filter::Env && vex::Filter::DoublePrecision);
//vex::Context ctx(#ifdef VEXCL_BACKEND_OPENCL 
  //              vex::Filter::Type(CL_DEVICE_TYPE_GPU) &&
    //            #endif  
      //          vex::Filter::Env && vex::Filter::DoublePrecision);

#ifdef VEXCL_BACKEND_OPENCL
    vex::Context ctx(vex::Filter::Type(CL_DEVICE_TYPE_GPU) && vex::Filter::Env && vex::Filter::DoublePrecision);
#else
    vex::Context ctx(vex::Filter::Env && vex::Filter::DoublePrecision);
#endif
    
    
std::cout << ctx << std::endl;

if (ctx.queue().empty()) {
	    std::cerr << "GPUs with double precision not found." << std::endl;
	    return 1;
	}

const size_t n = 16;
 
vex::vector<double> x(ctx, n);
vex::vector<double> y(ctx, n);
 
x = vex::constants::pi() * vex::element_index() / n;
y = pow(sin(x), 2.0) + pow(cos(x), 2.0);
 
std::cout << "x = " << x << std::endl;
std::cout << "y = " << y << std::endl;
}