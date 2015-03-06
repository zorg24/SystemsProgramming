//
//  PagedDiskArray.cpp
//  COMP2355 Winter 2015 HW4
//
#define _CRT_SECURE_NO_WARNINGS    // needed for Visual Studio

#include "PagedDiskArray.h"
// Implement the PagedDiskArray class here

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
		if (fseek(pageFile, pageSize * f->pageLoaded, SEEK_SET) != 0)
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
	if (fseek(pageFile, pageSize * pageNum, SEEK_SET) != 0)
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
