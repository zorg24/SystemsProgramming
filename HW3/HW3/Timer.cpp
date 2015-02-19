//
//  Timer.cpp
//  Homework 3
//
//  Created by Nathan Sturtevant on 2/16/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#include "Timer.h"

Timer::Timer()
{
	start = std::chrono::system_clock::now();
	ended = false;
}

void Timer::StartTimer()
{
	start = std::chrono::system_clock::now();
	ended = false;
}

double Timer::EndTimer()
{
	end = std::chrono::system_clock::now();
	ended = true;
	std::chrono::duration<double> elapsed = end-start;
	return elapsed.count();
}

double Timer::GetElapsedTime()
{
	if (!ended)
		end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end-start;
	return elapsed.count();
}

