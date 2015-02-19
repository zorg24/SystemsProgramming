#include <iostream>
#include "LList.h"
#include "SlidingPuzzleState.h"
#include <cstdint>
#include "Timer.h"

namespace SequentialBFS {

	void DoBFS()
	{
		// By default, starts at goal state
		SlidingPuzzleState s;
		LList<int> moves;

		uint8_t *stateDepths = new uint8_t[s.GetMaxRank()];

		// set all values to 255
		memset(stateDepths, 255, s.GetMaxRank());
		uint32_t seenStates = 1;
		stateDepths[s.Rank()] = 0;
		int currDepth = 0;

		Timer fullTimer;

		std::cout.setf(std::ios::fixed, std::ios::floatfield); // floatfield set to fixed
		std::cout.precision(2);

		while (seenStates != s.GetMaxRank()) //keep going until seenStates is the maxRank
		{
			Timer roundTimer; //new timer
			for (int x = 0; x < s.GetMaxRank(); x++) //loop through the all the entries (meaning maxRank)
			{
				if (stateDepths[x] == currDepth) //if the state we're at is the current Depth
				{
					s.Unrank(x); //convert the index into a map
					s.GetMoves(moves); //get the moves from this current state
					while (moves.IsEmpty() == false) //as long as there are moves
					{
						s.ApplyMove(moves.PeekFront()); //on this map, apply the move at the front of the map
						uint32_t rank = s.Rank(); //make variable named 'rank' to get the index of this map
						s.UndoMove(moves.PeekFront()); //on this map, undo hte move at the front of the map
						moves.RemoveFront(); //remove the front of of this list

						if (stateDepths[rank] == 255) //if the state at this index is equal to 255 (something unseen)
						{
							stateDepths[rank] = currDepth + 1; //then set the value at this rank (index) to one more than the current depth since it's one move away from where we  currently are
							seenStates++; //increment seenstates since we've seen another state
						}
					}
				}
			}
			std::cout << roundTimer.GetElapsedTime() << "s elapsed. ";
			std::cout << "Depth " << currDepth;
			std::cout << " complete. " << seenStates << " of " << s.GetMaxRank();
			std::cout << " total states seen.\n";
			currDepth++; //our current depth is incremented
		}
        //INDEX translates to the stae
        //UNRANK converts the index the map
        //RANK the map makes it hte index
		std::cout << fullTimer.EndTimer() << "s elapsed\n";
		delete[] stateDepths;
	}

	//Sample Run:
	//  0.43s elapsed. Depth 0 complete. 3 of 239500800 total states seen.
	//  0.44s elapsed. Depth 1 complete. 7 of 239500800 total states seen.
	//  0.44s elapsed. Depth 2 complete. 16 of 239500800 total states seen.
	//  0.44s elapsed. Depth 3 complete. 36 of 239500800 total states seen.
	//  0.44s elapsed. Depth 4 complete. 73 of 239500800 total states seen.
	//  0.43s elapsed. Depth 5 complete. 136 of 239500800 total states seen.
	//  0.43s elapsed. Depth 6 complete. 258 of 239500800 total states seen.
	//  0.44s elapsed. Depth 7 complete. 490 of 239500800 total states seen.
	//  0.42s elapsed. Depth 8 complete. 921 of 239500800 total states seen.
	//  0.43s elapsed. Depth 9 complete. 1702 of 239500800 total states seen.
	//  0.42s elapsed. Depth 10 complete. 3094 of 239500800 total states seen.
	//  0.44s elapsed. Depth 11 complete. 5588 of 239500800 total states seen.
	//  0.43s elapsed. Depth 12 complete. 10030 of 239500800 total states seen.
	//  0.43s elapsed. Depth 13 complete. 17884 of 239500800 total states seen.
	//  0.46s elapsed. Depth 14 complete. 31783 of 239500800 total states seen.
	//  0.47s elapsed. Depth 15 complete. 55998 of 239500800 total states seen.
	//  0.48s elapsed. Depth 16 complete. 97800 of 239500800 total states seen.
	//  0.46s elapsed. Depth 17 complete. 168967 of 239500800 total states seen.
	//  0.51s elapsed. Depth 18 complete. 288855 of 239500800 total states seen.
	//  0.55s elapsed. Depth 19 complete. 487218 of 239500800 total states seen.
	//  0.62s elapsed. Depth 20 complete. 810424 of 239500800 total states seen.
	//  0.72s elapsed. Depth 21 complete. 1326202 of 239500800 total states seen.
	//  0.85s elapsed. Depth 22 complete. 2137202 of 239500800 total states seen.
	//  1.06s elapsed. Depth 23 complete. 3385213 of 239500800 total states seen.
	//  1.49s elapsed. Depth 24 complete. 5270492 of 239500800 total states seen.
	//  1.90s elapsed. Depth 25 complete. 8052888 of 239500800 total states seen.
	//  2.53s elapsed. Depth 26 complete. 12062610 of 239500800 total states seen.
	//  3.32s elapsed. Depth 27 complete. 17683964 of 239500800 total states seen.
	//  4.48s elapsed. Depth 28 complete. 25331836 of 239500800 total states seen.
	//  5.87s elapsed. Depth 29 complete. 35397636 of 239500800 total states seen.
	//  7.58s elapsed. Depth 30 complete. 48158049 of 239500800 total states seen.
	//  9.33s elapsed. Depth 31 complete. 63728835 of 239500800 total states seen.
	//  11.38s elapsed. Depth 32 complete. 81900441 of 239500800 total states seen.
	//  12.96s elapsed. Depth 33 complete. 102200317 of 239500800 total states seen.
	//  14.53s elapsed. Depth 34 complete. 123787565 of 239500800 total states seen.
	//  15.29s elapsed. Depth 35 complete. 145628724 of 239500800 total states seen.
	//  15.59s elapsed. Depth 36 complete. 166535629 of 239500800 total states seen.
	//  15.08s elapsed. Depth 37 complete. 185434986 of 239500800 total states seen.
	//  13.50s elapsed. Depth 38 complete. 201493321 of 239500800 total states seen.
	//  11.43s elapsed. Depth 39 complete. 214265924 of 239500800 total states seen.
	//  9.20s elapsed. Depth 40 complete. 223781141 of 239500800 total states seen.
	//  6.99s elapsed. Depth 41 complete. 230364322 of 239500800 total states seen.
	//  5.02s elapsed. Depth 42 complete. 234607075 of 239500800 total states seen.
	//  3.37s elapsed. Depth 43 complete. 237110948 of 239500800 total states seen.
	//  2.19s elapsed. Depth 44 complete. 238461216 of 239500800 total states seen.
	//  1.39s elapsed. Depth 45 complete. 239104461 of 239500800 total states seen.
	//  0.89s elapsed. Depth 46 complete. 239374764 of 239500800 total states seen.
	//  0.62s elapsed. Depth 47 complete. 239467075 of 239500800 total states seen.
	//  0.50s elapsed. Depth 48 complete. 239494191 of 239500800 total states seen.
	//  0.46s elapsed. Depth 49 complete. 239499581 of 239500800 total states seen.
	//  0.43s elapsed. Depth 50 complete. 239500696 of 239500800 total states seen.
	//  0.42s elapsed. Depth 51 complete. 239500782 of 239500800 total states seen.
	//  0.44s elapsed. Depth 52 complete. 239500800 of 239500800 total states seen.
	//  190.43s elapsed

	// Note: before code optimization, running time was 278.41s

}

