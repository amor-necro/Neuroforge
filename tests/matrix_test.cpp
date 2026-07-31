#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include "math/matrix.hpp"

using neuroforge::math::Matrix;


// Rule of Five: static properties

static_assert(std::is_copy_constructible_v<Matrix<int>>);
static_assert(std::is_copy_assignable_v<Matrix<int>>);
static_assert(std::is_move_constructible_v<Matrix<int>>);
static_assert(std::is_move_assignable_v<Matrix<int>>);
static_assert(std::is_nothrow_move_constructible_v<Matrix<int>>);
static_assert(std::is_nothrow_move_assignable_v<Matrix<int>>);
static_assert(std::is_destructible_v<Matrix<int>>);


// Default Constructor


void test_default_constructor()
{
   Matrix<int> A;

    assert(A.rows() == 0);
    assert(A.cols() == 0);
    assert(A.size() == 0);
    assert(A.empty());
}


// Size Constructor

void test_size_constructor()
{
}


// Fill Constructor


void test_fill_constructor()
{
}


// Element Access


void test_element_access()
{
}


// Corner Elements


void test_corner_elements()
{
}


// Large Matrix

void test_large_matrix()
{
}


// Rule of Five: Copy Constructor


void test_copy_constructor()
{
    Matrix<int> A(2, 3, 5);

    Matrix<int> B(A);

    assert(B.rows() == 2);
    assert(B.cols() == 3);
    assert(B.size() == 6);

    for (std::size_t row = 0; row < A.rows(); ++row)
    {
        for (std::size_t col = 0; col < A.cols(); ++col)
        {
            assert(B(row, col) == A(row, col));
        }
    }

    B(0, 0) = 99;
    B(1, 2) = 99;
    assert(A(0, 0) == 5);
    assert(A(1, 2) == 5);
}


void test_copy_constructor_empty()
{
    Matrix<int> A;

    Matrix<int> B(A);

    assert(B.rows() == 0);
    assert(B.cols() == 0);
    assert(B.size() == 0);
    assert(B.empty());
}


void test_copy_constructor_nontrivial_element()
{
    Matrix<std::string> A(1, 2, "hello");

    Matrix<std::string> B(A);

    assert(B(0, 0) == "hello");
    assert(B(0, 1) == "hello");

    B(0, 0) = "world";
    assert(A(0, 0) == "hello");
}


// Rule of Five: Copy Assignment


void test_copy_assignment()
{
    Matrix<int> A(2, 2, 7);
    Matrix<int> B(1, 1, 1);

    B = A;

    assert(B.rows() == 2);
    assert(B.cols() == 2);
    assert(B.size() == 4);

    for (std::size_t row = 0; row < B.rows(); ++row)
    {
        for (std::size_t col = 0; col < B.cols(); ++col)
        {
            assert(B(row, col) == 7);
        }
    }

    B(0, 0) = 42;
    assert(A(0, 0) == 7);
}


void test_copy_assignment_grows_target()
{
    Matrix<int> A(3, 3, 5);
    Matrix<int> B(1, 1, 0);

    B = A;

    assert(B.rows() == 3);
    assert(B.cols() == 3);
    assert(B(2, 2) == 5);
}


void test_copy_assignment_empty()
{
    Matrix<int> A;
    Matrix<int> B(2, 3, 4);

    B = A;

    assert(B.rows() == 0);
    assert(B.cols() == 0);
    assert(B.empty());
}


void test_self_assignment()
{
    Matrix<int> A(2, 2, 3);

    A = A;

    assert(A.rows() == 2);
    assert(A.cols() == 2);
    assert(A(0, 0) == 3);
    assert(A(1, 1) == 3);
}


// Rule of Five: Move Constructor


void test_move_constructor()
{
    Matrix<int> A(2, 3, 4);

    Matrix<int> B(std::move(A));

    assert(B.rows() == 2);
    assert(B.cols() == 3);
    assert(B.size() == 6);
    assert(B(0, 0) == 4);
    assert(B(1, 2) == 4);

    assert(A.empty());
}


void test_moved_from_reuse()
{
    Matrix<int> A(2, 2, 9);

    Matrix<int> B(std::move(A));
    assert(B(1, 1) == 9);

    A = Matrix<int>(1, 1, 7);
    assert(A.rows() == 1);
    assert(A.cols() == 1);
    assert(A(0, 0) == 7);
}


// Rule of Five: Move Assignment


void test_move_assignment()
{
    Matrix<int> A(2, 2, 3);
    Matrix<int> B(1, 1, 1);

    B = std::move(A);

    assert(B.rows() == 2);
    assert(B.cols() == 2);
    assert(B(0, 0) == 3);
    assert(B(1, 1) == 3);

    assert(A.empty());
}


void test_move_assignment_resizes()
{
    Matrix<int> A(3, 3, 9);
    Matrix<int> B(2, 2, 2);

    B = std::move(A);

    assert(B.rows() == 3);
    assert(B.cols() == 3);
    assert(B(2, 2) == 9);

    A = Matrix<int>(2, 2, 5);
    assert(A(0, 1) == 5);
}


int main()
{
    test_default_constructor();
    test_copy_constructor();
    test_copy_constructor_empty();
    test_copy_constructor_nontrivial_element();
    test_copy_assignment();
    test_copy_assignment_grows_target();
    test_copy_assignment_empty();
    test_self_assignment();
    test_move_constructor();
    test_moved_from_reuse();
    test_move_assignment();
    test_move_assignment_resizes();

    std::cout << "All Matrix Rule of Five tests passed!\n";
    return 0;
}