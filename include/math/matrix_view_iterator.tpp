template<typename T>
MatrixViewIterator<T>::MatrixViewIterator(T* base,
                                           std::size_t index,
                                           std::size_t stride,
                                           std::size_t cols) noexcept
    : base_(base)
    , index_(index)
    , stride_(stride)
    , cols_(cols)
{
}

template<typename T>
typename MatrixViewIterator<T>::reference
MatrixViewIterator<T>::operator*() const
{
    std::size_t row = index_ / cols_;
    std::size_t col = index_ % cols_;
    return *(base_ + (row * stride_) + col);
}

template<typename T>
typename MatrixViewIterator<T>::pointer
MatrixViewIterator<T>::operator->() const
{
    return &**this;
}

template<typename T>
bool MatrixViewIterator<T>::operator==(MatrixViewIterator other) const
{
    return index_ == other.index_;
}

template<typename T>
bool MatrixViewIterator<T>::operator!=(MatrixViewIterator other) const
{
    return !(*this == other);
}

template<typename T>
auto MatrixViewIterator<T>::operator<=>(MatrixViewIterator other) const
{
    return index_ <=> other.index_;
}

template<typename T>
MatrixViewIterator<T>& MatrixViewIterator<T>::operator++()
{
    ++index_;
    return *this;
}

template<typename T>
MatrixViewIterator<T> MatrixViewIterator<T>::operator++(int)
{
    MatrixViewIterator tmp = *this;
    ++index_;
    return tmp;
}

template<typename T>
MatrixViewIterator<T>& MatrixViewIterator<T>::operator--()
{
    --index_;
    return *this;
}

template<typename T>
MatrixViewIterator<T> MatrixViewIterator<T>::operator--(int)
{
    MatrixViewIterator tmp = *this;
    --index_;
    return tmp;
}

template<typename T>
MatrixViewIterator<T>& MatrixViewIterator<T>::operator+=(difference_type n)
{
    if (n >= 0)
    {
        index_ += static_cast<std::size_t>(n);
    }
    else
    {
        index_ -= static_cast<std::size_t>(-n);
    }
    return *this;
}

template<typename T>
MatrixViewIterator<T>& MatrixViewIterator<T>::operator-=(difference_type n)
{
    if (n >= 0)
    {
        index_ -= static_cast<std::size_t>(n);
    }
    else
    {
        index_ += static_cast<std::size_t>(-n);
    }
    return *this;
}

template<typename T>
MatrixViewIterator<T> MatrixViewIterator<T>::operator+(difference_type n) const
{
    MatrixViewIterator tmp = *this;
    tmp += n;
    return tmp;
}

template<typename T>
MatrixViewIterator<T> MatrixViewIterator<T>::operator-(difference_type n) const
{
    MatrixViewIterator tmp = *this;
    tmp -= n;
    return tmp;
}

template<typename T>
typename MatrixViewIterator<T>::difference_type
MatrixViewIterator<T>::operator-(MatrixViewIterator other) const
{
    return static_cast<difference_type>(index_) - static_cast<difference_type>(other.index_);
}

template<typename T>
typename MatrixViewIterator<T>::reference
MatrixViewIterator<T>::operator[](difference_type n) const
{
    return *(*this + n);
}
