//
//  SlidingPuzzleState.h
//  HW 2 Solution
//
//  Created by Nathan Sturtevant on 2/13/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#ifndef __HW_2_Solution__SlidingPuzzleState__
#define __HW_2_Solution__SlidingPuzzleState__

#include <stdio.h>
#include "LList.h"
#include <cstdint>

const int kUp = 0;
const int kDown = 1;
const int kLeft = 2;
const int kRight = 3;

class SlidingPuzzleState
{
public:
	// initialize with default state
	SlidingPuzzleState();
	// initialize with parameter
	SlidingPuzzleState(const int tiles[12]);
	// initialize from rank
	SlidingPuzzleState(uint32_t rank);

	// get rank value from state
	uint32_t Rank();
	uint32_t GetMaxRank();
	// get state from rank value
	void Unrank(uint32_t);
	
	SlidingPuzzleState *Clone();
	void GetMoves(LList<int> &l);
	bool ApplyMove(int move);
	bool UndoMove(int move);
	int GetTileInSquare(int row, int col);
	void GetEmptySquare(int &row, int &col);
	bool IsSolution();
	void Print();
	bool GetParity();
private:
	bool LegalMove(int move);
	int InvertMove(int move);
	int puzzle[12];
	int blank;
};

#endif /* defined(__HW_2_Solution__SlidingPuzzleState__) */
