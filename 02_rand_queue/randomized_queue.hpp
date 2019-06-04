#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>


template <typename T>
class randomized_queue {
private:

    std::vector<T> r_queue;

    size_t _size;

    std::mt19937 random_generator_;

    class iterator {
    private:
        size_t pos;

        randomized_queue* queue_ref;

        std::vector<T>permutation;

        typename std::vector<T>::iterator it;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using ref = T&;
        using pointer = T*;

        explicit iterator(size_t pos, randomized_queue* queue_ref) : pos(pos), queue_ref(queue_ref)
        {
            permutation = queue_ref->r_queue;
            std::shuffle(permutation.begin(), permutation.end(), queue_ref->random_generator_);
            if (pos == 0)
                it = permutation.begin();
            else
                it = permutation.end();
        };

        iterator(const iterator& tmp_iter) {
            pos = tmp_iter.pos;
            queue_ref = tmp_iter.queue_ref;
            permutation.clear();
            permutation = tmp_iter.permutation;
            it = tmp_iter.it;
        }

        iterator & operator=(const iterator & tmp_iter) {
            if (this != &tmp_iter) {
                pos = tmp_iter.pos;
                queue_ref = tmp_iter.queue_ref;
                permutation.clear();
                permutation = tmp_iter.permutation;
                it = tmp_iter.it;
            }
            return *this;
        }

        ref operator*() const
        {
            return *it;
        }

        bool operator==(iterator const& iterator) const
        {
            return (pos == iterator.pos && queue_ref == iterator.queue_ref);
        }

        bool operator!=(iterator const& iterator) const
        {
            return (pos != iterator.pos || queue_ref != iterator.queue_ref);
        }

        iterator& operator++()
        {
            pos++;
            it++;
            return *this;
        }

        iterator operator++(int)
        {
            auto tmp = *this;
            ++pos;
            ++it;
            return tmp;
        }

        iterator& operator--()
        {
            pos--;
            it--;
            return *this;
        }

        iterator operator--(int)
        {
            auto tmp = *this;
            --pos;
            --it;
            return tmp;
        }
    };

    size_t get_random_pos()
    {
        std::uniform_int_distribution<size_t> uid(0, _size - 1);
        return uid(random_generator_);
    };

public:

    randomized_queue()
    {
        std::random_device device;
        random_generator_.seed(device());
        _size = 0;
    }


    randomized_queue(const randomized_queue& tmp_rq) {
        _size = tmp_rq._size;
        r_queue.clear();
        r_queue = tmp_rq.r_queue;
        random_generator_ = tmp_rq.random_generator_;
    }

    randomized_queue & operator=(const randomized_queue & tmp_rq) {
        if (this != &tmp_rq) {
            _size = tmp_rq._size;
            r_queue.clear();
            r_queue = tmp_rq.r_queue;
            random_generator_ = tmp_rq.random_generator_;
        }
        return *this;
    }

    iterator begin()
    {
        return iterator(0, this);
    };

    iterator end()
    {
        return iterator(size(), this);
    };

    bool empty() const
    {
        return _size == 0;
    }

    size_t size() const
    {
        return _size;
    }

    T sample() const
    {
        return r_queue[get_random_pos()];
    }

    T dequeue()
    {
        std::swap(r_queue[size() - 1], r_queue[get_random_pos()]);
        T tmp = r_queue.back();
        r_queue.pop_back();
        _size--;
        return tmp;
    }

    void enqueue(T& added)
    {
        r_queue.push_back(added);
        _size++;
    }
};

