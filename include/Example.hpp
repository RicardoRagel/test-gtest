#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

namespace Example
{
    //! Sum x and y, store it in sum and return it.
    int sum(int x, int y, int &sum);

    //! Get the square of arg1 only if it is positive. Returns false in case arg1 is negative
    bool square_if_positive(int x, int &square);

    //! A simple class containing 2 integers and their sum
    class Addition
    {
        public:
            Addition(int x, int y); // Constructor
            Addition(Addition &a);  // Copy constructor
            
            int get_sum();

        private:
            int m_x, m_y;   // numbers to sum
            int m_sum;      // the sum
    };
}

#endif // EXAMPLE_HPP