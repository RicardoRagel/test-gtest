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

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to encapsulate data for our tests using test fixture object, that simply are 
// "::testing::Test" derived class where we can define the necessary variables and functions for our tests,
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
// more information: https://google.github.io/googletest/advanced.html#sharing-resources-between-tests-in-the-same-test-suite
// for example, it is important to know that each test uses a new test fixture object, but we can use SetUpTestSuite if we need
// that some of these variables are shared between these objects (basically, statics).

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use "Explicit Success and Failure"
TEST(ExplicitSuccessAndFailure, ExplicitSuccess)
{
    int8_t select = 2;
    switch(select)
    {
        case 1:
            std::cout << "1" << std::endl;
            SUCCEED();
            break;
        case 2:
            std::cout << "2" << std::endl;
            SUCCEED();
            break;
        default:
            std::cout << "default" << std::endl;
            FAIL();
    }
}
TEST(ExplicitSuccessAndFailure, ExplicitFailure)
{
    int8_t select = 45;
    switch(select)
    {
        case 1:
            std::cout << "1" << std::endl;
            SUCCEED();
            break;
        case 2:
            std::cout << "2" << std::endl;
            SUCCEED();
            break;
        default:
            std::cout << "default" << std::endl;
            FAIL() << "Non-expected Option";
    }
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use "Expected Predicate Assertions"
bool allPositive(int a, int b, int c)
{
    return ( a>=0 ) && ( b>=0 ) && ( c>=0 )? true : false;
}
TEST(ExpectedPredicate, TestOK)
{
    // the "3" means 3 arguments
    EXPECT_PRED3(allPositive, 33, 69, 72);
}
TEST(ExpectedPredicate, TestFAIL)
{
    // the "3" means 3 arguments
    EXPECT_PRED3(allPositive, 33, -69, 72);
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to create our own Assertion
// We simply need to create a function that returns a testing::AssertionResult object,
// that can be OK (testing::AssertionSuccess()) or FAIL (testing::AssertionFailure())
testing::AssertionResult testCopyAdditionObjects(Example::Addition &add)
{
    Example::Addition new_add = add; 

    if(new_add.get_sum() == add.get_sum())
    {
        return testing::AssertionSuccess();
    }
    else
    {
        return testing::AssertionFailure() << "Copy constructor fails, sum's are not equals";
    }
}
TEST(UsingCustomAssertion, TestAdditionCopyConstructor)
{
    Example::Addition add(std::rand(), std::rand());

    EXPECT_TRUE(testCopyAdditionObjects(add));
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to compare floating numbers where an epsilon difference is acceptable
TEST(FloatingNumberComparision, TestExpectedEqual)
{
    double num1     = 33.33334;
    double num2     = 33.3334;
    
    EXPECT_EQ   (num1, num2);
}
TEST(FloatingNumberComparision, TestExpectedNear)
{
    double num1     = 33.33334;
    double num2     = 33.3334;
    double epsilon  =  0.0001;
    EXPECT_NEAR (num1, num2, epsilon);
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use the built-in library of "Matchers" to execute other generic tests
// see https://google.github.io/googletest/reference/matchers.html#generic-comparison
#include "gmock/gmock.h"
TEST(Matchers, TestStringMatchers)
{
    std::string str = "This is a test";
    EXPECT_THAT(str, ::testing::StartsWith("This is"));
    EXPECT_THAT(str, ::testing::HasSubstr("test"));
}
TEST(Matchers, TestPointerMatchers)
{
    int* ptr = NULL;
    EXPECT_THAT(ptr, ::testing::NotNull());
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use Death Tests to check if a piece of code (that can be simply a function)
// exit correctly or not. 
// Note that the piece of code under test can be a compound statement
// Note that the last argument can be a Matcher or simply a regex expresion to check the expected error message (std::cerr)
TEST(DeathTests, TestExitCorrectly)
{
    EXPECT_EXIT
    (
        {
            int positive_value = 3;
            Example::finish_positively(positive_value);
        },
        testing::ExitedWithCode(0),
        ""
    );
}
TEST(DeathTests, TestExitWithError)
{
    EXPECT_EXIT
    (
        {
            int positive_value = -3;
            Example::finish_positively(positive_value);
        },
        testing::ExitedWithCode(0),
        ""
    );
}
TEST(DeathTests, TestDeath)
{
    EXPECT_DEATH
    (
        {
            int positive_value = -3;
            Example::finish_positively(positive_value);
        },
        ""
    );
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use Traces to make easier knowing what/where is failing our test
// In this case, let's create a test sub-routine, and call it from our test from several places
void test_multiple_square_if_positive(int n)
{
    int garbage;
    EXPECT_TRUE( Example::square_if_positive(n-1, garbage) ); 
    EXPECT_TRUE( Example::square_if_positive(n-2, garbage) );
}
TEST(TracingTests, TestScopeTrace)
{   
    // Let's create a scope where failures will include the following trace
    {
        SCOPED_TRACE("First part of the TestScopeTrace");
        test_multiple_square_if_positive(2);
    }
    // Let's create another scope where failures will include the following trace
    {
        SCOPED_TRACE("Second part of the TestScopeTrace");
        test_multiple_square_if_positive(1);
    }
}

//------------------------------------------------------------------------------------------------------------------
// A warning about the use of subroutines and failures assertion
// When an ASSERTION test fails within a subroutine, this subroutines ends, but it doesn't mean that the 
// test has finished, it will continue from that subroutine calling next line.
void subroutine()
{
    ASSERT_TRUE(false) << "Fail 1 inside the subroutine"; // It will fail

    // So this next line will not be executed
}
TEST(PropagatingFailures, TestSubroutine1)
{
    subroutine();

    ASSERT_TRUE(false) << "Fail 2 outside the subroutine"; // It will be executed (and fail) although we could think
                                                           // it would not be executed due to subroutine() failed
}
// To avoid it (i.e. if subroutine fails the test ends up):
TEST(PropagatingFailures, TestSubroutine2)
{
    subroutine();

    if(HasFatalFailure()) return;

    ASSERT_TRUE(false) << "Fail 2 outside the subroutine"; // It will be executed (and fail) although we could think
                                                           // it would not be executed due to subroutine() failed
}

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to write Value-Parametrized Tests
// This is useful when we want to repeat tests with different inputs all at once

// First, we need to define a fixture class, that derived from testing::Test, but in this case using a derived one:
// testing::TestWithParamInterface<T>, that basically is the same but allowing us to introduce a parameter of type T.
// In this case, we want to test that a series of input names are in a list that we have in our Example library.
class ParametrizedTestClass : public testing::TestWithParam<const char *>
{
    public:
        bool isValidName()
        {
            // To access the param, we can use the GetParam() member of TestWithParam class
            const char * param = GetParam();
            bool result = false;
            for(auto name : Example::valid_names)
            {
                if(strcmp(name.c_str(), param) == 0)
                {
                    result = true;
                    break;
                }
            }

            return result;
        }
};

// Then, we use the TEST_P ("pattern" or "parametrized") to create the type of test that we are interested.
// Note that we are passing the previous fixture class and using its method directly.
TEST_P(ParametrizedTestClass, TestValidName)
{
    // Here we can also use GetParam(), but in this case we are already doing it in the class
    EXPECT_TRUE(isValidName());
}

INSTANTIATE_TEST_SUITE_P(MultipleTests,
                         ParametrizedTestClass,
                         testing::Values("Ricardo", "Paula", "Miguel"));

//------------------------------------------------------------------------------------------------------------------
// Demonstrate how to use Typed Tests
// They allow to repeat the same test logic over a list of types. 
// You only need to write the test logic once, although you must know the type list when writing typed tests.

// First, it is necessary to define a fixture class, templatized, so we can use it with all our types
template <typename T>
class TemplatizedTest : public testing::Test 
{
    public:
        void addElement(T element)
        {
            m_list.push_back(element);
        }
        size_t getSize()
        {
            return m_list.size();
        }

    private:
        std::vector<T> m_list;
};

// Then, we also need to define our types list
using MyTypes = ::testing::Types<char, int, unsigned int>;

// And associate it with our templatized fixture class
TYPED_TEST_SUITE(TemplatizedTest, MyTypes);

// Finally, creates the test using the fixture class (that already has the types associated)
TYPED_TEST(TemplatizedTest, CheckAddElements) 
{
    // Inside a test, refer to the special name TypeParam to get the type
    // parameter.  
    TypeParam n;

    // Since we are inside a derived class template, C++ requires
    // us to visit the members of TemplatizedTest via 'this'.
    this->addElement(n);
    this->addElement(n);
    this->addElement(n);

    // And test
    EXPECT_EQ(this->getSize(), 3);
}