#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>

int main() {
    const unsigned int N = 1 << 20;

    //try {
	// Init VexCL context: grab one GPU with double precision.
	//vex::Context ctx(
		//vex::Filter::Type(CL_DEVICE_TYPE_GPU) &&
		//vex::Filter::DoublePrecision &&
		//vex::Filter::Count(1)
		//vex::Filter::Any
		//vex::Filter::Type(CL_DEVICE_TYPE_GPU)
		//vex::Filter::Platform("AMD")
		vex::Filter::Env;
		//);

vex::Context ctx( vex::Filter::Env );

	if (ctx.queue().empty()) {
	    std::cerr << "GPUs with double precision not found." << std::endl;
	    return 1;
	}

	std::cout << ctx << std::endl;
    // } //Try ends
  /*
     catch (const cl::Error &err) {
	std::cerr << "OpenCL error: " << err << std::endl;
	return 1;
    }
  */
}
