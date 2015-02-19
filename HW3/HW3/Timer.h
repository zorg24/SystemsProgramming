//
//  Timer.h
//  Homework 3
//
//  Created by Nathan Sturtevant on 2/16/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#ifndef __Homework_3__Timer__
#define __Homework_3__Timer__

#include <stdio.h>
#include <chrono>
#include <ctime>

class Timer
{
public:
	Timer();
	void StartTimer();
	double EndTimer();
	double GetElapsedTime();
private:
	bool ended;
	std::chrono::time_point<std::chrono::system_clock> start, end;
};

#endif /* defined(__Homework_3__Timer__) */
