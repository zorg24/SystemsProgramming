#pragma once
#include "LList.h"
class SlidingPuzzleState
{
public:
	SlidingPuzzleState(const int tiles[12]);
	~SlidingPuzzleState();
	LList<int> GetMoves();
	bool ApplyMove(int move);
	bool UndoMove(int move);
	int GetTileInSquare(int row, int col);
	void GetEmptySquare(int &row, int &col);
	void Print();
	SlidingPuzzleState *Clone();
	bool IsSolution();
	static const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
private:
	int tiles[12];
    bool IsValid(int row, int col);
};

