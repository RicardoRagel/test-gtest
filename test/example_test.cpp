#include <gtest/gtest.h>
#include "Example.hpp"

// Demonstrate some basic assertions using:
// EXPECT_*(): check one or multiple expected values. Although it fails, the TestSuit continues with the next test.
// ASSERT_*(): idem, but if it fails, this Test Suit finishes
TEST(ExampleTest, BasicAssertions)
{
  // Expect bool value true
  EXPECT_TRUE(true);
  // Expect equality.
  EXPECT_EQ( 7*6 , 42 );
  // Expect two strings to be equal.
  ASSERT_STREQ("hello", "hello");
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
}

// Demonstrate how to use a function defined in this file and how to add an failure custom message (ctest -V mandatory)
bool alwaysTrue()
{
    return false;
}
TEST(ExampleTest, UsingFunctions)
{
    EXPECT_EQ(alwaysTrue(), true) << "ERROR: alwaysTrue() function doesn't return true!!";
}

// Demonstrate how to use loops with tests
TEST(ExampleTest, IterativeTests)
{
    for(int i = 1; i<=10; i++)
    {
        // Expect arg1 is lower than arg2
        ASSERT_LT(i, 5) << "Error at i = " << i;
    }
}

// Demonstrate how to use a function defined in a linked library
TEST(ExampleTest, TestSum)
{
    int x = std::rand();
    int y = std::rand();
    int expected_sum = x + y;
    int result_sum;
    // Check function returns the expected value
    EXPECT_EQ(expected_sum, Example::sum(x, y, result_sum));
    // Check function stored the expected value
    EXPECT_EQ(expected_sum, result_sum);
}
TEST(ExampleTest, TestSquare)
{
    // Check function returns the expected value for a positive input 
    int x_pos = 5;
    int expected_square = x_pos * x_pos;
    int result_square;
    EXPECT_TRUE(Example::square_if_positive(x_pos, result_square));
    EXPECT_EQ(expected_square, result_square);

    // Check function returns the expected value for a negative input 
    int x_neg = -7;
    EXPECT_FALSE(Example::square_if_positive(x_neg, result_square));
}

// Demonstrate how to encapsulate data for our tests using a "::testing::Test" derived class
// and how to override the "SetUp" and "TearDown" (closing function) to manipulate this data
// This is useful when our test are using/doing always the same kind of things, so we don't
// have to repeat it in everyone.
class ExampleTestClass : public ::testing::Test
{
    // Members must be accessible from derived classes of GTest
    protected:

        // Some example data member that needs to be initialized and deleted
        int * x;

        // "virtual" to be able to override it from derived classes 
        // and "override" to make sure in compile-time we 
        // are not creating a new function, we are overriding the
        // the base class onr (::testing::Test).
        virtual void SetUp() override
        {
            std::cout << "Setting up!" << std::endl;
            x = new int(42);
        }   

        virtual void TearDown() override
        {
            std::cout << "Tearing down!" << std::endl;
            delete x;
        }

        // Some other functions to be used
        int getX()
        {
            return *x;
        }
        void setX(int value)
        {
            *x = value;
        }
};

TEST_F(ExampleTestClass, TestSquare)
{
    // Check function returns the expected value for a positive input 
    setX(+std::rand());
    int expected_square = getX() * getX();
    int result_square;
    EXPECT_TRUE(Example::square_if_positive(getX(), result_square));
    EXPECT_EQ(expected_square, result_square);

    // Check function returns the expected value for a negative input 
    setX(-std::rand());
    EXPECT_FALSE(Example::square_if_positive(getX(), result_square));
}