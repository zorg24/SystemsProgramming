//
//  TestPagedDiskArray.h
//  COMP2355 Winter 2015 HW4
//

#ifndef __HW4__TestPagedDiskArray__
#define __HW4__TestPagedDiskArray__

#include <cstddef>
#include "PagedDiskArray.h"
#include <iostream>

// TestPagedDiskArrray - run tests on the PagedDiskArray class with specified
//    page size and number of pages.
template<class T>
void TestPagedDiskArray(size_t pageSize, size_t numPages);

// TestPagedDiskArrray - run tests on the PagedDiskArray class with specified
//    page size and number of pages.
//
// Print error messages when errors are detected.  Note that uint8_t values to
// be printed are wrapped with "unsigned()" so that they will be interpreted by
// the output stream as unisgned numbers rather than arbitrary character values.

template<class T>
void TestPagedDiskArray(size_t pageSize, size_t numPages) {
    std::cout << "Testing page size " << pageSize << ", num pages = " << numPages << "\n";
    srand(1);  // reset pseudo-random number generator

    // Create a disk array
    const char fileName[] = "disk_array.dat";
    PagedDiskArray<T> d(pageSize, numPages, fileName);

    // Create some test data to write and read (don't run this test with a really big array,
    // since the test data is all in memory)
    size_t arraySize = pageSize * numPages;
    T *testData = new T[arraySize];
    for (size_t i = 0; i < arraySize; ++i) {
        testData[i] = rand() & 0xFF;  // set test data to some semi-random value
    }

    // Set and read back every array entry
    for (size_t i = 0; i < arraySize; ++i) {
        d.set(i, testData[i]);
        T valueRead = d[i];
        if (valueRead != testData[i]) {
            std::cerr << "ERROR: during writing, d[" << i << "] = " << unsigned(valueRead)
                    << ", expected " << unsigned(testData[i]) << "\n";
        }
    }

    // Read back entries sequentially, then change each entry
    for (size_t i = 0; i < arraySize; ++i) {
        uint64_t valueRead = d[i];
        if (valueRead != testData[i]) {
            std::cerr << "ERROR: during read back, d[" << i << "] = " << unsigned(valueRead)
                    << ", expected " << unsigned(testData[i]) << "\n";
        }
        testData[i] = rand() & 0xFF;  // set test data to different semi-random value
        d.set(i, testData[i]);
    }

    // Generate 100 pseudo-random locations in file
    const size_t numLocations = 100;
    size_t locations[numLocations];
    for (size_t i = 0; i < numLocations; ++i) {
        locations[i] = (rand() % numPages) * pageSize + (rand() % pageSize);
    }

    // Write the 100 locations in the file, then read them back
    for (size_t i = 0; i < numLocations; ++i) {
        testData[locations[i]] = rand() & 0xFF;  // set test data to different semi-random value
        d.set(locations[i], testData[locations[i]]);
    }
    for (size_t i = 0; i < numLocations; ++i) {
        T valueRead = d[locations[i]];
        T valueExpected = testData[locations[i]];
        if (valueRead != testData[locations[i]]) {
            std::cerr << "ERROR: during random write/read at location " << locations[i] << ", read "
                    << unsigned(valueRead) << ", expected " << unsigned(valueExpected) << "\n";
        }
    }

    std::cout << "Test finished for page size " << pageSize << ", num pages = " << numPages << "\n";
}

#endif /* defined(__HW4__TestPagedDiskArray__) */
