#include <vexcl/vexcl.hpp>
#include <cstring>

class Device{
 public : 
	std::string deviceType;
};

class GPU : public Device{
public :
	GPU(){deviceType = "CL_DEVICE_TYPE_GPU";}	
	//static std::string GetDevice(){return deviceType;}
};

class CPU : public Device{
public :
	CPU(){deviceType = "CL_DEVICE_TYPE_CPU";}	
	//static std::string GetDevice(){return deviceType;}
};

class All{};

class Backend{
public:
	std::string backend;
};

class OpenCL : public Backend{
public:
	OpenCL(){ backend = "VEXCL_BACKEND_OPENCL"; }
};

class Cuda : public Backend{
public:
	Cuda(){ backend = "VEXCL_BACKEND_CUDA"; }
};

#ifdef VEXCL_BACKEND_CUDA
template<class T> void ListDevice(){
//if(!strcmp(T().deviceType,"CL_DEVICE_TYPE_CPU"))
if( T().deviceType == "CL_DEVICE_TYPE_CPU" )
{
 std::cout<<"Your trying to run CUDA code on CPU...."<<std::endl;
 std::cout<<"Kindly change your device to GPU or compile the code with OpenCL backend"<<std::endl;
}
else
{
auto dev = vex::backend::device_list(vex::Filter::Any);
unsigned pos = 0;
for(auto d = dev.begin(); d != dev.end(); d++)
   std::cout << ++pos << ". " << *d << std::endl;
}
}
#else
template <class T> void ListDevice() {
vex::Context ctx(vex::Filter::Type(T().deviceType) &&
                   vex::Filter::DoublePrecision);
  if (!ctx)
    throw std::runtime_error("No devices available.");
  // Print out list of selected devices:
  std::cout << ctx << std::endl;
}

template <>
void ListDevice<All>(){
vex::Context ctx( vex::Filter::Any && vex::Filter::DoublePrecision );
if (!ctx) throw std::runtime_error("No devices available.");
// Print out list of selected devices:
std::cout << ctx << std::endl;

}
#endif
