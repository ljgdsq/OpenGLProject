#pragma once
struct Size
{
    int x;
    int y;
    Size()
    {
        this->x = 0;
        this->y = 0;
    }
    Size(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
};