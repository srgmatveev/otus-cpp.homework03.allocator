#pragma once

#include "PoolList.h"
#include <stdexcept>
#include <cstring>

template<typename T, size_t init_pool_size = 1, bool multi_vals = false>
struct custom_allocator {

    //type definitions
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type= ptrdiff_t;
    using size_type= size_t;

    bool is_vector{false};
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

        if (n == 0) return nullptr;
        T *p = nullptr;
        if (n == 1 and (is_vector == false or multi_vals == false)) {
            ++members_count;
            size_t p_size = 0;
            if (init_pool_size == 0) { p_size = 1; }
            else { p_size = init_pool_size; }
            if (!pool_list) pool_list = new PoolList<T>();


            pool_list->add_allocate_node_pointer_to_list(add_members_count, p_size);

            p = reinterpret_cast<T *>(pool_list->get_element_pointer(add_members_count, p_size));
            ++add_members_count;

        } else if (!multi_vals) {
            is_vector = true;
            p = reinterpret_cast<T *>(std::malloc(n * sizeof(T)));
            if (pool_list) {
                std::memcpy(p, pool_list, sizeof(T));
                delete pool_list;
                pool_list = nullptr;
                members_count = 0;
                add_members_count = 0;
            }

        } else {

            for ( auto i = 0; i < n; ++i ) ++members_count;
            if (!pool_list) pool_list = new PoolList<T>();
            p = reinterpret_cast<T *>(pool_list->add_allocate_node_pointer_to_list_multi(add_members_count, n));
            for ( auto i = 0; i < n; ++i ) ++add_members_count;
        }

        if (!p)
            throw std::bad_alloc();
        return p;
    }

    void deallocate(T *p, std::size_t n) {
        if (is_vector) {
            std::free(p);
        } else {
            for ( int i = n; i > 0; --i ) --members_count;
            if (members_count < 0) members_count = 0;
            if (!members_count) {
                if (pool_list) {
                    delete pool_list;
                    pool_list = nullptr;
                }
                add_members_count = 0;
            }
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {

        p->~T();
    }
};

