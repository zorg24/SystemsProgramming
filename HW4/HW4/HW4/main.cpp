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
	TestPagedDiskArray<uint8_t>(512, 16);
	TestPagedDiskArray<uint8_t>(11, 23);
	TestPagedDiskArray<uint8_t>(4096, 2);
	TestPagedDiskArray<uint8_t>(2, 4096);

	TestPagedDiskArray<uint64_t>(512, 16);
	TestPagedDiskArray<uint64_t>(11, 23);
	TestPagedDiskArray<uint64_t>(4096, 2);
	TestPagedDiskArray<uint64_t>(2, 4096);

	TestPagedDiskArray<double>(512, 16);
	TestPagedDiskArray<double>(11, 23);
	TestPagedDiskArray<double>(4096, 2);
	TestPagedDiskArray<double>(2, 4096);
}

