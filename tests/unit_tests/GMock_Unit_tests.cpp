//
// Created by sergio on 02.07.18.
//

#include <gmock/gmock.h>
#include "my_forward_list.h"
#include "custom_allocator.h"

using namespace testing;

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