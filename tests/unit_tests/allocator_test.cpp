//
// Created by sergio on 04.08.18.
//

#include <gmock/gmock.h>
#include "custom_allocator.h"

using namespace testing;

TEST(Allocator_Test, Allocator_Test_Alloc_create) {

    custom_allocator<int, 2 , true>* allocator = new custom_allocator<int,2,true>();

    int* p = allocator->allocate(10);
    allocator->members_count=10;
    ASSERT_EQ(allocator->pool_list->get_size(), 1);
    allocator->deallocate(p,10);

    if(allocator) delete allocator;

    custom_allocator<int, 2 , true>* allocator1 = new custom_allocator<int,2,true>();
    p = allocator->allocate(1);
    int* p1 = allocator->allocate(3);
    ASSERT_EQ(allocator->pool_list->get_size(), 2);
    allocator->deallocate(p,5);
    allocator->deallocate(p1,6);




}
