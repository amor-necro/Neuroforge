// Constructor Implementations

template<typename T>
Matrix<T>::Matrix(std::size_t rows,
                  std::size_t cols)
    : rows_(rows),
      cols_(cols),
      data_(rows * cols)
{
}

template<typename T>
Matrix<T>::Matrix(std::size_t rows,
                  std::size_t cols,
                  const T& value)
    : rows_(rows),
      cols_(cols),
      data_(rows * cols, value)
{
}

//==================================================
// Element Access Implementations
//==================================================

template<typename T>
T& Matrix<T>::operator()(std::size_t row,
                         std::size_t col)
{
    assert(row < rows_);
    assert(col < cols_);

    return data_[(row * cols_) + col];
}

template<typename T>
const T& Matrix<T>::operator()(std::size_t row,
                               std::size_t col) const
{
    assert(row < rows_);
    assert(col < cols_);

    return data_[(row * cols_) + col];
}

//==================================================
// Observer Implementations
//==================================================

template<typename T>
std::size_t Matrix<T>::rows() const noexcept
{
    return rows_;
}

template<typename T>
std::size_t Matrix<T>::cols() const noexcept
{
    return cols_;
}

template<typename T>
std::size_t Matrix<T>::size() const noexcept
{
    return data_.size();
}

template<typename T>
bool Matrix<T>::empty() const noexcept
{
    return data_.empty();
}