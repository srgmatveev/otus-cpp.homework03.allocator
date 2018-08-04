//
// Created by sergio on 04.08.18.
//


#include <gmock/gmock.h>
#include "factorial.h"

using namespace testing;

TEST(Factorial_Test, Factorial_correct_values) {

    ASSERT_THAT(factorial<int>(0), Eq(1));
    ASSERT_THAT(factorial<int>(1), Eq(1));
    ASSERT_THAT(factorial<int>(2), Eq(2));
    ASSERT_THAT(factorial<int>(3), Eq(6));
    ASSERT_THAT(factorial<int>(4), Eq(24));
    ASSERT_THAT(factorial<int>(5), Eq(120));
    ASSERT_THAT(factorial<int>(6), Eq(720));
    ASSERT_THAT(factorial<int>(7), Eq(5040));
    ASSERT_THAT(factorial<int>(8), Eq(40320));
    ASSERT_THAT(factorial<int>(9), Eq(362880));
}
