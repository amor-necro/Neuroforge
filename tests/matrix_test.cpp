#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
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
static_assert(noexcept(std::declval<Matrix<int>&>().clear()));
static_assert(noexcept(std::declval<Matrix<int>&>().swap(std::declval<Matrix<int>&>())));
static_assert(std::is_same_v<Matrix<int>::value_type, int>);
static_assert(std::is_same_v<Matrix<int>::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<Matrix<int>::iterator, std::vector<int>::iterator>);
static_assert(std::is_same_v<Matrix<int>::const_iterator, std::vector<int>::const_iterator>);
static_assert(std::is_same_v<Matrix<int>::reverse_iterator, std::vector<int>::reverse_iterator>);
static_assert(std::is_same_v<Matrix<int>::const_reverse_iterator, std::vector<int>::const_reverse_iterator>);
static_assert(noexcept(std::declval<Matrix<int>&>().begin()));
static_assert(noexcept(std::declval<const Matrix<int>&>().begin()));
static_assert(noexcept(std::declval<Matrix<int>&>().end()));
static_assert(noexcept(std::declval<const Matrix<int>&>().end()));
static_assert(noexcept(std::declval<Matrix<int>&>().rbegin()));
static_assert(noexcept(std::declval<const Matrix<int>&>().rbegin()));
static_assert(noexcept(std::declval<Matrix<int>&>().rend()));
static_assert(noexcept(std::declval<const Matrix<int>&>().rend()));
static_assert(noexcept(std::declval<Matrix<int>&>().cbegin()));
static_assert(noexcept(std::declval<Matrix<int>&>().cend()));
static_assert(noexcept(std::declval<Matrix<int>&>().crbegin()));
static_assert(noexcept(std::declval<Matrix<int>&>().crend()));


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


// Element Access: data()


void test_data_contiguous_row_major()
{
    Matrix<int> A(2, 3, 0);

    for (std::size_t k = 0; k < A.size(); ++k)
    {
        A.data()[k] = static_cast<int>(k);
    }

    assert(A(0, 0) == 0);
    assert(A(0, 1) == 1);
    assert(A(0, 2) == 2);
    assert(A(1, 0) == 3);
    assert(A(1, 1) == 4);
    assert(A(1, 2) == 5);
}


void test_data_matches_operator_paren()
{
    Matrix<int> A(2, 3, 0);

    for (std::size_t row = 0; row < A.rows(); ++row)
    {
        for (std::size_t col = 0; col < A.cols(); ++col)
        {
            assert(&A(row, col) == A.data() + (row * A.cols()) + col);
        }
    }
}


void test_data_const()
{
    Matrix<int> A(2, 2, 7);
    const Matrix<int>& CA = A;

    const int* p = CA.data();

    assert(p[0] == 7);
    assert(p[3] == 7);
}


void test_data_empty()
{
    Matrix<int> A;

    int* p = A.data();

    (void)p;
}


// Element Access: front() and back()


void test_front()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 10;

    assert(A.front() == 10);

    A.front() = 11;
    assert(A(0, 0) == 11);
}


void test_back()
{
    Matrix<int> A(2, 3, 0);
    A(1, 2) = 20;

    assert(A.back() == 20);

    A.back() = 21;
    assert(A(1, 2) == 21);
}


void test_front_back_const()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 10;
    A(1, 2) = 20;

    const Matrix<int>& CA = A;

    assert(CA.front() == 10);
    assert(CA.back() == 20);
}


void test_front_back_single_element()
{
    Matrix<int> A(1, 1, 42);

    assert(A.front() == 42);
    assert(A.back() == 42);

    A.front() = 43;
    assert(A.back() == 43);
}


void test_front_back_shared_storage()
{
    Matrix<int> A(2, 3, 0);
    A(0, 0) = 5;
    A(1, 2) = 9;

    assert(A.front() == A(0, 0));
    assert(A.back() == A(1, 2));

    assert(&A.front() == &A(0, 0));
    assert(&A.back() == &A(1, 2));
}


// Element Access: at()


void test_at_valid()
{
    Matrix<int> A(2, 3, 0);

    for (std::size_t row = 0; row < A.rows(); ++row)
    {
        for (std::size_t col = 0; col < A.cols(); ++col)
        {
            A.at(row, col) = static_cast<int>(row * A.cols() + col);
        }
    }

    for (std::size_t row = 0; row < A.rows(); ++row)
    {
        for (std::size_t col = 0; col < A.cols(); ++col)
        {
            assert(A.at(row, col) == static_cast<int>(row * A.cols() + col));
            assert(A.at(row, col) == A(row, col));
        }
    }

    const Matrix<int>& CA = A;
    assert(CA.at(1, 2) == 5);
}


void test_at_throws_out_of_range()
{
    Matrix<int> A(2, 3, 1);

    bool threw = false;
    try
    {
        A.at(2, 0);
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }
    assert(threw);

    threw = false;
    try
    {
        A.at(0, 3);
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }
    assert(threw);

    threw = false;
    try
    {
        A.at(2, 3);
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }
    assert(threw);
}


void test_at_empty_throws()
{
    Matrix<int> A;

    bool threw = false;
    try
    {
        A.at(0, 0);
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }
    assert(threw);
}


void test_at_throws_const()
{
    Matrix<int> A(1, 1, 1);
    const Matrix<int>& CA = A;

    bool threw = false;
    try
    {
        CA.at(1, 0);
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }
    assert(threw);
}


// Modifiers: fill()


void test_fill_basic()
{
    Matrix<int> A(2, 3, 0);
    A.fill(7);
    assert(A(0, 0) == 7);
    assert(A(0, 1) == 7);
    assert(A(0, 2) == 7);
    assert(A(1, 0) == 7);
    assert(A(1, 1) == 7);
    assert(A(1, 2) == 7);
}


void test_fill_overwrites_existing()
{
    Matrix<int> A(2, 2, 1);
    A.fill(9);
    assert(A(0, 0) == 9);
    assert(A(0, 1) == 9);
    assert(A(1, 0) == 9);
    assert(A(1, 1) == 9);
}


void test_fill_empty()
{
    Matrix<int> A;
    A.fill(1);
    assert(A.empty());
}


void test_fill_nontrivial_type()
{
    Matrix<std::string> A(2, 2, "hello");
    A.fill("world");
    assert(A(0, 0) == "world");
    assert(A(1, 1) == "world");
}


// Modifiers: clear()


void test_clear_populated()
{
    Matrix<int> A(2, 3, 5);
    A.clear();
    assert(A.rows() == 0);
    assert(A.cols() == 0);
    assert(A.size() == 0);
    assert(A.empty());
}


void test_clear_empty()
{
    Matrix<int> A;
    A.clear();
    assert(A.empty());
}


void test_clear_then_reuse()
{
    Matrix<int> A(2, 3, 1);
    A.clear();
    Matrix<int> B(3, 2, 2);
    A = B;
    assert(A.rows() == 3);
    assert(A.cols() == 2);
    assert(A(0, 0) == 2);
    assert(A(2, 1) == 2);
}


// Modifiers: swap()


void test_swap_exchange_contents()
{
    Matrix<int> A(2, 3, 1);
    Matrix<int> B(2, 3, 2);
    A.swap(B);
    assert(A(0, 0) == 2);
    assert(A(1, 2) == 2);
    assert(B(0, 0) == 1);
    assert(B(1, 2) == 1);
}


void test_swap_unequal_dimensions()
{
    Matrix<int> A(2, 3, 1);
    Matrix<int> B(3, 2, 2);
    A.swap(B);
    assert(A.rows() == 3);
    assert(A.cols() == 2);
    assert(A(0, 0) == 2);
    assert(B.rows() == 2);
    assert(B.cols() == 3);
    assert(B(0, 0) == 1);
}


void test_swap_empty_with_populated()
{
    Matrix<int> A;
    Matrix<int> B(2, 2, 7);
    A.swap(B);
    assert(A.rows() == 2);
    assert(A.cols() == 2);
    assert(A(0, 0) == 7);
    assert(B.empty());
}


void test_swap_self()
{
    Matrix<int> A(2, 2, 3);
    A.swap(A);
    assert(A(0, 0) == 3);
    assert(A(1, 1) == 3);
}


// Comparison: operator== and operator!=()


void test_equality_identical_matrices()
{
    Matrix<int> A(2, 3, 5);
    Matrix<int> B(2, 3, 5);
    assert(A == B);
}


void test_inequality_different_values()
{
    Matrix<int> A(2, 3, 5);
    Matrix<int> B(2, 3, 6);
    assert(!(A == B));
    assert(A != B);
}


void test_inequality_different_dimensions()
{
    Matrix<int> A(2, 3, 5);
    Matrix<int> B(3, 2, 5);
    assert(!(A == B));
    assert(A != B);
}


void test_equality_empty_matrices()
{
    Matrix<int> A;
    Matrix<int> B;
    assert(A == B);
}


void test_inequality_empty_vs_populated()
{
    Matrix<int> A;
    Matrix<int> B(1, 1, 1);
    assert(!(A == B));
    assert(A != B);
}


void test_equality_same_total_size_different_layout()
{
    Matrix<int> A(1, 6, 3);
    Matrix<int> B(2, 3, 3);
    assert(!(A == B));
    assert(A != B);
}


void test_inequality_is_negation()
{
    Matrix<int> A(2, 2, 1);
    Matrix<int> B(2, 2, 2);
    assert((A != B) == !(A == B));
    assert((A != A) == !(A == A));
}


// Iterators: type aliases


void test_iterator_type_aliases()
{
    static_assert(std::is_same_v<Matrix<int>::value_type, int>);
    static_assert(std::is_same_v<Matrix<int>::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<Matrix<int>::iterator, std::vector<int>::iterator>);
    static_assert(std::is_same_v<Matrix<int>::const_iterator, std::vector<int>::const_iterator>);
    static_assert(std::is_same_v<Matrix<int>::reverse_iterator, std::vector<int>::reverse_iterator>);
    static_assert(std::is_same_v<Matrix<int>::const_reverse_iterator, std::vector<int>::const_reverse_iterator>);
}


// Iterators: noexcept


void test_iterator_noexcept()
{
    Matrix<int> A(2, 2, 0);
    const Matrix<int>& CA = A;

    (void)A.begin();
    (void)A.end();
    (void)A.rbegin();
    (void)A.rend();
    (void)CA.begin();
    (void)CA.end();
    (void)CA.rbegin();
    (void)CA.rend();
    (void)CA.cbegin();
    (void)CA.cend();
    (void)CA.crbegin();
    (void)CA.crend();
}


// Iterators: range-based for


void test_range_based_for()
{
    Matrix<int> A(2, 3, 1);
    int sum = 0;
    for (int& x : A)
    {
        sum += x;
    }
    assert(sum == 6);
}


// Iterators: std::fill


void test_std_fill()
{
    Matrix<int> A(2, 3, 0);
    std::fill(A.begin(), A.end(), 7);

    for (std::size_t i = 0; i < A.size(); ++i)
    {
        assert(A.data()[i] == 7);
    }
}


// Iterators: std::accumulate


void test_std_accumulate()
{
    Matrix<int> A(2, 3, 3);
    int sum = std::accumulate(A.cbegin(), A.cend(), 0);
    assert(sum == 18);
}


// Iterators: std::copy


void test_std_copy()
{
    Matrix<int> A(2, 3, 0);
    int k = 1;
    for (auto& x : A)
    {
        x = k++;
    }

    std::vector<int> dest(A.size());
    std::copy(A.begin(), A.end(), dest.begin());

    for (std::size_t i = 0; i < A.size(); ++i)
    {
        assert(dest[i] == A.data()[i]);
    }
}


// Iterators: const iteration


void test_const_iteration()
{
    Matrix<int> A(2, 2, 4);
    const Matrix<int>& CA = A;

    int sum = 0;
    for (auto it = CA.cbegin(); it != CA.cend(); ++it)
    {
        sum += *it;
    }
    assert(sum == 16);
}


// Iterators: reverse iteration


void test_reverse_iteration()
{
    Matrix<int> A(1, 5, 0);
    for (std::size_t i = 0; i < A.size(); ++i)
    {
        A.data()[i] = static_cast<int>(i + 1);
    }

    int sum = 0;
    for (auto it = A.rbegin(); it != A.rend(); ++it)
    {
        sum += *it;
    }
    assert(sum == 15);
}


// Iterators: const reverse iteration


void test_const_reverse_iteration()
{
    Matrix<int> A(2, 3, 2);
    const Matrix<int>& CA = A;

    int sum = 0;
    for (auto it = CA.crbegin(); it != CA.crend(); ++it)
    {
        sum += *it;
    }
    assert(sum == 12);
}


// Iterators: empty matrix


void test_empty_matrix_iterators()
{
    Matrix<int> A;
    assert(A.begin() == A.end());
    assert(A.rbegin() == A.rend());
    assert(A.cbegin() == A.cend());
    assert(A.crbegin() == A.crend());
}


// Iterators: single element


void test_single_element_iterators()
{
    Matrix<int> A(1, 1, 42);

    assert(*A.begin() == 42);
    assert(*A.cbegin() == 42);
    assert(*A.rbegin() == 42);
    assert(*A.crbegin() == 42);

    assert(A.begin() + 1 == A.end());
    assert(A.rbegin() + 1 == A.rend());
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
    test_data_contiguous_row_major();
    test_data_matches_operator_paren();
    test_data_const();
    test_data_empty();
    test_front();
    test_back();
    test_front_back_const();
    test_front_back_single_element();
    test_front_back_shared_storage();
    test_at_valid();
    test_at_throws_out_of_range();
    test_at_empty_throws();
    test_at_throws_const();
    test_fill_basic();
    test_fill_overwrites_existing();
    test_fill_empty();
    test_fill_nontrivial_type();
    test_clear_populated();
    test_clear_empty();
    test_clear_then_reuse();
    test_swap_exchange_contents();
    test_swap_unequal_dimensions();
    test_swap_empty_with_populated();
    test_swap_self();
    test_equality_identical_matrices();
    test_inequality_different_values();
    test_inequality_different_dimensions();
    test_equality_empty_matrices();
    test_inequality_empty_vs_populated();
    test_equality_same_total_size_different_layout();
    test_inequality_is_negation();
    test_iterator_type_aliases();
    test_iterator_noexcept();
    test_range_based_for();
    test_std_fill();
    test_std_accumulate();
    test_std_copy();
    test_const_iteration();
    test_reverse_iteration();
    test_const_reverse_iteration();
    test_empty_matrix_iterators();
    test_single_element_iterators();

    std::cout << "All Matrix tests passed!\n";
    return 0;
}