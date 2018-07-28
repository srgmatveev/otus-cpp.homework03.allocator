//
// Created by sergio on 02.07.18.
//

#include <gmock/gmock.h>
#include "factorial.h"
#include "my_forward_list.h"
#include "custom_allocator.h"

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


TEST(Forward_List_Test, Forward_List_Test_Append_Delete_Test) {
    hw03::my_forward_list<int, custom_allocator<int, 2>> fwd_list = {1, 2, 3};
    int count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 3);

    fwd_list.pop_back();
    count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 2);


    fwd_list.pop_back();
    count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 1);


    fwd_list.pop_back();
    count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 0);


    fwd_list.pop_back();
    count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 0);

    fwd_list.push_back(1);
    count = 0;

    for ( auto &i : fwd_list ) { ++count; }


    ASSERT_EQ(count, 1);


    fwd_list.push_back(1);
    fwd_list.push_back(1);

    count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 3);

}


TEST(Forward_List_Test, Forward_List_Test_Zero_Allocator_size) {
    hw03::my_forward_list<int, custom_allocator<int,0>> fwd_list = {1,2,3,5,6,7,8};
    int count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 7);


}

TEST(Forward_List_Test, Forward_List_Test_Default_Allocator_size) {
    hw03::my_forward_list<int, custom_allocator<int>> fwd_list = {1,2,3,5,6,7,8};
    fwd_list.push_back(15);
    int count = 0;

    for ( auto &i : fwd_list ) { ++count; }

    ASSERT_EQ(count, 8);


}