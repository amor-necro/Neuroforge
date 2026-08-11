#pragma once

#include <cstddef>

#include "matrix_view_iterator.hpp"

namespace neuroforge::math
{

template<typename T>
class MatrixView
{
private:
    T* data_ = nullptr;
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::size_t stride_ = 0;

    // MatrixView is a non-owning borrow of existing storage.
    // The pointed-to memory must outlive this view.
    // Any operation on the source storage that reallocates or destroys
    // its underlying buffer (e.g. std::vector reallocation, Matrix destruction)
    // invalidates all views referring to that storage.
    // Overlapping views are allowed; algorithms that mutate through views
    // must account for possible aliasing.

public:
    MatrixView() = default;

    MatrixView(T* data,
               std::size_t rows,
               std::size_t cols,
               std::size_t stride) noexcept;

    [[nodiscard]]
    std::size_t rows() const noexcept;

    [[nodiscard]]
    std::size_t cols() const noexcept;

    [[nodiscard]]
    std::size_t stride() const noexcept;

    [[nodiscard]]
    std::size_t size() const noexcept;

    T& operator()(std::size_t row,
                  std::size_t col);

    const T& operator()(std::size_t row,
                        std::size_t col) const;

    T* data() noexcept;

    const T* data() const noexcept;

    using iterator = MatrixViewIterator<T>;
    using const_iterator = MatrixViewIterator<const T>;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
};

#include "matrix_view.tpp"

} // namespace neuroforge::math
