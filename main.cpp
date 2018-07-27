#include <iostream>
#include <map>
#include <algorithm>

#include "my_forward_list.h"
#include "custom_allocator.h"
#include "factorial.h"

static const size_t INIT_POOL_SIZE_OF_ALLOCATOR = 10;


int main(int argc, char *argv[]) {


    auto make_pair_from_factorial = [i = 0]()mutable  throw() -> std::pair<int, int> {
        int key = i;
        int value = factorial(i);
        ++i;
        return std::make_pair(key, value);
    };


    std::map<int, int> m1;
    std::generate_n(std::inserter(m1, m1.begin()), INIT_POOL_SIZE_OF_ALLOCATOR, make_pair_from_factorial);

    std::map<int, int, std::less<int>, custom_allocator<int, INIT_POOL_SIZE_OF_ALLOCATOR>> m2;
    std::generate_n(std::inserter(m2, m2.begin()), INIT_POOL_SIZE_OF_ALLOCATOR, make_pair_from_factorial);


    for ( auto elem : m2 ) {
        std::cout << elem.first << " " << elem.second << "\n";
    }


    hw03::my_forward_list<int> fwd_list1{};
    std::generate_n(std::front_inserter(fwd_list1), INIT_POOL_SIZE_OF_ALLOCATOR,
                    [i = INIT_POOL_SIZE_OF_ALLOCATOR]()mutable { return --i; });

    hw03::my_forward_list<int, custom_allocator<int, INIT_POOL_SIZE_OF_ALLOCATOR>> fwd_list2{};
    std::generate_n(std::back_inserter(fwd_list2), INIT_POOL_SIZE_OF_ALLOCATOR, [i = 0]()mutable { return i++; });


    for ( auto &elem : fwd_list2 ) {
        std::cout << elem << std::endl;
    }


    return 0;

}