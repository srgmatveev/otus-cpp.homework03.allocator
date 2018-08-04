//
// Created by sergio on 26.07.18.
//

#pragma once

#include <iostream>

#include <cstddef>
#include <cstdlib>
#include <new>
#include <cmath>

struct pool_node {
private:
    size_t pool_size{0};
public:
    void *pool{nullptr};
    pool_node *next{nullptr};

    pool_node() = delete;

    pool_node(size_t size) : pool_size{size}, next{nullptr} {
           malloc_node(pool_size);
    }

    ~pool_node() {
        if (pool) std::free(pool);
    }


private:
    void malloc_node(const size_t &_sz) {

        if (!pool) pool = std::malloc(_sz);
        if (!pool) std::bad_alloc();
    }
};

template<typename U>
class PoolList {
    pool_node *head;
public:

    PoolList() : head{nullptr}{}

    size_t get_size() {
        size_t count = 0;
        auto tmp = head;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }

        return count;
    }

    void* get_node_adrres_by_node_number(const size_t &index) {

        if (get_size() < index + 1) return nullptr;

        if(get_size()==1) {
            return head->pool;
        }

        auto *tmp = head;
        for ( auto i = 0; i < index; ++i ) {
            tmp = tmp->next;}

        return tmp->pool;
    }


    U* get_element_pointer(const size_t& index, const size_t& size_of_pool_node){

        U* p = nullptr;
        size_t pool_node_number = std::floor(index / size_of_pool_node);
        size_t offset_from_node = index - pool_node_number * size_of_pool_node;
        p = reinterpret_cast<U *> (get_node_adrres_by_node_number(pool_node_number)) + offset_from_node;

        return p;
    }

    void add_allocate_node_pointer_to_list(const size_t &index, const size_t& size_of_pool_node) {

        size_t pool_node_number = index / size_of_pool_node;

        if (get_size() < pool_node_number + 1) {
            for ( auto i = get_size(); i < (pool_node_number + 1); ++i ) {
                _add_node(size_of_pool_node);
            }
        }

    }

    void* add_allocate_node_pointer_to_list_multi(const size_t &index, const size_t& size_of_pool_node) {
        pool_node* p_n = _add_node(size_of_pool_node);
        if(p_n) return p_n->pool;
        return nullptr;
    }

    pool_node *get_last_node() {
        auto tmp = head;
        auto tmp1 = tmp;
        while (tmp) {
            tmp1 = tmp;
            tmp = tmp->next;
        }
        return tmp1;
    }

    ~PoolList();

private:
    pool_node* _add_node(const size_t& size_of_pool_node) {

        pool_node *tmp = new pool_node(size_of_pool_node*sizeof(U));

        if (!head) {
            head = tmp;
            tmp->next= nullptr;
        } else {
            get_last_node()->next = tmp;
        }

        return tmp;
    }

};


template<typename U>
PoolList<U>::~PoolList() {
    while (head) {
        pool_node *temp = head->next;
        delete head;
        head = temp;
    }
}