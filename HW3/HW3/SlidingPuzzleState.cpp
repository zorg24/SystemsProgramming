#include "SlidingPuzzleState.h"
#include <iostream>


SlidingPuzzleState::SlidingPuzzleState()
{
	tiles = new int[12];
	for (int i = 0; i < 12; ++i)
		tiles[i] = i;
}


SlidingPuzzleState::SlidingPuzzleState(const int tiles_[12])
{
    tiles = new int[12];
    for (int i = 0; i < 12; ++i)
    {
        for (int j = i + 1; j < 12; ++j)
        {
			if (tiles_[i] == tiles_[j])
				std::cerr << "The input contains a duplicate entry specifically it contains two of the element " << tiles_[i] << std::endl;
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
            std::cerr << "The " << i << "th element of the input contains an element outside of the range [0,12)." << std::endl;
        }
    }
}

SlidingPuzzleState::~SlidingPuzzleState()
{
	delete[] tiles;
}

void SlidingPuzzleState::GetMoves(LList<int> &l)
{
    int row = 0, col = 0;
    GetEmptySquare(row, col);
    
    if(IsValid(row-1, col))
    {
        l.AddFront(UP);
    }
    if(IsValid(row+1, col))
    {
        l.AddFront(DOWN);
    }
    if(IsValid(row, col-1))
    {
        l.AddFront(LEFT);
    }
    if(IsValid(row, col+1))
    {
        l.AddFront(RIGHT);
    }
}

bool SlidingPuzzleState::IsValid(int row, int col)
{
    return (row >= 0 && row < 3 && col >= 0 && col < 4);
}

bool SlidingPuzzleState::ApplyMove(int move)
{
    bool ret = false;
	LList<int> moves;
    for (GetMoves(moves); !moves.IsEmpty(); moves.RemoveFront())
    {
        if (moves.PeekFront() == move)
        {
            ret = true;
            break;
        }
    }
    
    if (!ret)
    {
        return ret;
    }
    
    int row = 0, col = 0;
    GetEmptySquare(row, col);
    
    int otherIndex;
    switch (move)
    {
        case LEFT:
            otherIndex = 4 * row + (col - 1);
            break;
        case RIGHT:
            otherIndex = 4 * row + (col + 1);
            break;
        case UP:
            otherIndex = 4 * (row - 1) + col;
            break;
        case DOWN:
            otherIndex = 4 * (row + 1) + col;
            break;
        default:
            std::cerr << "WTF you shouldn't be reaching this" << std::endl;
            return false;
    }
    int temp = tiles[otherIndex];
	tiles[otherIndex] = tiles[4 * row + col];
	tiles[4 * row + col] = temp;
    return true;
}

bool  SlidingPuzzleState::UndoMove(int move)
{
    switch(move)
    {
        case UP:
           return ApplyMove(DOWN);
        case DOWN:
           return ApplyMove(UP);
        case LEFT:
            return ApplyMove(RIGHT);
        case RIGHT:
            return ApplyMove(LEFT);
        default:
            std::cerr << "WTF you shouldn't be reaching this" << std::endl;
            return false;
    }
}

int SlidingPuzzleState::GetTileInSquare(int row, int col)
{
    if(!IsValid(row, col))
    {
        return -1;
    }
    return tiles[4 * row + col];
}

void SlidingPuzzleState::GetEmptySquare(int &row, int &col)
{
    for (row = 0; row < 3; ++row)
    {
        for (col = 0; col < 4; ++col)
        {
            if (tiles[4 * row + col] == 0)
            {
				return;
            }
        }
    }
}

void SlidingPuzzleState::Print()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if (GetTileInSquare(row, col) == 0)
				std::cout << " .";
			else
				std::cout << " " << GetTileInSquare(row, col);
		}
		std::cout << std::endl;
	}
}

SlidingPuzzleState *SlidingPuzzleState::Clone()
{
	return new SlidingPuzzleState(tiles);
}

bool SlidingPuzzleState::IsSolution()
{
    for (int i = 0; i < 12; ++i)
    {
        if (tiles[i] != i)
        {
            return false;
        }
    }
    return true;
}