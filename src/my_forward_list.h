// <my_forward_list.h> -*- C++ -*-


/** @file src/my_forward_list.h
 *  This is an header file for homrwork03::allocator, included by other library headers.
 */

#pragma once

#include <cstddef>


namespace hw03 {

/** @brief  A helper basic node class for my_forward_list.
 *          This is just a linked list with nothing inside it.
 */
    struct _Fwd_list_node_base {
        _Fwd_list_node_base() = default;

        _Fwd_list_node_base *next{nullptr};
    };


    template<typename _Tp>
    struct _Fwd_list_node
            : public _Fwd_list_node_base {
        _Fwd_list_node() = default;

        _Fwd_list_node(const _Tp &value) : value{value}, _Fwd_list_node_base{} {};
        _Tp value;


    };


    template<typename _Tp>
    struct _Fwd_list_iterator {
        typedef _Fwd_list_iterator<_Tp> _Self;
        typedef _Fwd_list_node<_Tp> _Node;

        typedef _Tp value_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
        typedef ptrdiff_t difference_type;
        typedef std::forward_iterator_tag iterator_category;

        _Fwd_list_iterator() noexcept
                : _M_node() {}

        explicit
        _Fwd_list_iterator(_Fwd_list_node_base *__n) noexcept
                : _M_node(__n) {}

        reference
        operator*() const noexcept { return static_cast<_Node *>(this->_M_node)->value; }

        pointer
        operator->() const noexcept { return &static_cast<_Node *>(this->_M_node)->value; }

        _Self &
        operator++() noexcept {
            _M_node = _M_node->next;
            return *this;
        }

        _Self
        operator++(int) noexcept {
            _Self __tmp(*this);
            _M_node = _M_node->next;
            return __tmp;
        }

        bool
        operator==(const _Self &__x) const noexcept { return _M_node == __x._M_node; }

        bool
        operator!=(const _Self &__x) const noexcept { return _M_node != __x._M_node; }

        _Self
        _M_next() const noexcept {
            if (_M_node)
                return _Fwd_list_iterator(_M_node->next);
            else
                return _Fwd_list_iterator(0);
        }

        _Fwd_list_node_base *_M_node;
    };


    template<typename _Tp>
    struct _Fwd_list_const_iterator {
        typedef _Fwd_list_const_iterator<_Tp> _Self;
        typedef const _Fwd_list_node<_Tp> _Node;
        typedef _Fwd_list_iterator<_Tp> iterator;

        typedef _Tp value_type;
        typedef const _Tp *pointer;
        typedef const _Tp &reference;
        typedef ptrdiff_t difference_type;
        typedef std::forward_iterator_tag iterator_category;

        _Fwd_list_const_iterator() noexcept
                : _M_node() {}

        explicit
        _Fwd_list_const_iterator(const _Fwd_list_node_base *__n)  noexcept
                : _M_node(__n) {}

        _Fwd_list_const_iterator(const iterator &__iter) noexcept
                : _M_node(__iter._M_node) {}

        reference
        operator*() const noexcept { return static_cast<_Node *>(this->_M_node)->value; }

        pointer
        operator->() const noexcept { return &static_cast<_Node *>(this->_M_node)->value; }

        _Self &
        operator++() noexcept {
            _M_node = _M_node->next;
            return *this;
        }

        _Self
        operator++(int) noexcept {
            _Self __tmp(*this);
            _M_node = _M_node->next;
            return __tmp;
        }

        bool
        operator==(const _Self &__x) const noexcept { return _M_node == __x._M_node; }

        bool
        operator!=(const _Self &__x) const noexcept { return _M_node != __x._M_node; }

        _Self
        _M_next() const noexcept {
            if (this->_M_node)
                return _Fwd_list_const_iterator(_M_node->next);
            else
                return _Fwd_list_const_iterator(0);
        }

        const _Fwd_list_node_base *_M_node;
    };

    template<class Type,
            class Allocator = std::allocator<Type>>
    class my_forward_list {

    public:
        typedef Allocator allocator_type;
        typedef typename Allocator::value_type value_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::difference_type difference_type;
        typedef typename Allocator::size_type size_type;

        typedef _Fwd_list_iterator<Type> iterator;
        typedef _Fwd_list_const_iterator<Type> const_iterator;

        typedef typename Allocator::template rebind<_Fwd_list_node<Type> >::other _Node_Allocator;

        typedef _Fwd_list_node<Type> _Node;
        typedef _Fwd_list_node_base _Node_base;

        my_forward_list() = default;

        explicit my_forward_list(const Allocator &al) : Node_Alloc{al}, head{} {

        }


        my_forward_list(
                std::initializer_list<Type> IList, const Allocator &al = Allocator())
                : Node_Alloc{al}, head{} {
            _M_range_initialize(IList.begin(), IList.end());

        }



        iterator insert_after(const_iterator __pos, const Type &__val) {
            return iterator(this->_M_insert_after(__pos, __val));
        }


        void push_back(const Type &value) {
            auto last = this->before_begin();

            while (std::next(last) != this->end()) {
                ++last;

            }
            insert_after(last, value);
        }




        void
        push_front(Type&& __val)
        { this->_M_insert_after(cbefore_begin(), std::move(__val)); }

        void
        pop_front()
        { this->_M_erase_after(&this->head); }

        void
        clear() noexcept { this->_M_erase_after(&this->head, 0); }

        ~my_forward_list(){clear();}

        iterator
        before_begin() noexcept { return iterator(&this->head); }


        const_iterator
        before_begin() const noexcept { return const_iterator(&this->head); }


        iterator
        begin() noexcept { return iterator(this->head.next); }


        const_iterator
        begin() const noexcept { return const_iterator(this->head.next); }


        iterator
        end() noexcept { return iterator(nullptr); }


        const_iterator
        end() const noexcept { return const_iterator(nullptr); }


        const_iterator
        cbegin() const noexcept { return const_iterator(this->head.next); }


        const_iterator
        cbefore_begin() const noexcept { return const_iterator(&this->head); }


        const_iterator
        cend() const noexcept { return const_iterator(nullptr); }


    private:
        _Node head;
        _Node_Allocator Node_Alloc;


    private:


        template<typename _InputIterator>
        void _M_range_initialize(_InputIterator __first, _InputIterator __last) {
            _Node_base *__to = &this->head;
            for ( ; __first != __last; ++__first ) {
                __to->next = this->_M_create_node(*__first);
                __to = __to->next;
            }
        }


        template<typename... _Args>
        _Node *
        _M_create_node(_Args &&... __args) {
            _Node *__node = Node_Alloc.allocate(1);

            Node_Alloc.construct(__node, std::forward<_Args>(__args)...);

            return __node;
        }


        template<typename... _Args>
        _Fwd_list_node_base *
        _M_insert_after(const_iterator __pos, _Args &&... __args) {
            _Fwd_list_node_base *__to
                    = const_cast<_Fwd_list_node_base *>(__pos._M_node);
            _Node *__thing = _M_create_node(std::forward<_Args>(__args)...);
            __thing->next = __to->next;
            __to->next = __thing;
            return __to->next;
        }


        _Fwd_list_node_base *
        _M_erase_after(_Fwd_list_node_base *__pos) {
            _Node *__curr = static_cast<_Node *>(__pos->next);
            __pos->next = __curr->next;
            Node_Alloc.destroy(__curr);
            Node_Alloc.deallocate(__curr, 1);

            return __pos->next;
        }


        _Fwd_list_node_base*
              _M_erase_after(_Fwd_list_node_base* __pos,
                       _Fwd_list_node_base* __last)
        {
            _Node* __curr = static_cast<_Node*>(__pos->next);
            while (__curr != __last)
            {
                _Node* __temp = __curr;
                __curr = static_cast<_Node*>(__curr->next);
                Node_Alloc.destroy(__temp);
                Node_Alloc.deallocate(__temp, 1);

            }
            __pos->next = __last;
            return __last;
        }


    };



}