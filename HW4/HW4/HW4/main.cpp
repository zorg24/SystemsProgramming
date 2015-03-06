//
//  main.cpp
//  COMP2355 Winter 2015 HW4
//

#include "TestPagedDiskArray.h"
#include <iostream>
#include <cstdint>

//testing
int main(int argc, const char * argv[])
{
	std::cout << "uint8_t" << std::endl;
	TestPagedDiskArray<uint8_t>(512, 16);
	TestPagedDiskArray<uint8_t>(11, 23);
	TestPagedDiskArray<uint8_t>(4096, 2);
	TestPagedDiskArray<uint8_t>(2, 4096);

	std::cout << "uint64_t" << std::endl;
	TestPagedDiskArray<uint64_t>(512, 16);
	TestPagedDiskArray<uint64_t>(11, 23);
	TestPagedDiskArray<uint64_t>(4096, 2);
	TestPagedDiskArray<uint64_t>(2, 4096);

	std::cout << "double" << std::endl;
	TestPagedDiskArray<double>(512, 16);
	TestPagedDiskArray<double>(11, 23);
	TestPagedDiskArray<double>(4096, 2);
	TestPagedDiskArray<double>(2, 4096);
}

