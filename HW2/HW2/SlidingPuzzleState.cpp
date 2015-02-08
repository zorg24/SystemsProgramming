#include "SlidingPuzzleState.h"


SlidingPuzzleState::SlidingPuzzleState(const int tiles_[12])
{
	for (int i = 0; i < 12; ++i)
	{
		tiles[i] = tiles_[i];
	}
}


SlidingPuzzleState::~SlidingPuzzleState()
{
}
