#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <array>
#include <string>
#include <ostream>

namespace my
{
template <typename ValueT>
class vector
{
  public:
    vector(size_t n = 0, ValueT val = ValueT()) : size_(n), capacity_(n)
    {
        arr_ = static_cast<ValueT *>(malloc(n * sizeof(ValueT)));
        for (auto i = 0; i < n; i++)
        {
            new (arr_ + i) ValueT(val);
        }
    }

    ~vector()
    {
        for (auto i = 0; i < size_; i++)
        {
            arr_[i].~ValueT();
        }
        std::free(arr_);
    }

    vector(vector &&vec) : vector()
    {
        swap(*this, vec);
    }

    vector(vector const &vec)
    {
        size_ = vec.size_;
        capacity_ = vec.capacity_;
        arr_ = static_cast<ValueT *>(malloc(capacity_ * sizeof(ValueT)));
        for (auto i = 0; i < size_; i++)
        {
            new (arr_ + i) ValueT(vec.arr_[i]);
        }
    }

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    void clear()
    {
        for (auto i = 0; i < size_; i++)
        {
            arr_[i].~ValueT();
        }
        size_ = 0;
    }

    void reserve(size_t new_capacity)
    {
        if (new_capacity >= size_)
        {
            capacity_ = new_capacity;
        }
        ValueT *foo = static_cast<ValueT *>(malloc(new_capacity * sizeof(ValueT)));
        for (auto i = 0; i < size_; i++)
        {
            new (foo + i) ValueT(std::move(arr_[i]));
            arr_[i].~ValueT();
        }
        std::free(arr_);
        arr_ = foo;
    }

    void shrink_to_fit()
    {
        reserve(size_);
    }

    void push_back(ValueT const &val)
    {
        if (size_ != capacity_)
        {
            new (arr_ + size_) ValueT(val);
            size_++;
            return;
        }
        reserve(capacity_ + 1);
        new (arr_ + size_) ValueT(val);
        size_++;
        return;
    }

    ValueT pop_back()
    {
        ValueT val = arr_[size_ - 1];
        arr_[size_ - 1].~ValueT();
        size_--;
        return val;
    }

    bool empty() const
    {
        return size_ <= 0;
    }

    vector &operator=(vector vec)
    {
        swap(*this, vec);
        return *this;
    }

    ValueT &operator[](size_t const &i) const
    {
        return arr_[i];
    }

    ValueT &at(size_t const &i) const
    {
        if (i <= size_)
        {
            return arr_[i];
        }
        throw std::out_of_range("Index out of bounds");
    }

    friend void swap(vector &vec1, vector &vec2)
    {
        std::swap(vec1.arr_, vec2.arr_);
        std::swap(vec1.size_, vec2.size_);
        std::swap(vec1.capacity_, vec2.capacity_);
    }

  private:
    size_t size_;
    size_t capacity_;
    ValueT *arr_;
};
} // namespace my
#endif
