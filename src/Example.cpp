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

    Addition::Addition(int x, int y)
    {
        m_x = x;
        m_y = y;
        m_sum = m_x + m_y;
    }

    Addition::Addition(Addition &a)
    {
        m_x = a.m_x;
        m_y = a.m_y;
        m_sum = a.m_sum;
    }

    int Addition::get_sum()
    {
        return m_sum;
    }

    void finish_positively(int positive_num)
    {
        if(positive_num >=0)
        {
            // Exit successfully
            exit(0);
        }
        else
        {
            exit(1);
        }
    }
}