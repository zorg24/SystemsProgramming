//Kris Douglass and Nathan Saslavsky
#include <iostream>
#include "SlidingPuzzleState.h"
#include <cassert>

void DepthLimitedDFS(int depth, SlidingPuzzleState &state);
bool DepthLimitedDFS(int depth, SlidingPuzzleState &state, bool isSolved, LList<int> &moves);
void Solve(SlidingPuzzleState &state);
const int kUp = 0;
const int kDown = 1;
const int kLeft = 2;
const int kRight = 3;

void TestHomework2()
{
	const int goal[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 11 };
	SlidingPuzzleState state(goal);

	// Perform solution test
	assert(state.IsSolution());

	// test that we can clone the state properly
	SlidingPuzzleState *clone = state.Clone();
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			assert(state.GetTileInSquare(row, col) == clone->GetTileInSquare(row, col));
		}
	}
	delete clone;
	clone = 0;

	// Test that we end up in the proper state

	const int moves[] = { kRight, kUp, kUp, kLeft, kLeft, kDown, kDown, kLeft, kUp, kRight, kRight, kDown, kRight, kUp, kLeft, kUp, kRight, kDown, kDown, kLeft, kUp, kRight, kUp, kLeft, kLeft, kLeft };

	for (int x = 25; x >= 0; x--)
	{
		assert(state.UndoMove(moves[x]) == true);
		assert(state.IsSolution() == false);
	}

	const int sol[] = { 1, 10, 3, 6, 8, 2, 5, 11, 9, 4, 0, 7 };
	SlidingPuzzleState solution(sol);
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			assert(state.GetTileInSquare(row, col) == solution.GetTileInSquare(row, col));
		}
	}

	// Test that we get back to the start state
	for (int x = 0; x < 26; x++)
	{
		assert(state.ApplyMove(moves[x]) == true);
	}
	assert(state.IsSolution() == true);


	// Test legal actions as we move across the board

	assert(solution.ApplyMove(kDown) == false);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kRight) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kRight) == false);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kUp) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kUp) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kUp) == false);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kLeft) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kLeft) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kLeft) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kLeft) == false);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kDown) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kDown) == true);
	assert(solution.IsSolution() == false);
	assert(solution.ApplyMove(kDown) == false);
	assert(solution.IsSolution() == false);

	solution.Print();

	// Test that we end up in the proper state

	const int modifiedState[] = { 8, 1, 10, 3, 9, 2, 5, 6, 0, 4, 7, 11 };
	SlidingPuzzleState modified(modifiedState);
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			assert(modified.GetTileInSquare(row, col) == solution.GetTileInSquare(row, col));
		}
	}

	// Test that you don't generate illegal moves in the corners
	SlidingPuzzleState newstate(goal);
	LList<int> acts;
	newstate.GetMoves(acts);
	for (int x = 0; x < 2; x++)
	{
		assert(acts.IsEmpty() == false);
		assert(acts.PeekFront() != kUp && acts.PeekFront() != kLeft);
		acts.RemoveFront();
	}
	assert(newstate.ApplyMove(kRight) == true);
	assert(newstate.ApplyMove(kRight) == true);
	assert(newstate.ApplyMove(kRight) == true);
	assert(newstate.ApplyMove(kDown) == true);
	assert(newstate.ApplyMove(kDown) == true);

	newstate.GetMoves(acts);
	newstate.GetMoves(acts); // should still only have 2 moves in the list
	for (int x = 0; x < 2; x++)
	{
		assert(acts.IsEmpty() == false);
		assert(acts.PeekFront() != kRight && acts.PeekFront() != kDown);
		acts.RemoveFront();
	}


}

int main(int argc, char* argv[]) {
	TestHomework2();
	return 0;
}

void DepthLimitedDFS(int depth, SlidingPuzzleState &state)
{
	LList<int> moveList;
	state.GetMoves(moveList);
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
	LList<int> moveList;
	state.GetMoves(moveList);
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

//What's doing is calling a modified version of the DFS which takes a LList reference that is used to track the moves, additionally it intentionally returns the game in a solved state rather than the initial state
//This was done in order to prevent the moves from being the removed from the LList
//Lastly the modified DFS returns a bool that is true if it solved it successfully, this is done so that it can be called with increasing depths (starting at 1) to ensure that an optimal strategy is found

//To call it simply pass a SlidingPuzzleState and it will be solved and the sequence of states to get to the solution will be printed
//Arbitrarily I put a limit of 100 on the depth it will search to, before giving up, however this can be trivially changed by modifying the for loop
void Solve(SlidingPuzzleState &state)
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