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
// Arithmetic Implementations
//==================================================

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix<T>::operator+: dimension mismatch");
    }

    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix<T>::operator-: dimension mismatch");
    }

    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix<T>::operator+=: dimension mismatch");
    }

    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        data_[i] += other.data_[i];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix<T>::operator-=: dimension mismatch");
    }

    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        data_[i] -= other.data_[i];
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const
{
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& scalar) const
{
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] / scalar;
    }
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar)
{
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        data_[i] *= scalar;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& scalar)
{
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        data_[i] /= scalar;
    }
    return *this;
}

//==================================================
// Capacity Implementations
//==================================================

template<typename T>
void Matrix<T>::resize(std::size_t rows, std::size_t cols)
{
    data_.resize(rows * cols);
    rows_ = rows;
    cols_ = cols;
}

template<typename T>
void Matrix<T>::resize(std::size_t rows, std::size_t cols, const T& value)
{
    data_.resize(rows * cols, value);
    rows_ = rows;
    cols_ = cols;
}

template<typename T>
void Matrix<T>::reserve(std::size_t capacity)
{
    data_.reserve(capacity);
}

template<typename T>
std::size_t Matrix<T>::capacity() const noexcept
{
    return data_.capacity();
}

template<typename T>
void Matrix<T>::shrink_to_fit()
{
    data_.shrink_to_fit();
}

template<typename T>
std::size_t Matrix<T>::max_size() const noexcept
{
    return data_.max_size();
}

//==================================================
// Iterator Implementations
//==================================================

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() noexcept
{
    return data_.begin();
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const noexcept
{
    return data_.begin();
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() noexcept
{
    return data_.end();
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const noexcept
{
    return data_.end();
}

template<typename T>
typename Matrix<T>::reverse_iterator Matrix<T>::rbegin() noexcept
{
    return data_.rbegin();
}

template<typename T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rbegin() const noexcept
{
    return data_.rbegin();
}

template<typename T>
typename Matrix<T>::reverse_iterator Matrix<T>::rend() noexcept
{
    return data_.rend();
}

template<typename T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rend() const noexcept
{
    return data_.rend();
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::cbegin() const noexcept
{
    return data_.cbegin();
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::cend() const noexcept
{
    return data_.cend();
}

template<typename T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crbegin() const noexcept
{
    return data_.crbegin();
}

template<typename T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crend() const noexcept
{
    return data_.crend();
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