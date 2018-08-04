//
// Created by sergio on 01.08.18.
//

#include <gmock/gmock.h>
#include <vector>
#include "custom_allocator.h"

using namespace testing;

TEST(Vector_Test, Vector_Test_Append_Delete_Test) {
    std::vector<int, custom_allocator<int, 2>> v = {1, 2, 3};
    //std::vector<int> v = {1, 2, 3};
    v.reserve(5);
    ASSERT_EQ(v.size(), 3);
    v.pop_back();
    ASSERT_EQ(v.size(), 2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    ASSERT_EQ(v.size(), 5);
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
   ASSERT_EQ(v.size(), 8);

    std::vector<int, custom_allocator<int, 2>> v1 = {1};
    v1.reserve(7);
    v1.push_back(2);
    ASSERT_EQ(v1.size(), 2);

    v1.pop_back();
    v1.pop_back();
    ASSERT_EQ(v1.size(), 0);
    v1.push_back(2);
    ASSERT_EQ(v1.size(), 1);
}