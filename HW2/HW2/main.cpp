#include <iostream>
#include "SlidingPuzzleState.h"

void DepthLimitedDFS(int depth, SlidingPuzzleState &state);

int main(int argc, char* argv[]) {
	const int nums[12] = { 1, 5, 3, 7, 6, 0, 2, 11, 4, 8, 9, 10 };
	SlidingPuzzleState puzzle(nums);
	puzzle.Print();
	std::cout << std::endl;
	std::cout << "Starting DFS:" << std::endl;
	DepthLimitedDFS(13, puzzle);
	puzzle.Print();
	std::cout << std::endl;
	return 0;
}

void DepthLimitedDFS(int depth, SlidingPuzzleState &state)
{
	LList<int> moveList = state.GetMoves();
	if (state.IsSolution())
	{
		std::cout << "Found a solution:" << std::endl;
		state.Print();
		std::cout << std::endl;
		return;
	}
	if (depth == 0)
		return;
	for (int move; !moveList.IsEmpty(); moveList.RemoveFront())
	{
		move = moveList.PeekFront();
		state.ApplyMove(move);
		DepthLimitedDFS(depth - 1, state);
		state.UndoMove(move);
	}
}