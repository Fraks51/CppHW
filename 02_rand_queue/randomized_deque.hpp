#include <list>
#include <iostream>

template <typename T> class deque
{
private:
    size_t _size;
    std::list<T> _deque;
public:
    typedef typename std::list<T>::iterator iterator;

    typename std::list<T>::iterator begin()
    {
        return _deque.begin();
    };

    typename std::list<T>::iterator end()
    {
        return _deque.end();
    };

    deque ()
    {
        _size = 0;
    }

    deque (const deque& tmp_deq)
    {
        _size = tmp_deq._size;
        _deque.clear();
        _deque = tmp_deq._deque;
    }

    deque & operator=(const deque & tmp_deq){
        if (this != &tmp_deq)
        {
            _size = tmp_deq._size;
            _deque.clear();
            _deque = tmp_deq._deque;
        }
        return *this;
    }

    bool empty()
    {
        return _size == 0;
    }

    size_t size()
    {
        return _size;
    }

    void push_back(T& added)
    {
        _deque.push_back(added);
        _size++;
    }

    void push_front(T& added)
    {
        _deque.push_front(added);
        _size++;
    }

    T front() const
    {
        return _deque.front();
    }

    T back() const
    {
        return _deque.back();
    }

    void pop_front() {
        _size--;
        _deque.pop_front();
    }

    void pop_back() {
        _size--;
        _deque.pop_back();
    }
};