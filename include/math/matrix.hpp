#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace neuroforge::math
{

template<typename T>
class Matrix
{
private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<T> data_;

public:

    // Constructors

    Matrix() = default;

    Matrix(std::size_t rows,
           std::size_t cols);

    Matrix(std::size_t rows,
           std::size_t cols,
           const T& value);


    // Special Member Functions (Rule of Five)

    ~Matrix() = default;

    Matrix(const Matrix&) = default;

    Matrix& operator=(const Matrix&) = default;

    Matrix(Matrix&&) noexcept = default;

    Matrix& operator=(Matrix&&) noexcept = default;


    // Element Access

    T& operator()(std::size_t row,
                  std::size_t col);

    const T& operator()(std::size_t row,
                        std::size_t col) const;

    T& at(std::size_t row,
          std::size_t col);

    const T& at(std::size_t row,
                std::size_t col) const;

    T& front();

    const T& front() const;

    T& back();

    const T& back() const;

    T* data() noexcept;

    const T* data() const noexcept;


    // Modifiers

    void fill(const T& value);

    void clear() noexcept;

    void swap(Matrix& other) noexcept;


    // Comparison

    bool operator==(const Matrix& other) const;

    bool operator!=(const Matrix& other) const;


    // Observers

    [[nodiscard]]
    std::size_t rows() const noexcept;

    [[nodiscard]]
    std::size_t cols() const noexcept;

    [[nodiscard]]
    std::size_t size() const noexcept;

    [[nodiscard]]
    bool empty() const noexcept;
};

#include "matrix.tpp"

} // namespace neuroforge::math