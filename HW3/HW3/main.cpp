//
//  main.cpp
//  HW 2 Solution
//
//  Created by Nathan Sturtevant on 2/13/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//
// By: Kris Douglass & Nathan Saslavsky


#include <iostream>
#include <thread>
#include "BFS.h"
#include "ParallelBFS.h"

int main(int argc, const char * argv[])
{
	//SequentialBFS::DoBFS();
	ParallelBFS::DoBFS(std::thread::hardware_concurrency());
}

