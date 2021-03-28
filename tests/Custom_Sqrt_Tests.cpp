#include <gtest/gtest.h>
#include <utilities.hpp>

class Custom_Sqrt_Tests : public ::testing::Test {};

TEST_F(Custom_Sqrt_Tests, Value_More_Or_Equal_One) {
	ASSERT_TRUE(is_equally(custom_sqrt(4), 2));
	ASSERT_TRUE(is_equally(custom_sqrt(164.8), 12.8374452287));
	ASSERT_TRUE(is_equally(custom_sqrt(1), 1));
	ASSERT_TRUE(is_equally(custom_sqrt(245634.123452456), 495.6148943005));
}

TEST_F(Custom_Sqrt_Tests, Value_Less_Than_One) {
	ASSERT_TRUE(is_equally(custom_sqrt(0.2), 0.4472135955));
	ASSERT_TRUE(is_equally(custom_sqrt(0.8), 0.894427191));
	ASSERT_TRUE(is_equally(custom_sqrt(0), 0));
	ASSERT_TRUE(is_equally(custom_sqrt(-0), 0));
	ASSERT_TRUE(is_equally(custom_sqrt(0.99999), 0.999995));
}
