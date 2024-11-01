#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(10);
    TDynamicVector<int> v1(v);
    ASSERT_EQ(v1,v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++)
        v[i] = i;
    TDynamicVector<int> v1(v);
    v1[0] = 100;  // Изменим элемент скопированного вектора
    EXPECT_NE(v[0], v1[0]); 
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[4]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1 = v;
    v = v;
    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    int m1[] = {1,2,3,4};
    int m2[] = { 5,6,7,8 };
    TDynamicVector<int> v(m1, 4);
    TDynamicVector<int> v1(m2,4);
    v1 = v;
    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v(6), v1(4);
    v1 = v;
    ASSERT_EQ(v1.size(), 6);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v(6), v1(4);
    ASSERT_NO_THROW(v1 = v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    int m1[] = { 1,2,3,4 };
    int m2[] = { 1,2,3,4 };
    TDynamicVector<int> v(m1, 4);
    TDynamicVector<int> v1(m2, 4);
    ASSERT_TRUE(v == v1);

}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(4);
    ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    ASSERT_FALSE(v == v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    int m1[] = { 1, 2, 3, 4 };
    TDynamicVector<int> v(m1, 4);
    v = v + 4;
    int m2[] = { 5, 6, 7, 8 };
    TDynamicVector<int> v1(m2, 4);
    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    int m1[] = { 1, 2, 3, 4 };
    TDynamicVector<int> v(m1, 4);
    v = v - 4;
    int m2[] = { -3, -2, -1, 0 };
    TDynamicVector<int> v1(m2, 4);
    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    int m1[] = { 1, 2, 3, 4 };
    TDynamicVector<int> v(m1, 4);
    v = v * 4;
    int m2[] = { 4, 8, 12, 16 };
    TDynamicVector<int> v1(m2, 4);
    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    int m1[] = { 1,2,3,4 };
    int m2[] = { 1,2,3,4 };
    TDynamicVector<int> v(m1, 4);
    TDynamicVector<int> v1(m2, 4);
    TDynamicVector<int>  v2 = v1 + v;
    int m3[] = { 2, 4, 6, 8 };
    TDynamicVector<int> v3(m3, 4);
    ASSERT_EQ(v3, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(4);
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    int m1[] = { 1,2,3,4 };
    int m2[] = { 1,2,3,4 };
    TDynamicVector<int> v(m1, 4);
    TDynamicVector<int> v1(m2, 4);
    TDynamicVector<int>  v2 = v1 - v;
    int m3[] = { 0, 0, 0, 0 };
    TDynamicVector<int> v3(m3, 4);
    ASSERT_EQ(v3, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(4);
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    int m1[] = { 1,2,3,4 };
    int m2[] = { 1,2,3,4 };
    TDynamicVector<int> v(m1, 4);
    TDynamicVector<int> v1(m2, 4);
    int res = v1 * v;
    int expected_res = 30;
    ASSERT_EQ(res, expected_res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3), v2(4);
    ASSERT_ANY_THROW(v1 * v2);
}

