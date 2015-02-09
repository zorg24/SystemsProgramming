#include <iostream>
#include "SlidingPuzzleState.h"

void DepthLimitedDFS(int i, SlidingPuzzleState &state);	

int main(int argc, char* argv[]) {
//	std::cout << "Hello World!" << std::endl;
	const int nums[12] = { 1, 5, 3, 7, 6, 0, 2, 11, 4, 8, 9, 10 };
	SlidingPuzzleState puzzle(nums);
//	puzzle.Print();
	DepthLimitedDFS(10, puzzle);

//	DepthLimitedDFS(depth, state) {
//		if depth == 0 return
//			moveList = state.GetMoves();
//		for each move in moveList{
//			Apply move to state
//			DepthLimitedDFS(depth - 1, state)
//			Undo move from state
//		}
//	}
	return 0;
}

void DepthLimitedDFS(int depth, SlidingPuzzleState &state)
{
	state.Print();
	std::cout << std::endl;
	if (depth == 0 || state.IsSolution())
		return;
	LList<int> moveList = state.GetMoves();
	for (int move = moveList.PeekFront(); !moveList.IsEmpty(); moveList.RemoveFront(), move = moveList.PeekFront())
	{
		state.ApplyMove(move);
		DepthLimitedDFS(depth - 1, state);
		state.UndoMove(move);
	}
}