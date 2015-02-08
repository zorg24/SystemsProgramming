#include "SlidingPuzzleState.h"
#include <iostream>


SlidingPuzzleState::SlidingPuzzleState(const int tiles_[12])
{
	for (int i = 0; i < 12; ++i)
	{
		for (int j = i; tiles_[i] != tiles_[j]; ++j)
		{
			std::cerr << "The input contains a duplicate entry" << std::endl;
		}
	}

	for (int i = 0; i < 12; ++i)
	{
		if (tiles_[i] >= 0 && tiles_[i] < 12)
		{
			tiles[i] = tiles_[i];
		}
		else
		{
			std::cerr << "The " << i << "th element of the input contains an element outside of the range [0,12).";
		}
	}
}


SlidingPuzzleState::~SlidingPuzzleState()
{
}



LList<int> GetMoves()
{
    LList<T> *temp = new LList<T>;

    
    return theList;
}
