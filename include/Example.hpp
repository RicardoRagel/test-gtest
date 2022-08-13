#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

namespace Example
{
    //! Sum x and y, store it in sum and return it.
    int sum(int x, int y, int &sum);

    //! Get the square of arg1 only if it is positive. Returns false in case arg1 is negative
    bool square_if_positive(int x, int &square);
}

#endif // EXAMPLE_HPP