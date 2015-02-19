//
//  SlidingPuzzleState.cpp
//  HW 2 Solution
//
//  Created by Nathan Sturtevant on 2/13/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#include "SlidingPuzzleState.h"
#include <cassert>
#include <iomanip>

static uint32_t Factorial(int val)
{
	static uint32_t table[13] =
	{ 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600 };
	assert(val <= 12);
	return table[val];
}


SlidingPuzzleState::SlidingPuzzleState()
{
	for (int x = 0; x < 12; x++)
		puzzle[x] = x;
	blank = 0;
}

SlidingPuzzleState::SlidingPuzzleState(const int tiles[12])
{
	for (int x = 0; x < 12; x++)
	{
		if (tiles[x] == 0)
			blank = x;
		puzzle[x] = tiles[x];
	}
}

// initialize from rank
SlidingPuzzleState::SlidingPuzzleState(uint32_t rank)
{
	Unrank(rank);
}


// get rank value from state
uint32_t SlidingPuzzleState::Rank()
{
	int locs[10]; // We only rank 10 of 12 items; last two are fixed by the parity
	int dual[12];
	
	// build the representation containing the item locations
	for (unsigned int x = 0; x < 12; x++)
	{
		dual[puzzle[x]] = x;
	}
	// build an array with the locations of the first 10 items
	for (int x = 0; x < 10; x++)
	{
		locs[x] = dual[x];
	}
	
	uint32_t hashVal = 0;
	int numEntriesLeft = 12;
	
	// compute the lexographical ranking of the locations
	// of the first 10 tiles
	for (unsigned int x = 0; x < 10; x++)
	{
		hashVal += locs[x]*Factorial(numEntriesLeft-1)/2;
		numEntriesLeft--;
		
		// decrement locations of remaining items
		// to keep the numbering compact
		for (unsigned y = x; y < 10; y++)
		{
			if (locs[y] > locs[x])
				locs[y]--;
		}
	}
	return hashVal;
}

uint32_t SlidingPuzzleState::GetMaxRank()
{
	return Factorial(12)/2;
}

// Get state from rank value
// To test this code we generated every state in the state space
// via unranking and tested its parity as well as that of its
// neighbors. We also verified that each state unranks and ranks
// back to the same state.
void SlidingPuzzleState::Unrank(uint32_t rank)
{
	int count = 12;
	uint64_t hashVal = rank;
	int dual[10];
	
	// unrank the locations of the first 10 tiles
	int numEntriesLeft = count-10+1;
	for (int x = 10-1; x >= 0; x--)
	{
		dual[x] = hashVal%numEntriesLeft;
		hashVal /= numEntriesLeft;
		numEntriesLeft++;
		for (int y = x+1; y < 10; y++)
		{
			if (dual[y] >= dual[x])
				dual[y]++;
		}
	}
	// clear puzzle locations
	for (int x = 0; x < 12; x++)
	{
		puzzle[x] = -1;
	}
	// revert locations of tiles into positions in the puzzle
	for (int x = 0; x < 10; x++)
	{
		puzzle[dual[x]] = x;
	}
	// reset the cache of the blanks location
	blank = dual[0];
	
	// now find the two -1's and assign them
	// to ensure the right parity
	int x = 0;
	int loc1 = -1, loc2 = -1;
	for (; x < 12; x++)
	{
		if (puzzle[x] == -1)
		{
			loc1 = x;
			x++;
			break;
		}
	}
	for (; x < 12; x++)
	{
		if (puzzle[x] == -1)
		{
			loc2 = x;
			break;
		}
	}
	assert(loc1 != -1 && loc2 != -1);
	// Choose an arbitrary ordering and then
	// check the parity. If it's wrong, we just
	// swap them and are guaranteed to get the right
	// parity.
	puzzle[loc1] = 10;
	puzzle[loc2] = 11;
	if (GetParity() == false)
	{
		puzzle[loc1] = 11;
		puzzle[loc2] = 10;
	}
	//After exhaustively testing the code we remove this call to save time.
	//assert(GetParity() == true);
}

SlidingPuzzleState *SlidingPuzzleState::Clone()
{
	return new SlidingPuzzleState(puzzle);
}

void SlidingPuzzleState::GetMoves(LList<int> &l)
{
	while (!l.IsEmpty())
		l.RemoveFront();

	if (blank > 3)
		l.AddFront(kUp);
	if (blank < 8)
		l.AddFront(kDown);
	if ((blank%4) != 3)
		l.AddFront(kRight);
	if ((blank%4) != 0)
		l.AddFront(kLeft);
}

bool SlidingPuzzleState::ApplyMove(int move)
{
	if (!LegalMove(move))
		return false;
	switch (move)
	{
		case kUp:
			puzzle[blank] = puzzle[blank-4];
			blank -= 4;
			puzzle[blank] = 0;
			break;
		case kDown:
			puzzle[blank] = puzzle[blank+4];
			blank += 4;
			puzzle[blank] = 0;
			break;
		case kRight:
			puzzle[blank] = puzzle[blank+1];
			blank += 1;
			puzzle[blank] = 0;
			break;
		case kLeft:
			puzzle[blank] = puzzle[blank-1];
			blank -= 1;
			puzzle[blank] = 0;
			break;
		default:
			std::cout << "Illegal move in Apply Move";
			return false;
			break;
	}
	return true;
}
bool SlidingPuzzleState::LegalMove(int move)
{
	switch (move)
	{
		case kUp: return (blank > 3);
		case kDown: return (blank < 8);
		case kRight: return ((blank%4) != 3);
		case kLeft: return ((blank%4) != 0);
		default: return false;
	}
}

int SlidingPuzzleState::InvertMove(int move)
{
	switch (move)
	{
		case kUp: return kDown;
		case kDown: return kUp;
		case kRight: return kLeft;
		case kLeft: return kRight;
		default: assert(!"Illegal move.");
	}
}


bool SlidingPuzzleState::UndoMove(int move)
{
	return ApplyMove(InvertMove(move));
}

int SlidingPuzzleState::GetTileInSquare(int row, int col)
{
	return puzzle[row*4+col];
}

void SlidingPuzzleState::GetEmptySquare(int &row, int &col)
{
	row = blank/4;
	col = blank%4;
}

bool SlidingPuzzleState::IsSolution()
{
	for (int x = 0; x < 12; x++)
		if (puzzle[x] != x)
			return false;
	return true;
}

void SlidingPuzzleState::Print()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			std::cout << std::setw(3) << GetTileInSquare(y, x);
		}
		std::cout << "\n";
	}
}

bool SlidingPuzzleState::GetParity()
{
	int cnt = 0;
	for (int x = 0; x < 12; x++)
	{
		if (puzzle[x] == 0)
			continue;
		for (int y = x+1; y < 12; y++)
		{
			if (puzzle[y] == 0)
				continue;
			if (puzzle[y] < puzzle[x]) // how many to the right are smaller
				cnt++;
		}
	}
	return (0==(cnt + (12-blank-1)/4)%2);
}

