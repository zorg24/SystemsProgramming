//
//  SimpleParallelBFS.cpp
//  Homework 3
//
//  Created by Nathan Sturtevant on 2/16/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#include "ParallelBFS.h"
#include "SlidingPuzzleState.h"
#include "Timer.h"
#include "SharedLList.h"

namespace ParallelBFS {
	
	const int workSize = 10000;
	
	/** Worker Thread:
	 * Work queue: will send a starting location from which we do workSize work
	 * dataLock: a lock used when writing to the BFS data
	 * data: the depths for the BFS data
	 * seenStates: a counter to mark how many states have had their depths updated
	 * depth: the current depth in the BFS
	 */
	void WorkerThread(SharedLList<uint32_t> *workQueue, std::mutex *dataLock, uint8_t *data, uint32_t *seenStates, int depth)
	{
		
        
	}
	
	void DoBFS(int numThreads)
	{
		std::cout << "Running with " << numThreads << " threads\n";
		// By default, starts at goal state
		SlidingPuzzleState s;
		LList<int> moves;
		SharedLList<uint32_t> workQueue;
		std::mutex lock;
		std::thread **threads = new std::thread*[numThreads];
		
		uint8_t *stateDepths = new uint8_t[s.GetMaxRank()];
		
		// set all values to 255
		memset(stateDepths, 255, s.GetMaxRank());
		uint32_t seenStates = 1;
		stateDepths[s.Rank()] = 0;
		int currDepth = 0;
		
		Timer fullTimer;
		
		std::cout.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed
		std::cout.precision(2);
		
		while (seenStates != s.GetMaxRank())
		{
			Timer roundTimer;
			
			// Write the code:

			// 1. to displatch threads

            for (int x = 0; x < numThreads; x++)
            {
                threads[x] = new std::thread(WorkerThread, &workQueue, &lock, stateDepths, &seenStates, currDepth);
            }

			// 2. to send the work to the queue
            
//            for (uint32_t x = 1; x < s.GetMaxRank(); x+=numThreads)
//            {
//               // workQueue.Add({x, std::min(x+numThreads, });
//            }
            
         //I know the for loop parameter above aren't correct, I'll look into it friday
			// 3. to tell the threads that all work is complete
			// 4. to join with the threads

			
			
			
			std::cout << roundTimer.GetElapsedTime() << "s elapsed. ";
			std::cout << "Depth " << currDepth;
			std::cout << " complete. " << seenStates << " of " << s.GetMaxRank();
			std::cout << " total states seen.\n";
			currDepth++;
		}
		std::cout << fullTimer.EndTimer() << "s elapsed\n";
		delete [] stateDepths;
		delete [] threads;
	}
	
	//Sample Run on a 2.3 GHz Intel Core i7 (4 real + 4 virual cores)
	//  Running with 8 threads
	//	0.59s elapsed. Depth 0 complete. 3 of 239500800 total states seen.
	//	0.55s elapsed. Depth 1 complete. 7 of 239500800 total states seen.
	//	0.58s elapsed. Depth 2 complete. 16 of 239500800 total states seen.
	//	0.55s elapsed. Depth 3 complete. 36 of 239500800 total states seen.
	//	0.55s elapsed. Depth 4 complete. 73 of 239500800 total states seen.
	//	0.57s elapsed. Depth 5 complete. 136 of 239500800 total states seen.
	//	0.55s elapsed. Depth 6 complete. 258 of 239500800 total states seen.
	//	0.53s elapsed. Depth 7 complete. 490 of 239500800 total states seen.
	//	0.56s elapsed. Depth 8 complete. 921 of 239500800 total states seen.
	//	0.58s elapsed. Depth 9 complete. 1702 of 239500800 total states seen.
	//	0.55s elapsed. Depth 10 complete. 3094 of 239500800 total states seen.
	//	0.53s elapsed. Depth 11 complete. 5588 of 239500800 total states seen.
	//	0.52s elapsed. Depth 12 complete. 10030 of 239500800 total states seen.
	//	0.57s elapsed. Depth 13 complete. 17884 of 239500800 total states seen.
	//	0.56s elapsed. Depth 14 complete. 31783 of 239500800 total states seen.
	//	0.57s elapsed. Depth 15 complete. 55998 of 239500800 total states seen.
	//	0.59s elapsed. Depth 16 complete. 97800 of 239500800 total states seen.
	//	0.55s elapsed. Depth 17 complete. 168967 of 239500800 total states seen.
	//	0.51s elapsed. Depth 18 complete. 288855 of 239500800 total states seen.
	//	0.48s elapsed. Depth 19 complete. 487218 of 239500800 total states seen.
	//	0.37s elapsed. Depth 20 complete. 810424 of 239500800 total states seen.
	//	0.44s elapsed. Depth 21 complete. 1326202 of 239500800 total states seen.
	//	0.41s elapsed. Depth 22 complete. 2137202 of 239500800 total states seen.
	//	0.45s elapsed. Depth 23 complete. 3385213 of 239500800 total states seen.
	//	0.44s elapsed. Depth 24 complete. 5270492 of 239500800 total states seen.
	//	0.51s elapsed. Depth 25 complete. 8052888 of 239500800 total states seen.
	//	0.58s elapsed. Depth 26 complete. 12062610 of 239500800 total states seen.
	//	0.76s elapsed. Depth 27 complete. 17683964 of 239500800 total states seen.
	//	0.92s elapsed. Depth 28 complete. 25331836 of 239500800 total states seen.
	//	1.25s elapsed. Depth 29 complete. 35397636 of 239500800 total states seen.
	//	1.51s elapsed. Depth 30 complete. 48158049 of 239500800 total states seen.
	//	1.91s elapsed. Depth 31 complete. 63728835 of 239500800 total states seen.
	//	2.26s elapsed. Depth 32 complete. 81900441 of 239500800 total states seen.
	//	2.73s elapsed. Depth 33 complete. 102200317 of 239500800 total states seen.
	//	2.98s elapsed. Depth 34 complete. 123787565 of 239500800 total states seen.
	//	3.22s elapsed. Depth 35 complete. 145628724 of 239500800 total states seen.
	//	3.28s elapsed. Depth 36 complete. 166535629 of 239500800 total states seen.
	//	3.16s elapsed. Depth 37 complete. 185434986 of 239500800 total states seen.
	//	2.83s elapsed. Depth 38 complete. 201493321 of 239500800 total states seen.
	//	2.55s elapsed. Depth 39 complete. 214265924 of 239500800 total states seen.
	//	1.99s elapsed. Depth 40 complete. 223781141 of 239500800 total states seen.
	//	1.63s elapsed. Depth 41 complete. 230364322 of 239500800 total states seen.
	//	1.18s elapsed. Depth 42 complete. 234607075 of 239500800 total states seen.
	//	0.83s elapsed. Depth 43 complete. 237110948 of 239500800 total states seen.
	//	0.58s elapsed. Depth 44 complete. 238461216 of 239500800 total states seen.
	//	0.43s elapsed. Depth 45 complete. 239104461 of 239500800 total states seen.
	//	0.28s elapsed. Depth 46 complete. 239374764 of 239500800 total states seen.
	//	0.42s elapsed. Depth 47 complete. 239467075 of 239500800 total states seen.
	//	0.48s elapsed. Depth 48 complete. 239494191 of 239500800 total states seen.
	//	0.57s elapsed. Depth 49 complete. 239499581 of 239500800 total states seen.
	//	0.54s elapsed. Depth 50 complete. 239500696 of 239500800 total states seen.
	//	0.57s elapsed. Depth 51 complete. 239500782 of 239500800 total states seen.
	//	0.63s elapsed. Depth 52 complete. 239500800 of 239500800 total states seen.
	//	53.77s elapsed
	
}
