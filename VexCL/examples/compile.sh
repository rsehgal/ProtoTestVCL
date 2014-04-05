rm -rf build
mkdir build
cd build
cmake -DVEXCL_BACKEND=$1 ..
make clean
make
cd ..
