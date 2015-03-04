//
//  PagedDiskArray.cpp
//  COMP2355 Winter 2015 HW4
//
#define _CRT_SECURE_NO_WARNINGS    // needed for Visual Studio

#include "PagedDiskArray.h"

// Implement the PagedDiskArray class here

PagedDiskArray::PagedDiskArray(size_t pageSize_init, size_t numPages_init, const char *fileName_init)  : pageSize(pageSize_init), numPages(numPages_init), arraySize(pageSize * numPages) //initalizing datamembers to parameters
{
    
}

PagedDiskArray::~PagedDiskArray()
{
    
}

uint8_t PagedDiskArray::operator[](size_t index)
{
    
}


void PagedDiskArray::set(size_t index, uint8_t value)
{
    
}


void PagedDiskArray::WritePageIfDirty(PageFrame *f)
{
    
}

// Write all dirty pages to the disk file
void PagedDiskArray::Flush()
{
    
}

// Load page into frame
void PagedDiskArray::LoadPage(size_t pageNum, PageFrame *f)
{
    
}
// Map page number to page frame in memory - returns nullptr if not present
PageFrame* PagedDiskArray::GetPageFrame(size_t pageNum)
{
    
}

// Choose best frame to replace in memory (smallest timeLoaded)
PageFrame* PagedDiskArray::ChooseReplacementFrame()
{
    
}
// Get pointer to desired array element, writing and reading
// page frames as necessary.  Set page frame dirty flag if
// dirty is true;
uint8_t* PagedDiskArray::GetElement(size_t index, bool dirty)
{
    
}


