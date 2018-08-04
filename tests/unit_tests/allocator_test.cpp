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
    allocator->deallocate(p,10);

    if(allocator) delete allocator;


    //ASSERT_THAT(factorial<int>(0), Eq(1));



}
