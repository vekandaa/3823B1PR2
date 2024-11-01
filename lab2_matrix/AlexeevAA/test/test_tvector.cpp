#include "tmatrix.h"

#include <gtest.h>

typedef int VTYPE;

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<VTYPE> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<VTYPE> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<VTYPE> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<VTYPE> v(10);

  ASSERT_NO_THROW(TDynamicVector<VTYPE> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<VTYPE> v(12);
  TDynamicVector<VTYPE> v2(v);

  EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<VTYPE> v(2);
  TDynamicVector<VTYPE> v1(v);
  v1[0] = 123;
  EXPECT_NE(v,v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<VTYPE> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<VTYPE> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<VTYPE> v(10);
  ASSERT_ANY_THROW(v[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  
  TDynamicVector<VTYPE> v(10);
  ASSERT_ANY_THROW(v[11]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<VTYPE> v;
  ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<VTYPE> v(3);
  TDynamicVector<VTYPE> v2(3);

  EXPECT_NO_THROW(v2 = v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  VTYPE l = 5;
  TDynamicVector<VTYPE> v(l);
  TDynamicVector<VTYPE> v2(14);
  v = v2;

  EXPECT_NE(l, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<VTYPE> v(5);
  TDynamicVector<VTYPE> v2(3);
  EXPECT_NO_THROW(v = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 3;
  TDynamicVector<VTYPE> v1(v);

  EXPECT_EQ(v,v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 3;

  EXPECT_EQ(v,v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 3;
  TDynamicVector<VTYPE> v1(1);
  v1[0] = 8;
  EXPECT_NE(v,v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  EXPECT_NO_THROW(v + 1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  EXPECT_NO_THROW(v - 12);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  EXPECT_NO_THROW(v * 30);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(2);
  v1[0] = 12;
  v[1] = 11;

  EXPECT_NO_THROW(v + v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(1);
  v1[0] = 12;
  EXPECT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(2);
  v1[0] = 12;
  v[1] = 11;

  EXPECT_NO_THROW(v - v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(1);
  v1[0] = 12;
  EXPECT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(2);
  v1[0] = 12;
  v[1] = 11;

  EXPECT_NO_THROW(v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<VTYPE> v(2);
  v[0] = 1;
  v[1] = 121;
  TDynamicVector<VTYPE> v1(1);
  v1[0] = 12;
  EXPECT_ANY_THROW(v * v1);
}

