#include <vexcl/vexcl.hpp>
#include <iostream>
#include <vector>
#define VEXCL_SHOW_KERNELS
 
size_t n = 16;

std::vector<double> fillFromFile(const char *filename);
std::vector<double> ReadFileAndFillDataVector(std::string filename);
void Test();

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
  //              vex::Filter::Type(CL_DEVICE_TYPE_CPU) &&
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

//const size_t n = 16;
//std::vector<double> x(n,1);
//std::vector<double> y(n,2);
/*
std::vector<double> x(n);
//std::vector<double> y(n);
for(int i=0;i<n;i++)
{
    x[i]=i+1;
    
}
 */

//logic to read file and fill vector
//std::vector<double> dataVector;
std::vector<double> x ;
        int dataLength=0;
        std::cout<<"Using Iterator to read file"<<std::endl;
	std::ifstream fin("ADC_cha1-2.txt");
        //std::ifstream fin("test52MB.txt");
        //std::ifstream fin("test.txt.10");
	copy(std::istream_iterator<double>(fin), std::istream_iterator<double>(), back_inserter(x));
	fin.close();
    //end = clock();  
    //std::cout << " Time required to read data = " << (double)(end - begin) / CLOCKS_PER_SEC << " secs." << std::endl;
        dataLength = x.size();
        n=dataLength;
        std::cout<<"Filed Vector length : "<<dataLength<<std::endl;

//---------------------------


//std::vector<double> x = fillFromfile("test.txt");
//Test();

int ww=4;
std::vector<double>z(n);

std::vector<double>r(n-ww+1);
std::vector<double>rfv(n);

vex::vector<double> FV(ctx.queue(), n);  //Input full Vector
vex::vector<double> RFV(ctx.queue(), n); //REsultant full vector
//vex::vector<double> A(ctx.queue(), n-ww+1);
//vex::vector<double> B(ctx.queue(), n-ww+1);
//vex::vector<double> C(ctx.queue(), n-ww+1);
//vex::vector<double> D(ctx.queue(), n-ww+1);
//vex::vector<double> R(ctx.queue(), n-ww+1);

//vex::vector<double> X(ctx.queue(), x);
//vex::vector<double> Y(ctx.queue(), y);
//vex::vector<double> Z(ctx.queue(),n);
std::cout<<"transferring data to device....."<<std::endl;
vex::copy(x.begin(),x.end(),FV.begin());
std::cout<<"Data Transfer done."<<std::endl;
//vex::copy(.begin(),x.begin()+13,A.begin());
//vex::copy(x.begin()+1,x.begin()+13+1,B.begin());

//No of Vectors to be created is equal to the window size
//Below instructions are working and show copying a portion of vex vector to other vex vector
//A=permutation(vex::element_index(0, 12))(FV);  //Copying one vex vector to another
//B=permutation(vex::element_index(1, 13))(FV);
//C=permutation(vex::element_index(2, 14))(FV);
//D=permutation(vex::element_index(3, 15))(FV);

//R = A+B+C+D;
//vex::copy(R,r);
//Z = X + Y;
//vex::copy(Z,z);
 
//std::cout << "r[8] = " << r[8] << std::endl;
//std::cout << "r[0] = " << r[0] << std::endl;

vex::profiler<> prof;
double time_elapsed=0.0;

vex::stencil<double> S(ctx, /*coefficients:*/{0.2, 0.2, 0.2, 0.2, 0.2}, /*center:*/2);
RFV = FV * S; //Skipping the first invokation.

int numOfIter=100;
double temp=0.0;
prof.tic_cpu("gpu");

for (int i =0 ;i <numOfIter ; i++)
{
    
RFV = FV * S;


}
ctx.finish();
temp = prof.toc("gpu");
time_elapsed += temp;
std::cout<<"time elapsed in GPU operation : "<<time_elapsed/numOfIter<<std::endl;

std::cout<<"Transfering data  back from device to host...."<<std::endl;
prof.tic_cpu("copy");
vex::copy(RFV,rfv);
time_elapsed = prof.toc("copy");
std::cout<<"transferrin done."<<std::endl;
std::cout<<"time elapsed in copying the results : "<<time_elapsed<<std::endl;

//std::cout << "rfv[0] = " << rfv[0] << std::endl;
//std::cout << "rfv[1] = " << rfv[1] << std::endl;

//Stop the printing
//for(int i=0;i<n;i++)
  //  std::cout<<i<<" : "<<rfv[i]<<std::endl;


//std::cout << "y = " << y << std::endl;
}

std::vector<double> ReadFileAndFillDataVector(std::string filename){

        //clock_t c1 = clock();
        std::vector<double> dataVector;
        int dataLength=0;
        std::cout<<"Using NOrmal Read File procedure"<<std::endl;
        std::ifstream infile(filename);
        double dataValue=0.0;
        while(!infile.eof())
        {
                infile >> dataValue;
                dataVector.push_back(dataValue);
        }
        
        infile.close();
        
        dataLength = dataVector.size() - 2;
        n=dataLength;
        std::cout<<"Filed Vector length : "<<dataLength<<std::endl;
        return dataVector;
}

std::vector<double> fillFromFile(const char *filename)
{
    //clock_t begin, end;
    //begin = clock();
        std::vector<double> dataVector;
        int dataLength=0;
        std::cout<<"Using Iterator to read file"<<std::endl;
	std::ifstream fin(filename);
	copy(std::istream_iterator<double>(fin), std::istream_iterator<double>(), back_inserter(dataVector));
	fin.close();
    //end = clock();  
    //std::cout << " Time required to read data = " << (double)(end - begin) / CLOCKS_PER_SEC << " secs." << std::endl;
        dataLength = dataVector.size();
        n=dataLength;
        std::cout<<"Filed Vector length : "<<dataLength<<std::endl;
        return dataVector;
}

void Test(){
    std::cout<<"Test function called"<<std::endl;
}
