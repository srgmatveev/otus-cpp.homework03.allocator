
#pragma once
//#define DEBUG 1

template<typename T, size_t init_pool_size>
struct custom_allocator {

    //type definitions
    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type= ptrdiff_t;
    using size_type= size_t;

    void* pool{nullptr};
    size_t members_count{0};



    template<typename U>
    struct rebind {
        using other = custom_allocator<U,init_pool_size>;
    };

    custom_allocator() = default;

    ~custom_allocator() = default;

    template<typename U>
    custom_allocator(const custom_allocator<U, init_pool_size> &) {

    }

    T *allocate(std::size_t n) {

#ifdef DEBUG
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#endif
        auto before_members_increment = members_count;

        for(auto i=0; i<n; ++i) {++members_count;}

        if(!pool) {

            pool = std::malloc(sizeof(T) * init_pool_size);
            if (!pool)
                throw std::bad_alloc();
        }
#ifdef DEBUG
        std::cout<<"members_count ="<<members_count<<std::endl;
#endif

        auto p = reinterpret_cast<T *>(pool) + before_members_increment;

        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
#ifdef DEBUG
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#endif
        if(!members_count) std::free(pool);

    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifdef DEBUG
        std::cout << "construct" << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        --members_count;
#ifdef DEBUG
        std::cout << "destroy" << std::endl;
        std::cout<<"members_count ="<<members_count<<std::endl;
#endif
        p->~T();


    }
};

