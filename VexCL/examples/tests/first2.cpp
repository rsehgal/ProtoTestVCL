#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>
//#include <vexcl/devlist.hpp>
//#include <context.hpp>

#define N 1024
int main() {
    //const unsigned int N = 1 << 20;
//auto dev = vex::backend::device_list(vex::Filter::Any);

    //try {
	// Init VexCL context: grab one GPU with double precision.
      /*
	vex::Context ctx(
		//vex::Filter::Type(CL_DEVICE_TYPE_GPU) &&
		//vex::Filter::DoublePrecision &&
		//vex::Filter::Count(1)
		//vex::Filter::Any
		vex::Filter::Type(CL_DEVICE_TYPE_GPU)
		//vex::Filter::Platform("AMD")
		);
      */


#ifdef VEXCL_BACKEND_OPENCL
    vex::Context ctx( vex::Filter::Exclusive( vex::Filter::Env ) );
#else
    vex::Context ctx( vex::Filter::Env );
#endif

	if (ctx.queue().empty()) {
	    std::cerr << "GPUs with double precision not found." << std::endl;
	    return 1;
	}

	else
	{

	    std::vector<float> a(N,1);
	    std::vector<float> b(N,2);
	    std::vector<float> c(N);

	    vex::vector<float> A(ctx,a);
	    vex::vector<float> B(ctx,b);
	    vex::vector<float> C(ctx,N);
	
	    C=A+B;

	    //std::vector<float>c(N);
	    vex::copy(C,c);
	    std::cout<<a[5]+b[5]<<"  :  "<<C[5]<<std::endl;

	}

//	std::cout << ctx << std::endl;
    // } //Try
  /*
     catch (const cl::Error &err) {
	std::cerr << "OpenCL error: " << err << std::endl;
	return 1;
    }
  */

   
}
