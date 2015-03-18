#include <iostream>
#include <stdexcept>
#include <vexcl/vexcl.hpp>
int main() {
vex::Context ctx( vex::Filter::Type(CL_DEVICE_TYPE_GPU) && vex::Filter::DoublePrecision );
if (!ctx) throw std::runtime_error("No devices available.");
// Print out list of selected devices:
std::cout << ctx << std::endl;
}

