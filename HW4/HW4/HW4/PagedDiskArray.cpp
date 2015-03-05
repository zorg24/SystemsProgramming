//
//  PagedDiskArray.cpp
//  COMP2355 Winter 2015 HW4
//
#define _CRT_SECURE_NO_WARNINGS    // needed for Visual Studio

#include "PagedDiskArray.h"
// Implement the PagedDiskArray class here

PagedDiskArray::PagedDiskArray(size_t pageSize_init, size_t numPages_init, const char *fileName_init)  : pageSize(pageSize_init), numPages(numPages_init), arraySize(pageSize * numPages) //initalizing datamembers to parameters
{
    //   fileName - file to use to store array. File will be erased if
    //              already exists, and filled with all 0.
    PageFrame pf;
    pf.buffer = new uint8_t[pageSize];
    memset(pf.buffer, 0, pageSize);
    pf.dirty = false;
    pf.pageLoaded = 0;
    pf.accessPTime = 0;
    pseudoTime = 0;
    
    FILE *f = fopen(fileName_init, "wb+");
    pageFile = f;
    if(f != 0)
    {
        for(int i = 0; i < numPages; ++i)
        {
            fwrite(&pf, sizeof(pf) , 1, f);
            pf.pageLoaded++;
        }
    }
    
    for (int i = 0; i < numPageFrames; i++)
    {
        frames[i].buffer = new uint8_t[pageSize];
        memset(frames[i].buffer, 0, pageSize);
    }
    delete [] pf.buffer;
    
}

PagedDiskArray::~PagedDiskArray()
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

uint8_t PagedDiskArray::operator[](size_t index)
{
    return *GetElement(index, false);
}

// Change a value in the array.Terminates program if out of bounds.
//
// index - byte index in the paged array.
// value - value to store in the array at the specified index.
void PagedDiskArray::set(size_t index, uint8_t value)
{
    if (index > arraySize)
    {
        std::terminate();
    }
    *GetElement(index, true) = value;
}


void PagedDiskArray::WritePageIfDirty(PageFrame *f)
{
	if (f->dirty)
	{
		fwrite(f, sizeof(PageFrame), 1, pageFile);
	}
}

// Write all dirty pages to the disk file
void PagedDiskArray::Flush()
{
	for (int i = 0; i < numPageFrames; ++i)
	{
		WritePageIfDirty(frames + i);
	}
}

// Load page into frame
void PagedDiskArray::LoadPage(size_t pageNum, PageFrame *f)
{
	fread(f, sizeof(PageFrame), 1, pageFile);
}

// Map page number to page frame in memory - returns nullptr if not present
PagedDiskArray::PageFrame* PagedDiskArray::GetPageFrame(size_t pageNum)
{
    for(int i = 0; i < numPageFrames; ++i)
    {
        if(pageNum == frames[i].pageLoaded)
        {
            return frames+i;
        }
    }
    return nullptr;
}

// Choose best frame to replace in memory (smallest timeLoaded)
PagedDiskArray::PageFrame* PagedDiskArray::ChooseReplacementFrame()
{
    uint64_t minTime = ~0;
    int minIndex = 0;
    for(int i = 0; i < numPageFrames; ++i)
    {
        if(frames[i].accessPTime < minTime)
        {
            minTime = frames[i].accessPTime;
            minIndex = i;
        }
    }
    return frames+minIndex;
}
// Get pointer to desired array element, writing and reading
// page frames as necessary.  Set page frame dirty flag if
// dirty is true;
uint8_t* PagedDiskArray::GetElement(size_t index, bool dirty)
{
    PageFrame *pf = GetPageFrame(index / pageSize);
    
    if(pf == nullptr)
    {
        PageFrame *p = ChooseReplacementFrame();
        WritePageIfDirty(p);
        LoadPage(index / pageSize, p);
        pf = p;
    }
    if (dirty)
        pf->dirty = true;
    return &pf->buffer[index % pageSize];
}


