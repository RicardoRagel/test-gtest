#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <stdlib.h> // exit()
#include <vector>
#include <string>

namespace Example
{
    // Sum x and y, store it in sum and return it.
    int sum(int x, int y, int &sum);

    // Get the square of arg1 only if it is positive. Returns false in case arg1 is negative
    bool square_if_positive(int x, int &square);

    // A simple class containing 2 integers and their sum
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

    // A function that makes the program exit correctly (value 0) always that it receives a positive value
    // Otherwise, it makes the program exit wrongly (value non-zero), that means it died
    void finish_positively(int positive_num);

    // A simple list of valid names
    static std::vector<std::string> valid_names{"Ricardo", "Herminia", "Manuel", "Paula"};
}

#endif // EXAMPLE_HPP