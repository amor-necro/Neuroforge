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


    // Capacity

    void resize(std::size_t rows, std::size_t cols);

    void resize(std::size_t rows, std::size_t cols, const T& value);

    void reserve(std::size_t capacity);

    [[nodiscard]]
    std::size_t capacity() const noexcept;

    void shrink_to_fit();

    [[nodiscard]]
    std::size_t max_size() const noexcept;


    // Comparison

    bool operator==(const Matrix& other) const;

    bool operator!=(const Matrix& other) const;


    // Arithmetic

    Matrix operator+(const Matrix& other) const;

    Matrix operator-(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);

    Matrix& operator-=(const Matrix& other);

    Matrix operator*(const T& scalar) const;

    Matrix operator/(const T& scalar) const;

    Matrix& operator*=(const T& scalar);

    Matrix& operator/=(const T& scalar);


    // Iterators

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;
    using difference_type = typename std::vector<T>::difference_type;
    using value_type = typename std::vector<T>::value_type;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;


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