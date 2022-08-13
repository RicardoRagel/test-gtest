#include "Example.hpp"

namespace Example
{
    int sum(int x, int y, int &sum)
    {
        sum = x + y;
        
        return sum;
    }

    bool square_if_positive(int x, int &square)
    {
        bool result = false;
        
        if(x >= 0)
        {
            square = x * x;
            result = true;
        }

        return result;
    }
}