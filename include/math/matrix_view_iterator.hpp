#pragma once

#include <cstddef>

namespace neuroforge::math
{

template<typename T>
class MatrixViewIterator
{
private:
    T* base_ = nullptr;
    std::size_t index_ = 0;
    std::size_t stride_ = 0;
    std::size_t cols_ = 0;

public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    MatrixViewIterator() = default;

    MatrixViewIterator(T* base,
                       std::size_t index,
                       std::size_t stride,
                       std::size_t cols) noexcept;

    reference operator*() const;

    pointer operator->() const;

    bool operator==(MatrixViewIterator other) const;
    bool operator!=(MatrixViewIterator other) const;
    auto operator<=>(MatrixViewIterator other) const;

    MatrixViewIterator& operator++();
    MatrixViewIterator operator++(int);
    MatrixViewIterator& operator--();
    MatrixViewIterator operator--(int);

    MatrixViewIterator& operator+=(difference_type n);
    MatrixViewIterator& operator-=(difference_type n);
    MatrixViewIterator operator+(difference_type n) const;
    MatrixViewIterator operator-(difference_type n) const;
    friend MatrixViewIterator operator+(difference_type n,
                                        const MatrixViewIterator& it);
    difference_type operator-(MatrixViewIterator other) const;
    reference operator[](difference_type n) const;
};

#include "matrix_view_iterator.tpp"

} // namespace neuroforge::math
