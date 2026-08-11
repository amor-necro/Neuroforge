template<typename T>
MatrixView<T>::MatrixView(T* data,
                           std::size_t rows,
                           std::size_t cols,
                           std::size_t stride) noexcept
    : data_(data)
    , rows_(rows)
    , cols_(cols)
    , stride_(stride)
{
}

template<typename T>
std::size_t MatrixView<T>::rows() const noexcept
{
    return rows_;
}

template<typename T>
std::size_t MatrixView<T>::cols() const noexcept
{
    return cols_;
}

template<typename T>
std::size_t MatrixView<T>::stride() const noexcept
{
    return stride_;
}

template<typename T>
std::size_t MatrixView<T>::size() const noexcept
{
    return rows_ * cols_;
}

template<typename T>
T& MatrixView<T>::operator()(std::size_t row,
                              std::size_t col)
{
    assert(row < rows_);
    assert(col < cols_);

    return data_[(row * stride_) + col];
}

template<typename T>
const T& MatrixView<T>::operator()(std::size_t row,
                                    std::size_t col) const
{
    assert(row < rows_);
    assert(col < cols_);

    return data_[(row * stride_) + col];
}

template<typename T>
T* MatrixView<T>::data() noexcept
{
    return data_;
}

template<typename T>
const T* MatrixView<T>::data() const noexcept
{
    return data_;
}

template<typename T>
typename MatrixView<T>::iterator MatrixView<T>::begin() noexcept
{
    return iterator(data_, 0, stride_, cols_);
}

template<typename T>
typename MatrixView<T>::iterator MatrixView<T>::end() noexcept
{
    return iterator(data_, rows_ * cols_, stride_, cols_);
}

template<typename T>
typename MatrixView<T>::const_iterator MatrixView<T>::begin() const noexcept
{
    return const_iterator(data_, 0, stride_, cols_);
}

template<typename T>
typename MatrixView<T>::const_iterator MatrixView<T>::end() const noexcept
{
    return const_iterator(data_, rows_ * cols_, stride_, cols_);
}
