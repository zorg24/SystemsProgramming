//
//  Lab11 COMP2355 Winter 2015
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread>
#include "Timer.h"

// InitValues - set array values.  Array items are
//   set to the sqrt of their index in the array.
//
// a - pointer to first item to set
// first - index of first array item to set
// last - index of the array item one past the last item to set
void InitValues(double *a, int first, int last) {
  for (int i = first; i < last; ++i) {
    a[i] = sqrt((double) i);
  }
}

// SumValues - sum array values.
//
// a - array to be summed
// sum - return value, the sum of all items in the range
// first - index of first array item to be summed
// last - index of the array item one past the last item to set
void SumValues(const double *a, double *sum, int first, int last) {
  double sumTmp = 0.0;
  for (int i = first; i < last; ++i) {
    sumTmp += a[i];
  }
  *sum = sumTmp;
}

// ThreadedSum - initialize and sum a large array using
//   multiple threads.
//
// numThreads - number of threads to use
// arraySize - size of array to use
double ThreadedSum(int numThreads, size_t arraySize) {
	double sum = 0.0;
	int workSize = arraySize / numThreads;
	double *a = new double[arraySize];
	std::thread **inits = new std::thread*[numThreads];
	int remainder = arraySize % numThreads;
	for (int i = 0; i < numThreads; ++i)
	{
		int finish = i * workSize + workSize;
		if (finish > arraySize)
			finish = arraySize;
		inits[i] = new std::thread(InitValues, a, i * workSize, finish);
	}
	for (int i = 0; i < numThreads; ++i)
	{
		inits[i]->join();
		delete inits[i];
	}
	delete[] inits;

	remainder = arraySize % numThreads;
	std::thread **work = new std::thread*[numThreads];
	double *sums = new double[numThreads];
	for (int i = 0; i < numThreads; ++i)
	{
		int finish = i * workSize + workSize;
		if (finish > arraySize)
			finish = arraySize;
		work[i] = new std::thread(SumValues, a, &sums[i], i * workSize, finish);
		if (remainder > 0)
			remainder--;
	}
	for (int i = 0; i < numThreads; ++i)
	{
		work[i]->join();
		delete work[i];
	}
	delete[] work;

	for (int i = 0; i < numThreads; ++i)
	{
		sum += sums[i];
	}
	delete[] sums;
	delete[] a;

  return sum;
}

int main(int argc, const char * argv[])
{
  // Use the number of hardware threads provided by the CPU(s).
  // If only one hardware thread, use two threads.
  int numThreads = std::thread::hardware_concurrency();
  std::cout << "Hardware threads available: " << numThreads << std::endl;
  if (numThreads < 2) numThreads = 2;  // use at least 2 threads

  // Create a Timer object
  Timer t;

  // Run for each power of 2 from 20 to 26 (You may want to start
  // with 10 to 15 for testing)
  for (int power = 20; power <= 26; power++)
  {
    t.StartTimer();
    double sum1 = ThreadedSum(1, 1<<power);
    t.EndTimer();
    std::cout << "Elapsed time: " << t.GetElapsedTime() << ", "
              << "arraySize " << (1<<power) << ", numThreads = 1, sum = "
              << std::setprecision(15) << sum1 << std::endl;

    t.StartTimer();
    double sumN = ThreadedSum(numThreads, 1<<power);
    t.EndTimer();
    std::cout << "Elapsed time: " << t.GetElapsedTime() << ", "
              << "arraySize " <<(1<<power)<< ", numThreads = "
              << numThreads << ", sum = "
              << std::setprecision(15) << sumN << std::endl;
  }
}
