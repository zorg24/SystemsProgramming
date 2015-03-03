//
//  main.cpp
//  COMP2355 Winter 2015 HW4
//

#include "TestPagedDiskArray.h"
#include <iostream>

int main(int argc, const char * argv[])
{
	TestPagedDiskArray(512, 16);
	TestPagedDiskArray(11, 23);
	TestPagedDiskArray(4096, 2);
	TestPagedDiskArray(2, 4096);
}

