
#pragma once


#include "PoolList.h"
#include <stdexcept>


template<typename T, size_t init_pool_size = 1>
struct custom_allocator {

    //type definitions
    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type= ptrdiff_t;
    using size_type= size_t;


    size_t members_count{0};
    size_t add_members_count{0};
    PoolList<T> *pool_list{nullptr};

    template<typename U>
    struct rebind {
        using other = custom_allocator<U, init_pool_size>;
    };

    custom_allocator() = default;

    ~custom_allocator() = default;

    template<typename U>
    custom_allocator(const custom_allocator<U, init_pool_size> &) {


    }

    T *allocate(std::size_t n) {

        if (n != 1) std::invalid_argument("Sorry, but we could allocate only one element for time");


        ++members_count;


        if (!pool_list) {

            if (init_pool_size == 0) { pool_list = new PoolList<T>(1); }
            else { pool_list = new PoolList<T>(init_pool_size); }

        }

        pool_list->add_allocate_node_pointer_to_list(add_members_count);


        auto p = reinterpret_cast<T *>(pool_list->get_element_pointer(add_members_count));
        ++add_members_count;


        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        --members_count;


        if (!members_count) {
            if (pool_list) {
                delete pool_list;
                pool_list = nullptr;

            }
            add_members_count = 0;

        };

    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {

        p->~T();


    }
};

