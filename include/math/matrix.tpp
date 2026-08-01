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

template<typename T>
T& Matrix<T>::at(std::size_t row,
                 std::size_t col)
{
    if (row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Matrix<T>::at: index out of range");
    }

    return data_[(row * cols_) + col];
}

template<typename T>
const T& Matrix<T>::at(std::size_t row,
                       std::size_t col) const
{
    if (row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Matrix<T>::at: index out of range");
    }

    return data_[(row * cols_) + col];
}

template<typename T>
T& Matrix<T>::front()
{
    assert(!data_.empty());

    return data_.front();
}

template<typename T>
const T& Matrix<T>::front() const
{
    assert(!data_.empty());

    return data_.front();
}

template<typename T>
T& Matrix<T>::back()
{
    assert(!data_.empty());

    return data_.back();
}

template<typename T>
const T& Matrix<T>::back() const
{
    assert(!data_.empty());

    return data_.back();
}

template<typename T>
T* Matrix<T>::data() noexcept
{
    return data_.data();
}

template<typename T>
const T* Matrix<T>::data() const noexcept
{
    return data_.data();
}

//==================================================
// Modifier Implementations
//==================================================

template<typename T>
void Matrix<T>::fill(const T& value)
{
    std::fill(data_.begin(), data_.end(), value);
}

template<typename T>
void Matrix<T>::clear() noexcept
{
    data_.clear();
    rows_ = 0;
    cols_ = 0;
}

template<typename T>
void Matrix<T>::swap(Matrix& other) noexcept
{
    using std::swap;
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
    swap(data_, other.data_);
}

//==================================================
// Comparison Implementations
//==================================================

template<typename T>
bool Matrix<T>::operator==(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        return false;
    }

    return std::equal(data_.begin(), data_.end(), other.data_.begin());
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& other) const
{
    return !(*this == other);
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