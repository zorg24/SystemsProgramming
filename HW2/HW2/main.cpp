#include <iostream>
#include "SlidingPuzzleState.h"

void DepthLimitedDFS(int i, SlidingPuzzleState &state);

void SimpleTest(SlidingPuzzleState& puzzle)
{
	puzzle.ApplyMove(SlidingPuzzleState::UP);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.UndoMove(SlidingPuzzleState::UP);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.ApplyMove(SlidingPuzzleState::LEFT);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.UndoMove(SlidingPuzzleState::LEFT);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.ApplyMove(SlidingPuzzleState::DOWN);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.UndoMove(SlidingPuzzleState::DOWN);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.ApplyMove(SlidingPuzzleState::RIGHT);
	puzzle.Print();
	std::cout << std::endl;
	puzzle.UndoMove(SlidingPuzzleState::RIGHT);
	puzzle.Print();
	std::cout << std::endl;
}

void IsSolutionTest()
{
	const int n[12] = { 1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	SlidingPuzzleState p(n);
	p.Print();
	std::cout << std::endl;
	p.ApplyMove(SlidingPuzzleState::LEFT);
	p.Print();
	std::cout << std::endl << p.IsSolution() << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
//	IsSolutionTest();
	const int nums[12] = { 1, 5, 3, 7, 6, 0, 2, 11, 4, 8, 9, 10 };
	SlidingPuzzleState puzzle(nums);
	puzzle.Print();
	std::cout << std::endl;
//	SimpleTest(puzzle);
	std::cout << "Starting DFS:" << std::endl;
	DepthLimitedDFS(10, puzzle);
	puzzle.Print();
	std::cout << std::endl;
	return 0;
}

//	DepthLimitedDFS(depth, state) {
//		if depth == 0 return
//			moveList = state.GetMoves();
//		for each move in moveList{
//			Apply move to state
//			DepthLimitedDFS(depth - 1, state)
//			Undo move from state
//		}
//	}
void DepthLimitedDFS(int depth, SlidingPuzzleState &state)
{
//	state.Print();
//	std::cout << std::endl;
	LList<int> moveList = state.GetMoves();
	if (depth == 0 || state.IsSolution() || moveList.IsEmpty())
		return;
	for (int move; !moveList.IsEmpty(); moveList.RemoveFront())
	{
		move = moveList.PeekFront();
		state.ApplyMove(move);
		DepthLimitedDFS(depth - 1, state);
		state.UndoMove(move);
	}
}