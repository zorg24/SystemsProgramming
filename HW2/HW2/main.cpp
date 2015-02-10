//Kris Douglass and Nathan Saslavsky
//We weren't sure what you wanted so its currently set up to only set up to run the extra credit, but it should take uncommenting a few lines to run the other
#include <iostream>
#include "SlidingPuzzleState.h"

void DepthLimitedDFS(int depth, SlidingPuzzleState &state);
bool DepthLimitedDFS(int depth, SlidingPuzzleState &state, bool isSolved, LList<int> &moves);
void IterativeDeepeningDFS(SlidingPuzzleState &state);

int main(int argc, char* argv[]) {
	const int nums[12] = { 1, 5, 3, 7, 6, 0, 2, 11, 4, 8, 9, 10 };
	SlidingPuzzleState puzzle(nums);
//	puzzle.Print();
//	std::cout << std::endl;
//	std::cout << "Starting DFS:" << std::endl;
//	DepthLimitedDFS(13, puzzle);
//	puzzle.Print();
//	std::cout << std::endl;
	IterativeDeepeningDFS(puzzle);
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

bool DepthLimitedDFS(int depth, SlidingPuzzleState &state, bool isSolved, LList<int> &moves)
{
	LList<int> moveList = state.GetMoves();
	if (state.IsSolution())
	{
		return true;
	}
	if (depth == 0)
		return false;
	for (int move; !moveList.IsEmpty(); moveList.RemoveFront())
	{
		move = moveList.PeekFront();
		state.ApplyMove(move);
		moves.AddFront(move);
		bool a = DepthLimitedDFS(depth - 1, state, false, moves);
		if (a)
		{
			return true;
		}
		state.UndoMove(move);
		moves.RemoveFront();
	}
	return false;
}

// We used Iterative Deepening DFS, which is similar to a BFS, but it uses much less memory because it doesn't need to keep all the leaf nodes in queue.
//This does come at the cost slightly slower perforance, but only hte constant factor; that is the runntime is assymptotically the same as BFS.
void IterativeDeepeningDFS(SlidingPuzzleState &state)
{
	SlidingPuzzleState *init = state.Clone();
	LList<int> moves;
	for (int i = 0; i < 100; ++i)
	{
		if (DepthLimitedDFS(i, state, false, moves))
		{
			break;
		}
	}

	LList<int> reverseMoves;
	for (int move; !moves.IsEmpty(); moves.RemoveFront())
	{
		move = moves.PeekFront();
		reverseMoves.AddFront(move);
	}

	for (int move; !reverseMoves.IsEmpty(); reverseMoves.RemoveFront())
	{
		move = reverseMoves.PeekFront();
		init->Print();
		std::cout << std::endl;
		init->ApplyMove(move);
	}
	init->Print();
	std::cout << std::endl;
	delete init;
}