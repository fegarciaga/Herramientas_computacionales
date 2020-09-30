#include "factorial.h"
#include "gtest/gtest.h"
namespace {
    // Tests factorial of negative numbers.
    TEST(FactorialTest, Negative) {
        // This test is named "Negative", and belongs to the "FactorialTest"
        // test case.
        EXPECT_EQ(0, factorial(-5));
        EXPECT_EQ(0, factorial(-1));
    }
    // Tests factorial of 0.
    TEST(FactorialTest, Zero) {
        EXPECT_EQ(1, factorial(0));
    }

// Tests factorial of positive numbers.
    TEST(FactorialTest, Positive) {
        EXPECT_EQ(1, factorial(1));
        EXPECT_EQ(2, factorial(2));
        EXPECT_EQ(6, factorial(3));
        EXPECT_EQ(40320, factorial(8));
    }
}
