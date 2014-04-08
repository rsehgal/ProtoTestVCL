#include <vexcl/vexcl.hpp>
#include<iostream>
int main() {
    std::cout
        << "VexCL backend: "
#ifdef VEXCL_BACKEND_OPENCL
        << "OpenCL"
#else
        << "CUDA"
#endif
        << std::endl;

    vex::Context ctx(vex::Filter::Env && vex::Filter::DoublePrecision);
    std::cout << ctx << std::endl;

    const size_t n = 16;

    vex::profiler<> prof(ctx);
    prof.tic_cpu("generate data");

    vex::vector<double> x(ctx, n);
    vex::vector<double> y(ctx, n);

    x = vex::constants::pi() * vex::element_index() / n;
    y = pow(sin(x), 2.0) + pow(cos(x), 2.0);
   
    prof.toc("generate data");
 
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    std::cout << prof << std::endl;
}
