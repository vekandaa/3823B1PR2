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

  EXPECT_EQ((v1 == v), true);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(v);

  EXPECT_NE(&v, &v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)  // was off for some reason
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);
 
  ASSERT_ANY_THROW(v.at(-2) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);
 
  ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE + 1) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(10);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
  }
  v = v;

  EXPECT_NE(1, v[0]);
  EXPECT_EQ(9, v[9]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  size_t size_vec = 10;
  TDynamicVector<int> v(size_vec);
  TDynamicVector<int> v1(size_vec);
  for (size_t i = 0; i < v1.size(); i++) {
    v1[i] = i;
  }
  v = v1;

  EXPECT_NE(1, v[0]);
  EXPECT_EQ(9, v[9]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(12);
  for (size_t i = 0; i < v1.size(); i++) {
    v1[i] = i;
  }
  v = v1;

  EXPECT_EQ(12, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(12);
  for (size_t i = 0; i < v1.size(); i++) {
    v1[i] = i;
  }
  v = v1;

  EXPECT_NE(1, v[0]);
  EXPECT_EQ(11, v[11]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  size_t size_vec = 10;
  TDynamicVector<int> v(size_vec);
  TDynamicVector<int> v1(size_vec);
  for (size_t i = 0; i < v1.size(); i++) {
    v[i] = i;
    v1[i] = i;
  }

  EXPECT_EQ(true, (v1 == v));
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(10);

  EXPECT_EQ(true, (v == v));
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(12);

  EXPECT_EQ(true, (v != v1));
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  int val = 10;
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(10);
  for (size_t i = 0; i < v.size(); i++) {
      v[i] = i;
    }
  
  v1 = v + val;

  EXPECT_NE(11, v1[0]);
  EXPECT_EQ(19, v1[9]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  int val = 10;
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(10);
  for (size_t i = 0; i < v.size(); i++) {
      v[i] = i;
    }
  
  v1 = v - val;

  EXPECT_NE(11, v1[0]);
  EXPECT_EQ(-1, v1[9]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  int val = 10;
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(10);
  for (size_t i = 0; i < v.size(); i++) {
      v[i] = i;
  }
  
  v1 = v * val;

  EXPECT_EQ(0, v1[0]);
  EXPECT_EQ(90, v1[9]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  size_t size_vec = 10;
  TDynamicVector<int> v(size_vec);
  TDynamicVector<int> v1(size_vec);
  TDynamicVector<int> v2(size_vec);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
    v1[i] = i + 10;
  }

  v2 = v + v1;
  
  EXPECT_NE(0, v2[0]);
  EXPECT_EQ(28, v2[9]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
    v1[i] = i + 10;
  }
  v1[10] = 20;
  
  ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  size_t size_vec = 10;
  TDynamicVector<int> v(size_vec);
  TDynamicVector<int> v1(size_vec);
  TDynamicVector<int> v2(size_vec);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i + 10;
    v1[i] = i;
  }

  v2 = v - v1;
  
  EXPECT_NE(11, v2[1]);
  EXPECT_EQ(10, v2[9]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
    v1[i] = i + 10;
  }
  v1[10] = 20;
  
  ASSERT_ANY_THROW(v1 - v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  size_t size_vec = 10;
  TDynamicVector<int> v(size_vec);
  TDynamicVector<int> v1(size_vec);
  TDynamicVector<int> v2(size_vec);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
    v1[i] = i + 10;
  }
  
  EXPECT_EQ(735, (v * v1));  // 0*10 + 1*11 + 2*12 + 3*13 + 4*14 + 5*15 + 6*16 + 7*17 + 8*18 + 9*19 = 735;
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = i;
    v1[i] = i + 10;
  }
  v1[10] = 20;
  
  ASSERT_ANY_THROW(v * v1);
}

