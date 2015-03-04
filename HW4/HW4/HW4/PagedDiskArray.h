//
//  PagedDiskArray.h
//  COMP2355 Winter 2015 HW4
//

#ifndef __HW4__PagedDiskArray__
#define __HW4__PagedDiskArray__

#include <cstddef>
#include <cstdint>
#include <cstdio>

// PagedDiskArray - provide an object that acts like an array of uint8_t (bytes)

class PagedDiskArray {
public:
	// Constructor - create disk file
	//
	//   pageSize - size of each page in bytes.
	//   numPages - number of pages in file
	//   fileName - file to use to store array. File will be erased if
	//              already exists, and filled with all 0.
	PagedDiskArray(size_t pageSize_init, size_t numPages_init, const char *fileName_init);

	// Destructor - flush dirty pages, close file, and free all memory.
	~PagedDiskArray();

	// Return a value in the array. Terminates program if out of bounds.
	//
	// index - byte index in the paged array.
	uint8_t operator[](size_t index);

	// Change a value in the array.Terminates program if out of bounds.
	//
	// index - byte index in the paged array.
	// value - value to store in the array at the specified index.
	void set(size_t index, uint8_t value);

private:
	const size_t pageSize;  // page size in bytes
	const size_t numPages;  // number of pages in array
	const size_t arraySize; // total array size in bytes (pageSize*numPages)
	static const size_t numPageFrames = 2;  // number of buffers to cache pages
	uint64_t pseudoTime;    // advance by one each time any page is accessed

	// Define struct for page frame
	struct PageFrame {
		uint8_t *buffer;          // pointer to buffer
		size_t pageLoaded;     // page number currently loaded
		bool dirty;            // true if page modified in memory
		uint64_t accessPTime;  // psuedoTime page was most recently accessed
	};

	PageFrame frames[numPageFrames];

	FILE *pageFile;          // file pointer to access page file

	// Write page frame to disk if dirty, then mark non-dirty
	void WritePageIfDirty(PageFrame *f);

	// Write all dirty pages to the disk file
	void Flush();

	// Load page into frame
	void LoadPage(size_t pageNum, PageFrame *f);

	// Map page number to page frame in memory - returns nullptr if not present
	PageFrame *GetPageFrame(size_t pageNum);

	// Choose best frame to replace in memory (smallest timeLoaded)
	PageFrame *ChooseReplacementFrame();

	// Get pointer to desired array element, writing and reading
	// page frames as necessary.  Set page frame dirty flag if
	// dirty is true;
	uint8_t *GetElement(size_t index, bool dirty);
};

#endif /* defined(__HW4__PagedDiskArray__) */
