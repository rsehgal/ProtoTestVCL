#include <iostream>
#include <stdexcept>
#include <device.h>
//#include <vexcl/vexcl.hpp>
//#include <cstring>

int main() {
  /* ListDevice<CPU>() OR ListDevice<GPU>() runs the primary template.
     ListDevice<All>() runs the specialized template.
  */
  ListDevice<GPU>();
	
  //GetDevice<Cuda,GPU>().ListDevice();
}
