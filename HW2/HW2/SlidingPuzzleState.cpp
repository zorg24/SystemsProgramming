#include "SlidingPuzzleState.h"
#include <iostream>


SlidingPuzzleState::SlidingPuzzleState(const int tiles_[12])
{
    for (int i = 0; i < 12; ++i)
    {
        for (int j = i; tiles_[i] != tiles_[j]; ++j)
        {
            std::cerr << "The input contains a duplicate entry" << std::endl;
        }
    }
    
    for (int i = 0; i < 12; ++i)
    {
        if (tiles_[i] >= 0 && tiles_[i] < 12)
        {
            tiles[i] = tiles_[i];
        }
        else
        {
            std::cerr << "The " << i << "th element of the input contains an element outside of the range [0,12).";
        }
    }
}


SlidingPuzzleState::~SlidingPuzzleState()
{
}



LList<int> SlidingPuzzleState::GetMoves()
{
    LList<int> *temp = new LList<int>;
    //    finding the empty cell
    int row = 0, col = 0;
    for (row = 0; row < 3; ++row)
    {
        for (col = 0; col < 4; ++col)
        {
            if (tiles[4 * row + col] == 0)
            {
                break;
            }
        }
        if (tiles[4 * row + col] == 0)
        {
            break;
        }
    }
    if(IsValid(row-1, col))
    {
        temp->AddFront(LEFT);
    }
    if(IsValid(row+1, col))
    {
        temp->AddFront(RIGHT);
    }
    if(IsValid(row, col-1))
    {
        temp->AddFront(UP);
    }
    if(IsValid(row, col+1))
    {
        temp->AddFront(DOWN);
    }
    
    return *temp;
}

bool SlidingPuzzleState::IsValid(int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col > 4;
}