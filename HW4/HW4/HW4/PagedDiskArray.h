//
//  PagedDiskArray.h
//  COMP2355 Winter 2015 HW4
//

#ifndef __HW4__PagedDiskArray__
#define __HW4__PagedDiskArray__

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

// PagedDiskArray - provide an object that acts like an array of uint8_t (bytes)

template<class T>
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
	T operator[](size_t index);

	// Change a value in the array.Terminates program if out of bounds.
	//
	// index - byte index in the paged array.
	// value - value to store in the array at the specified index.
	void set(size_t index, T value);

private:
	const size_t pageSize;  // page size in bytes
	const size_t numPages;  // number of pages in array
	const size_t arraySize; // total array size in bytes (pageSize*numPages)
	static const size_t numPageFrames = 2;  // number of buffers to cache pages
	uint64_t pseudoTime;    // advance by one each time any page is accessed

	// Define struct for page frame
	struct PageFrame {
		T *buffer;          // pointer to buffer
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
	T *GetElement(size_t index, bool dirty);
};

template<class T>
PagedDiskArray<T>::PagedDiskArray(size_t pageSize_init, size_t numPages_init, const char *fileName_init) : pageSize(pageSize_init), numPages(numPages_init), arraySize(pageSize * numPages) //initalizing datamembers to parameters
{
	//   fileName - file to use to store array. File will be erased if
	//              already exists, and filled with all 0.
	PageFrame pf;
	pf.buffer = new T[pageSize];
	memset(pf.buffer, 0, pageSize);
	pf.dirty = false;
	pf.pageLoaded = 0;
	pf.accessPTime = 0;
	pseudoTime = 0;

	FILE *f = fopen(fileName_init, "wb+");
	pageFile = f;
	for (int i = 0; i < numPages; ++i)
	{
		fwrite(pf.buffer, sizeof(T), pageSize, f);
	}

	for (int i = 0; i < numPageFrames; i++)
	{
		frames[i].buffer = new T[pageSize];
		memset(frames[i].buffer, 0, pageSize);
	}
	delete[] pf.buffer;
}

template<class T>
PagedDiskArray<T>::~PagedDiskArray()
{
	fclose(pageFile);
	for (int i = 0; i < numPageFrames; i++)
	{
		delete[] frames[i].buffer;
	}
}

// Return a value in the array. Terminates program if out of bounds.
//
// index - byte index in the paged array.
template<class T>
T PagedDiskArray<T>::operator[](size_t index)
{
	return *GetElement(index, false);
}

// Change a value in the array.Terminates program if out of bounds.
//
// index - byte index in the paged array.
// value - value to store in the array at the specified index.
template<class T>
void PagedDiskArray<T>::set(size_t index, T value)
{
	if (index > arraySize)
	{
		std::terminate();
	}
	*GetElement(index, true) = value;
}

template<class T>
void PagedDiskArray<T>::WritePageIfDirty(PageFrame *f)
{
	if (f->dirty)
	{
		if (fseek(pageFile, pageSize * f->pageLoaded * sizeof(T), SEEK_SET) != 0)
		{
			std::cerr << "Seek to write failed.";
		}
		if (fwrite(f->buffer, sizeof(T), pageSize, pageFile) != pageSize)
		{
			std::cerr << "Write failed.";
		}
	}
}

// Write all dirty pages to the disk file
template<class T>
void PagedDiskArray<T>::Flush()
{
	for (int i = 0; i < numPageFrames; ++i)
	{
		WritePageIfDirty(frames + i);
	}
}

// Load page into frame
template<class T>
void PagedDiskArray<T>::LoadPage(size_t pageNum, PageFrame *f)
{
	if (fseek(pageFile, pageSize * pageNum * sizeof(T), SEEK_SET) != 0)
	{
		std::cerr << "Seek to read failed.";
	}
	if (fread(f->buffer, sizeof(T), pageSize, pageFile) != pageSize)
	{
		std::cerr << "Read failed.";
	}
	f->pageLoaded = pageNum;
	f->accessPTime = pseudoTime;
	f->dirty = false;
}

// Map page number to page frame in memory - returns nullptr if not present
template<class T>
typename PagedDiskArray<T>::PageFrame* PagedDiskArray<T>::GetPageFrame(size_t pageNum)
{
	for (int i = 0; i < numPageFrames; ++i)
	{
		if (pageNum == frames[i].pageLoaded)
		{
			return frames + i;
		}
	}
	return nullptr;
}

// Choose best frame to replace in memory (smallest timeLoaded)
template<class T>
typename PagedDiskArray<T>::PageFrame* PagedDiskArray<T>::ChooseReplacementFrame()
{
	uint64_t minTime = ~0;
	int minIndex = 0;
	for (int i = 0; i < numPageFrames; ++i)
	{
		if (frames[i].accessPTime < minTime)
		{
			minTime = frames[i].accessPTime;
			minIndex = i;
		}
	}
	return frames + minIndex;
}
// Get pointer to desired array element, writing and reading
// page frames as necessary.  Set page frame dirty flag if
// dirty is true;
template<class T>
T* PagedDiskArray<T>::GetElement(size_t index, bool dirty)
{
	pseudoTime++;
	PageFrame *pf = GetPageFrame(index / pageSize);

	if (pf == nullptr)
	{
		PageFrame *p = ChooseReplacementFrame();
		WritePageIfDirty(p);
		LoadPage(index / pageSize, p);
		pf = p;
	}
	if (dirty)
		pf->dirty = true;
	pf->accessPTime = pseudoTime;
	return &pf->buffer[index % pageSize];
}

#endif /* defined(__HW4__PagedDiskArray__) */
