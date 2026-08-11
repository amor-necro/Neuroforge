#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>

#include "math/matrix.hpp"
#include "math/matrix_view.hpp"

using neuroforge::math::Matrix;
using neuroforge::math::MatrixView;
using neuroforge::math::MatrixViewIterator;


// C++23 random_access_iterator concept validation


using Iter = MatrixViewIterator<int>;
using CIter = MatrixViewIterator<const int>;

static_assert(std::input_iterator<Iter>);
static_assert(std::forward_iterator<Iter>);
static_assert(std::bidirectional_iterator<Iter>);
static_assert(std::incrementable<Iter>);
static_assert(std::sentinel_for<Iter, Iter>);
static_assert(std::indirectly_readable<Iter>);
static_assert(std::totally_ordered<Iter>);
static_assert(std::regular<Iter>);
static_assert(std::random_access_iterator<Iter>);
static_assert(std::random_access_iterator<CIter>);


// Compile-time const-correctness checks


static_assert(std::is_same_v<decltype(std::declval<Matrix<int>&>().row(0)), MatrixView<int>>);
static_assert(std::is_same_v<decltype(std::declval<const Matrix<int>&>().row(0)), MatrixView<const int>>);

static_assert(std::is_same_v<decltype(std::declval<Matrix<int>&>().column(0)), MatrixView<int>>);
static_assert(std::is_same_v<decltype(std::declval<const Matrix<int>&>().column(0)), MatrixView<const int>>);

static_assert(std::is_same_v<decltype(std::declval<Matrix<int>&>().block(0, 0, 1, 1)), MatrixView<int>>);
static_assert(std::is_same_v<decltype(std::declval<const Matrix<int>&>().block(0, 0, 1, 1)), MatrixView<const int>>);

static_assert(std::is_same_v<MatrixView<int>, MatrixView<int>>);
static_assert(std::is_same_v<MatrixView<const int>, MatrixView<const int>>);
static_assert(!std::is_same_v<MatrixView<int>, MatrixView<const int>>);


// Type properties


void test_matrix_view_is_default_constructible()
{
    MatrixView<int> view;
    assert(view.rows() == 0);
    assert(view.cols() == 0);
    assert(view.stride() == 0);
    assert(view.size() == 0);
}


// Construction: basic metadata


void test_matrix_view_basic_construction()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    assert(view.rows() == 2);
    assert(view.cols() == 3);
    assert(view.stride() == 3);
    assert(view.size() == 6);
}


// Construction: no data copy


void test_matrix_view_does_not_copy_data()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    assert(!view.empty());
    assert(view.size() == 6);
}


// Construction: empty storage


void test_matrix_view_empty_storage()
{
    MatrixView<int> view(nullptr, 0, 0, 0);

    assert(view.empty());
    assert(view.size() == 0);
    assert(view.rows() == 0);
    assert(view.cols() == 0);
    assert(view.stride() == 0);
}


// Construction: single element


void test_matrix_view_single_element()
{
    int value = 42;
    MatrixView view(&value, 1, 1, 1);

    assert(view.rows() == 1);
    assert(view.cols() == 1);
    assert(view.stride() == 1);
    assert(view.size() == 1);
}


// Construction: rectangular


void test_matrix_view_rectangular()
{
    int storage[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    MatrixView view(storage, 3, 4, 4);

    assert(view.rows() == 3);
    assert(view.cols() == 4);
    assert(view.stride() == 4);
    assert(view.size() == 12);
}


// Construction: non-unit stride


void test_matrix_view_non_unit_stride()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 2, 3);

    assert(view.rows() == 2);
    assert(view.cols() == 2);
    assert(view.stride() == 3);
    assert(view.size() == 4);
}


// Construction: const type


void test_matrix_view_const_type()
{
    const int storage[] = {1, 2, 3};
    MatrixView<const int> view(storage, 1, 3, 3);

    assert(view.rows() == 1);
    assert(view.cols() == 3);
    assert(view.stride() == 3);
    assert(view.size() == 3);
}


// Element Access: operator()


void test_operator_parentheses_basic()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    assert(view(0, 0) == 1);
    assert(view(0, 1) == 2);
    assert(view(0, 2) == 3);
    assert(view(1, 0) == 4);
    assert(view(1, 1) == 5);
    assert(view(1, 2) == 6);
}


void test_operator_parentheses_mutable()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    view(0, 0) = 10;
    view(1, 2) = 60;

    assert(storage[0] == 10);
    assert(storage[5] == 60);
}


void test_operator_parentheses_const()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    const MatrixView<int>& cview = view;

    assert(cview(0, 0) == 1);
    assert(cview(1, 2) == 6);

    (void)cview;
}


void test_operator_parentheses_strided_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 2, 3);

    assert(view(0, 0) == 1);
    assert(view(0, 1) == 2);
    assert(view(1, 0) == 4);
    assert(view(1, 1) == 5);

    view(0, 1) = 99;
    assert(storage[1] == 99);
    assert(storage[4] == 5);
}


void test_operator_parentheses_first_last()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    assert(view(0, 0) == view.front());
    assert(view(1, 2) == view.back());
}


// Matrix::row()


void test_row_basic()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> r = A.row(1);

    assert(r.rows() == 1);
    assert(r.cols() == 3);
    assert(r.stride() == 3);
    assert(r.size() == 3);

    assert(r(0, 0) == 4);
    assert(r(0, 1) == 5);
    assert(r(0, 2) == 6);
}


void test_row_write_through()
{
    Matrix<int> A(3, 3, 0);
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    MatrixView<int> r = A.row(1);
    r(0, 0) = 40;
    r(0, 2) = 60;

    assert(A(1, 0) == 40);
    assert(A(1, 1) == 5);
    assert(A(1, 2) == 60);
}


void test_row_first_middle_last()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> r0 = A.row(0);
    MatrixView<int> r1 = A.row(1);
    MatrixView<int> r2 = A.row(2);

    assert(r0(0, 0) == 1); assert(r0(0, 1) == 2); assert(r0(0, 2) == 3);
    assert(r1(0, 0) == 4); assert(r1(0, 1) == 5); assert(r1(0, 2) == 6);
    assert(r2(0, 0) == 7); assert(r2(0, 1) == 8); assert(r2(0, 2) == 9);
}


void test_row_const()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> r = CA.row(1);

    assert(r.rows() == 1);
    assert(r.cols() == 3);
    assert(r.stride() == 3);

    assert(r(0, 0) == 4);
    assert(r(0, 1) == 5);
    assert(r(0, 2) == 6);
}


void test_row_single_row_matrix()
{
    Matrix<int> A(1, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;

    MatrixView<int> r = A.row(0);

    assert(r.rows() == 1);
    assert(r.cols() == 3);
    assert(r.stride() == 3);
    assert(r.size() == 3);

    assert(r(0, 0) == 1);
    assert(r(0, 1) == 2);
    assert(r(0, 2) == 3);
}


// Matrix::column()


void test_column_basic()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> c = A.column(1);

    assert(c.rows() == 3);
    assert(c.cols() == 1);
    assert(c.stride() == 3);
    assert(c.size() == 3);

    assert(c(0, 0) == 2);
    assert(c(1, 0) == 5);
    assert(c(2, 0) == 8);
}


void test_column_first_middle_last()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> c0 = A.column(0);
    MatrixView<int> c1 = A.column(1);
    MatrixView<int> c2 = A.column(2);

    assert(c0(0, 0) == 1); assert(c0(1, 0) == 4); assert(c0(2, 0) == 7);
    assert(c1(0, 0) == 2); assert(c1(1, 0) == 5); assert(c1(2, 0) == 8);
    assert(c2(0, 0) == 3); assert(c2(1, 0) == 6); assert(c2(2, 0) == 9);
}


void test_column_write_through()
{
    Matrix<int> A(3, 3, 0);
    A(0, 1) = 2; A(1, 1) = 5; A(2, 1) = 8;

    MatrixView<int> c = A.column(1);
    c(0, 0) = 20;
    c(2, 0) = 80;

    assert(A(0, 1) == 20);
    assert(A(1, 1) == 5);
    assert(A(2, 1) == 80);
}


void test_column_const()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> c = CA.column(2);

    assert(c.rows() == 2);
    assert(c.cols() == 1);
    assert(c.stride() == 3);

    assert(c(0, 0) == 3);
    assert(c(1, 0) == 6);
}


void test_column_single_column_matrix()
{
    Matrix<int> A(3, 1, 0);
    A(0, 0) = 1;
    A(1, 0) = 4;
    A(2, 0) = 7;

    MatrixView<int> c = A.column(0);

    assert(c.rows() == 3);
    assert(c.cols() == 1);
    assert(c.stride() == 1);
    assert(c.size() == 3);

    assert(c(0, 0) == 1);
    assert(c(1, 0) == 4);
    assert(c(2, 0) == 7);
}


void test_column_strided_access()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView view(storage, 2, 3, 3);

    MatrixView<int> c(storage + 1, 2, 1, 3);

    assert(c.rows() == 2);
    assert(c.cols() == 1);
    assert(c.stride() == 3);

    assert(c(0, 0) == 2);
    assert(c(1, 0) == 5);

    c(1, 0) = 99;
    assert(storage[4] == 99);
    assert(storage[1] == 2);
}


// Matrix::block()


void test_block_basic()
{
    Matrix<int> A(4, 4, 0);
    A(0, 0) =  1; A(0, 1) =  2; A(0, 2) =  3; A(0, 3) =  4;
    A(1, 0) =  5; A(1, 1) =  6; A(1, 2) =  7; A(1, 3) =  8;
    A(2, 0) =  9; A(2, 1) = 10; A(2, 2) = 11; A(2, 3) = 12;
    A(3, 0) = 13; A(3, 1) = 14; A(3, 2) = 15; A(3, 3) = 16;

    MatrixView<int> b = A.block(1, 1, 2, 2);

    assert(b.rows() == 2);
    assert(b.cols() == 2);
    assert(b.stride() == 4);
    assert(b.size() == 4);

    assert(b(0, 0) ==  6);
    assert(b(0, 1) ==  7);
    assert(b(1, 0) == 10);
    assert(b(1, 1) == 11);
}


void test_block_single_element()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> b = A.block(1, 1, 1, 1);

    assert(b.rows() == 1);
    assert(b.cols() == 1);
    assert(b.stride() == 3);
    assert(b.size() == 1);
    assert(b(0, 0) == 5);
}


void test_block_full_matrix()
{
    Matrix<int> A(3, 3, 7);

    MatrixView<int> b = A.block(0, 0, 3, 3);

    assert(b.rows() == 3);
    assert(b.cols() == 3);
    assert(b.stride() == 3);
    assert(b.size() == 9);

    for (std::size_t i = 0; i < b.rows(); ++i)
    {
        for (std::size_t j = 0; j < b.cols(); ++j)
        {
            assert(b(i, j) == 7);
        }
    }
}


void test_block_top_left()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> b = A.block(0, 0, 2, 2);

    assert(b(0, 0) == 1);
    assert(b(0, 1) == 2);
    assert(b(1, 0) == 4);
    assert(b(1, 1) == 5);
}


void test_block_bottom_right()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> b = A.block(1, 1, 2, 2);

    assert(b(0, 0) == 5);
    assert(b(0, 1) == 6);
    assert(b(1, 0) == 8);
    assert(b(1, 1) == 9);
}


void test_block_write_through()
{
    Matrix<int> A(4, 4, 0);
    A(1, 1) = 6; A(1, 2) = 7;
    A(2, 1) = 10; A(2, 2) = 11;

    MatrixView<int> b = A.block(1, 1, 2, 2);
    b(0, 0) = 60;
    b(1, 1) = 110;

    assert(A(1, 1) == 60);
    assert(A(1, 2) ==  7);
    assert(A(2, 1) == 10);
    assert(A(2, 2) == 110);
}


void test_block_const()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    const Matrix<int>& CA = A;
    MatrixView<const int> b = CA.block(1, 1, 2, 2);

    assert(b.rows() == 2);
    assert(b.cols() == 2);
    assert(b.stride() == 3);

    assert(b(0, 0) == 5);
    assert(b(0, 1) == 6);
    assert(b(1, 0) == 8);
    assert(b(1, 1) == 9);
}


void test_block_cols_not_equal_stride()
{
    Matrix<int> A(3, 4, 0);
    A(0, 0) =  1; A(0, 1) =  2; A(0, 2) =  3; A(0, 3) =  4;
    A(1, 0) =  5; A(1, 1) =  6; A(1, 2) =  7; A(1, 3) =  8;
    A(2, 0) =  9; A(2, 1) = 10; A(2, 2) = 11; A(2, 3) = 12;

    MatrixView<int> b = A.block(0, 1, 3, 2);

    assert(b.cols() == 2);
    assert(b.stride() == 4);

    assert(b(0, 0) == 2);
    assert(b(0, 1) == 3);
    assert(b(1, 0) == 6);
    assert(b(1, 1) == 7);
    assert(b(2, 0) == 10);
    assert(b(2, 1) == 11);
}


void test_block_zero_rows()
{
    Matrix<int> A(3, 3, 0);

    MatrixView<int> b = A.block(1, 1, 0, 2);

    assert(b.rows() == 0);
    assert(b.cols() == 2);
    assert(b.stride() == 3);
    assert(b.size() == 0);
}


void test_block_zero_cols()
{
    Matrix<int> A(3, 3, 0);

    MatrixView<int> b = A.block(1, 1, 2, 0);

    assert(b.rows() == 2);
    assert(b.cols() == 0);
    assert(b.stride() == 3);
    assert(b.size() == 0);
}


// Const correctness


void test_const_row_view_data_pointer()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> r = CA.row(1);

    assert(r.data() == A.data() + 3);
}


void test_const_column_view_data_pointer()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> c = CA.column(1);

    assert(c.data() == A.data() + 1);
}


void test_const_block_view_data_pointer()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    const Matrix<int>& CA = A;
    MatrixView<const int> b = CA.block(1, 1, 2, 2);

    assert(b.data() == A.data() + 4);
}


void test_const_row_view_readonly()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> r = CA.row(1);

    assert(r(0, 0) == 4);
    assert(r(0, 1) == 5);
    assert(r(0, 2) == 6);
}


void test_const_column_view_readonly()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    const Matrix<int>& CA = A;
    MatrixView<const int> c = CA.column(1);

    assert(c(0, 0) == 2);
    assert(c(1, 0) == 5);
}


void test_const_block_view_readonly()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    const Matrix<int>& CA = A;
    MatrixView<const int> b = CA.block(1, 1, 2, 2);

    assert(b(0, 0) == 5);
    assert(b(0, 1) == 6);
    assert(b(1, 0) == 8);
    assert(b(1, 1) == 9);
}


void test_mutable_view_data_pointer_matches_matrix()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    MatrixView<int> r = A.row(0);
    MatrixView<int> c = A.column(1);
    MatrixView<int> b = A.block(0, 0, 2, 2);

    assert(r.data() == A.data());
    assert(c.data() == A.data() + 1);
    assert(b.data() == A.data());
}


// Lifetime and aliasing


void test_lifetime_view_destroyed_before_matrix()
{
    Matrix<int> A(2, 2, 0);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    {
        MatrixView<int> v = A.row(0);
        assert(v(0, 0) == 1);
        assert(v(0, 1) == 2);
    }

    assert(A(0, 0) == 1);
    assert(A(1, 1) == 4);
}


void test_overlapping_views_share_storage()
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    MatrixView<int> b1 = A.block(0, 0, 2, 2);
    MatrixView<int> b2 = A.block(1, 1, 2, 2);

    assert(b1(1, 1) == 5);
    assert(b2(0, 0) == 5);

    b2(0, 0) = 50;
    assert(b1(1, 1) == 50);
    assert(A(1, 1) == 50);
}


void test_dangling_view_contract_documented()
{
    MatrixView<int> v;
    {
        Matrix<int> A(2, 2, 0);
        A(0, 0) = 1; A(0, 1) = 2;
        A(1, 0) = 3; A(1, 1) = 4;
        v = A.row(0);
        assert(v(0, 0) == 1);
    } // A is destroyed here. v is now dangling.

    // v is NOT dereferenced after A is destroyed.
    // Dereferencing v here would be undefined behavior.
    // Neuroforge does not track view lifetimes; the caller must ensure
    // the source storage outlives every view that refers to it.
    (void)v;
}


// Iterator traversal


void test_iterator_dereference_row_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
}


void test_iterator_arrow_row_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(it.operator->() == &*it);
    assert(*it == 1);
}


void test_iterator_prefix_increment()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(*it == 1);
    ++it;
    assert(*it == 2);
    assert(&*it == storage + 1);
}


void test_iterator_postfix_increment()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(*it == 1);
    MatrixViewIterator<int> old = it++;
    assert(*old == 1);
    assert(*it == 2);
}


void test_iterator_prefix_decrement()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 1, 3, 3);

    assert(*it == 2);
    --it;
    assert(*it == 1);
}


void test_iterator_postfix_decrement()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 1, 3, 3);

    assert(*it == 2);
    MatrixViewIterator<int> old = it--;
    assert(*old == 2);
    assert(*it == 1);
}


void test_iterator_row_boundary_crossing()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 2, 3);
    MatrixViewIterator<int> it(storage, 0, 3, 2);

    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 4);
    ++it;
    assert(*it == 5);
}


void test_iterator_column_view_stride()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 1);

    assert(*it == 1);
    ++it;
    assert(*it == 4);
    ++it;
    assert(*it == 7);
}


void test_iterator_block_view_gap_skip()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage + 1, 0, 3, 2);

    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 6);
}


void test_iterator_const_dereference()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    const int* cstorage = storage;
    MatrixViewIterator<const int> it(cstorage, 0, 3, 3);

    assert(*it == 1);
    ++it;
    assert(*it == 2);
}


void test_iterator_const_arrow()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    const int* cstorage = storage;
    MatrixViewIterator<const int> it(cstorage, 0, 3, 3);

    assert(it.operator->() == &*it);
}


void test_iterator_mutable_write_through()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    *it = 10;
    assert(storage[0] == 10);

    ++it;
    *it = 20;
    assert(storage[1] == 20);
}


// Iterator random access


void test_iterator_operator_plus_positive()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(*(it + 0) == 1);
    assert(*(it + 1) == 2);
    assert(*(it + 2) == 3);
    assert(*(it + 3) == 4);
}


void test_iterator_operator_plus_negative()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 3, 3, 3);

    assert(*(it + (-2)) == 2);
    assert(*(it + (-1)) == 3);
    assert(*(it + 0) == 4);
}


void test_iterator_operator_minus()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 3, 3, 3);

    assert(*(it - 1) == 3);
    assert(*(it - 2) == 2);
    assert(*(it - 3) == 1);
}


void test_iterator_operator_plus_equals()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    it += 2;
    assert(*it == 3);

    it += 1;
    assert(*it == 4);
}


void test_iterator_operator_minus_equals()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 3, 3, 3);

    it -= 2;
    assert(*it == 2);

    it -= 1;
    assert(*it == 1);
}


void test_iterator_operator_bracket()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(it[0] == 1);
    assert(it[1] == 2);
    assert(it[2] == 3);
    assert(it[3] == 4);
    assert(it[4] == 5);
    assert(it[5] == 6);
}


void test_iterator_difference()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it1(storage, 0, 3, 3);
    MatrixViewIterator<int> it2(storage, 3, 3, 3);

    assert(it2 - it1 == 3);
    assert(it1 - it2 == -3);
    assert(it1 - it1 == 0);
}


void test_iterator_row_boundary_jump()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 2);

    assert(*it == 1);
    assert(*(it + 1) == 2);
    assert(*(it + 2) == 4);
    assert(*(it + 3) == 5);
}


void test_iterator_column_view_random_access()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 1);

    assert(*it == 1);
    assert(*(it + 1) == 4);
    assert(*(it + 2) == 7);
    assert(it[0] == 1);
    assert(it[1] == 4);
    assert(it[2] == 7);
}


void test_iterator_block_view_random_access()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage + 1, 0, 3, 2);

    assert(*it == 2);
    assert(it[0] == 2);
    assert(it[1] == 3);
    assert(it[2] == 5);
    assert(it[3] == 6);

    assert(*(it + 2) == 5);
}


void test_iterator_const_random_access()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<const int> it(storage, 0, 3, 3);

    assert(it[0] == 1);
    assert(it[1] == 2);
    assert(it[2] == 3);
    assert(*(it + 3) == 4);

    MatrixViewIterator<const int> it2(storage, 2, 3, 3);
    assert(it2 - it == 2);
}


// begin() / end()


void test_begin_end_basic()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto it = view.begin();
    auto end = view.end();

    assert(it != end);
    assert(*it == 1);

    ++it;
    assert(*it == 2);

    it += 4;
    assert(it == end);
}


void test_begin_end_empty_view()
{
    MatrixView<int> view;

    assert(view.begin() == view.end());
}


void test_begin_end_row_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> row(storage, 1, 3, 3);

    auto it = row.begin();
    auto end = row.end();

    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(it == end);
    assert(end - row.begin() == 3);
}


void test_begin_end_column_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> col(storage + 1, 2, 1, 3);

    auto it = col.begin();
    auto end = col.end();

    assert(*it == 2);
    ++it;
    assert(*it == 5);
    ++it;
    assert(it == end);
    assert(end - col.begin() == 2);
}


void test_begin_end_block_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> block(storage + 1, 2, 2, 3);

    auto it = block.begin();
    auto end = block.end();

    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 6);
    ++it;
    assert(it == end);
    assert(end - block.begin() == 4);
}


// Iterator comparisons


void test_iterator_equality()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto it1 = view.begin();
    auto it2 = view.begin();
    auto it3 = view.begin();
    ++it3;

    assert(it1 == it2);
    assert(it1 != it3);
    assert(it2 != it3);
}


void test_iterator_less()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto it1 = view.begin();
    auto it2 = view.begin();
    ++it2;
    auto it3 = view.end();

    assert(it1 < it2);
    assert(it1 <= it2);
    assert(it2 > it1);
    assert(it2 >= it1);
    assert(it1 < it3);
    assert(it3 > it1);
    assert(it1 <= it3);
    assert(it3 >= it1);
    assert(it1 <= it1);
    assert(it1 >= it1);
}


void test_end_minus_begin_equals_size()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    assert(view.end() - view.begin() == 6);
}


void test_begin_plus_size_equals_end()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    assert(view.begin() + view.size() == view.end());
}


// Range-for


void test_range_for_mutable()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    int sum = 0;
    for (auto& x : view)
    {
        sum += x;
        x = 0;
    }
    assert(sum == 21);
    for (std::size_t i = 0; i < view.size(); ++i)
    {
        assert(storage[i] == 0);
    }
}


void test_range_for_const()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    int sum = 0;
    for (const auto& x : view)
    {
        sum += x;
    }
    assert(sum == 21);
}


// Const iteration


void test_const_view_iterators_are_const()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    const MatrixView<int>& cview = view;
    auto it = cview.begin();
    auto end = cview.end();

    assert(*it == 1);
    ++it;
    assert(*it == 2);
    assert(it != end);
}


void test_iterator_n_plus_it()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 3);

    assert(*(2 + it) == 3);
    assert(*(it + 2) == 3);
}


void test_iterator_block_semantic_2x2()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> block(storage, 2, 2, 3);

    int values[4];
    int idx = 0;
    for (auto it = block.begin(); it != block.end(); ++it)
    {
        values[idx++] = *it;
    }

    assert(values[0] == 1);
    assert(values[1] == 2);
    assert(values[2] == 4);
    assert(values[3] == 5);
}


void test_iterator_block_begin_plus_2_points_to_4()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 2);

    assert(*it == 1);
    assert(*(it + 2) == 4);
    assert(it[2] == 4);
}


void test_iterator_block_operator_bracket_3_is_5()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 2);

    assert(it[0] == 1);
    assert(it[1] == 2);
    assert(it[2] == 4);
    assert(it[3] == 5);
}


void test_iterator_strided_column_traversal()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixViewIterator<int> it(storage, 0, 3, 1);

    assert(*it == 1);
    assert(*(it + 1) == 4);
    assert(*(it + 2) == 7);
    assert(it[0] == 1);
    assert(it[1] == 4);
    assert(it[2] == 7);
}


void test_iterator_end_minus_1_is_last()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    assert(*(view.end() - 1) == 6);
    assert(*(view.end() - 2) == 5);
}


void test_iterator_empty_view_begin_equals_end()
{
    MatrixView<int> view;
    assert(view.begin() == view.end());
}


void test_iterator_stl_distance()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto dist = std::distance(view.begin(), view.end());
    assert(dist == 6);
    (void)dist;
}


void test_iterator_stl_advance()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto it = view.begin();
    std::advance(it, 2);
    assert(*it == 3);

    std::advance(it, -1);
    assert(*it == 2);
}


void test_iterator_stl_accumulate()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    int sum = std::accumulate(view.begin(), view.end(), 0);
    assert(sum == 21);
    (void)sum;
}


void test_iterator_stl_find()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> view(storage, 2, 3, 3);

    auto it = std::find(view.begin(), view.end(), 4);
    assert(it != view.end());
    assert(*it == 4);
}


void test_iterator_stl_copy_block()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> block(storage, 2, 2, 3);

    int dest[4];
    std::copy(block.begin(), block.end(), dest);

    assert(dest[0] == 1);
    assert(dest[1] == 2);
    assert(dest[2] == 4);
    assert(dest[3] == 5);
}


void test_iterator_range_for_row_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> row(storage, 1, 3, 3);

    int sum = 0;
    for (int& x : row)
    {
        sum += x;
    }
    assert(sum == 6);
}


void test_iterator_range_for_column_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> col(storage + 1, 2, 1, 3);

    int sum = 0;
    for (int& x : col)
    {
        sum += x;
    }
    assert(sum == 2 + 5);
}


void test_iterator_range_for_block_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    MatrixView<int> block(storage + 1, 2, 2, 3);

    int values[4];
    int idx = 0;
    for (int& x : block)
    {
        values[idx++] = x;
    }

    assert(values[0] == 2);
    assert(values[1] == 3);
    assert(values[2] == 5);
    assert(values[3] == 6);
}


void test_iterator_const_range_for_block_view()
{
    int storage[] = {1, 2, 3, 4, 5, 6};
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    const Matrix<int>& CA = A;
    auto block = CA.block(0, 0, 2, 2);

    int sum = 0;
    for (const int& x : block)
    {
        sum += x;
    }
    assert(sum == 1 + 2 + 4 + 5);
}


int main()
{
    test_matrix_view_is_default_constructible();
    test_matrix_view_basic_construction();
    test_matrix_view_does_not_copy_data();
    test_matrix_view_empty_storage();
    test_matrix_view_single_element();
    test_matrix_view_rectangular();
    test_matrix_view_non_unit_stride();
    test_matrix_view_const_type();

    test_operator_parentheses_basic();
    test_operator_parentheses_mutable();
    test_operator_parentheses_const();
    test_operator_parentheses_strided_view();
    test_operator_parentheses_first_last();

    test_row_basic();
    test_row_write_through();
    test_row_first_middle_last();
    test_row_const();
    test_row_single_row_matrix();

    test_column_basic();
    test_column_first_middle_last();
    test_column_write_through();
    test_column_const();
    test_column_strided_access();
    test_column_single_column_matrix();

    test_block_basic();
    test_block_single_element();
    test_block_full_matrix();
    test_block_top_left();
    test_block_bottom_right();
    test_block_write_through();
    test_block_const();
    test_block_cols_not_equal_stride();
    test_block_zero_rows();
    test_block_zero_cols();

    test_const_row_view_data_pointer();
    test_const_column_view_data_pointer();
    test_const_block_view_data_pointer();
    test_const_row_view_readonly();
    test_const_column_view_readonly();
    test_const_block_view_readonly();
    test_mutable_view_data_pointer_matches_matrix();

    test_lifetime_view_destroyed_before_matrix();
    test_overlapping_views_share_storage();
    test_dangling_view_contract_documented();

    test_iterator_dereference_row_view();
    test_iterator_arrow_row_view();
    test_iterator_prefix_increment();
    test_iterator_postfix_increment();
    test_iterator_prefix_decrement();
    test_iterator_postfix_decrement();
    test_iterator_row_boundary_crossing();
    test_iterator_column_view_stride();
    test_iterator_block_view_gap_skip();
    test_iterator_const_dereference();
    test_iterator_const_arrow();
    test_iterator_mutable_write_through();

    test_iterator_operator_plus_positive();
    test_iterator_operator_plus_negative();
    test_iterator_operator_minus();
    test_iterator_operator_plus_equals();
    test_iterator_operator_minus_equals();
    test_iterator_operator_bracket();
    test_iterator_difference();
    test_iterator_row_boundary_jump();
    test_iterator_column_view_random_access();
    test_iterator_block_view_random_access();
    test_iterator_const_random_access();

    test_begin_end_basic();
    test_begin_end_empty_view();
    test_begin_end_row_view();
    test_begin_end_column_view();
    test_begin_end_block_view();

    test_iterator_equality();
    test_iterator_less();
    test_end_minus_begin_equals_size();
    test_begin_plus_size_equals_end();

    test_range_for_mutable();
    test_range_for_const();
    test_const_view_iterators_are_const();

    test_iterator_n_plus_it();
    test_iterator_block_semantic_2x2();
    test_iterator_block_begin_plus_2_points_to_4();
    test_iterator_block_operator_bracket_3_is_5();
    test_iterator_strided_column_traversal();
    test_iterator_end_minus_1_is_last();
    test_iterator_empty_view_begin_equals_end();
    test_iterator_stl_distance();
    test_iterator_stl_advance();
    test_iterator_stl_accumulate();
    test_iterator_stl_find();
    test_iterator_stl_copy_block();
    test_iterator_range_for_row_view();
    test_iterator_range_for_column_view();
    test_iterator_range_for_block_view();
    test_iterator_const_range_for_block_view();

    std::cout << "All MatrixView tests passed!\n";
    return 0;
}
