#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(m);

  EXPECT_EQ((m1 == m), true);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(m);

  EXPECT_NE(&m, &m1);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);

  EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(5);
  m[0][1] = 3;

  EXPECT_EQ(3, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
 
  ASSERT_ANY_THROW(m.at(3).at(-2) = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
 
  ASSERT_ANY_THROW(m.at(3).at(MAX_VECTOR_SIZE + 1) = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
    }
  }
  m = m;

  EXPECT_NE(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  size_t size_mat = 5;
  TDynamicMatrix<int> m(size_mat);
  TDynamicMatrix<int> m1(size_mat);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m1[i][j] = i + j;
    }
  }
  m = m1;

  EXPECT_NE(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(6);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m1[i][j] = i + j;
    }
  }
  m = m1;

  EXPECT_EQ(6, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(6);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m1[i][j] = i + j;
    }
  }
  m = m1;

  EXPECT_NE(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  size_t size_mat = 5;
  TDynamicMatrix<int> m(size_mat);
  TDynamicMatrix<int> m1(size_mat);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j;
    }
  }

  EXPECT_EQ(true, (m1 == m));
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(5);

  EXPECT_EQ(true, (m == m));
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(6);

  EXPECT_EQ(false, (m == m1));
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix)  // added
{
  int val = 10;
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(5);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
    }
  }
  
  m1 = m * val;

  EXPECT_EQ(0, m1[0][0]);
  EXPECT_EQ(20, m1[1][1]);
}

TEST(TDynamicMatrix, can_multiply_vector_by_matrix)  // added
{
  TDynamicMatrix<int> m(5);
  TDynamicVector<int> v(5);
  TDynamicVector<int> v1(5);
  for (size_t i = 0; i < m.size(); i++) {
    v[i] = i;
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
    }
  }
  
  v1 = m * v;

  EXPECT_EQ(30, v1[0]);
  EXPECT_EQ(70, v1[4]);  // 0*4 + 1*5 + 2*6 + 3*7 + 4*8 = 70;
}

TEST(TDynamicMatrix, cant_multiply_vector_by_matrix_with_not_equal_size)  // added
{
  TDynamicMatrix<int> m(5);
  TDynamicVector<int> v(6);
  TDynamicVector<int> v1(5);
  for (size_t i = 0; i < m.size(); i++) {
    v[i] = i;
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
    }
  }

  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  size_t size_mat = 5;
  TDynamicMatrix<int> m(size_mat);
  TDynamicMatrix<int> m1(size_mat);
  TDynamicMatrix<int> m2(size_mat);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j + 10;
    }
  }

  m2 = m + m1;
  
  EXPECT_NE(0, m2[0][0]);
  EXPECT_EQ(14, m2[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(6);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j + 10;
    }
  }

  for (size_t i = 5; i < m1.size(); i++) {
    for (size_t j = 5; j < m1.size(); j++) {
      m1[i][j] = i + j + 10;
    }
  }
  
  ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  size_t size_mat = 5;
  TDynamicMatrix<int> m(size_mat);
  TDynamicMatrix<int> m1(size_mat);
  TDynamicMatrix<int> m2(size_mat);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j + 10;
    }
  }

  m2 = m1 - m;
  
  EXPECT_NE(0, m2[0][0]);
  EXPECT_EQ(10, m2[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(5);
  TDynamicMatrix<int> m1(6);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j + 10;
    }
  }

  for (size_t i = 5; i < m1.size(); i++) {
    for (size_t j = 5; j < m1.size(); j++) {
      m1[i][j] = i + j + 10;
    }
  }
  
  ASSERT_ANY_THROW(m1 - m);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)  // added
{
  size_t size_mat = 3;
  TDynamicMatrix<int> m(size_mat);
  TDynamicMatrix<int> m1(size_mat);
  TDynamicMatrix<int> m2(size_mat);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j;
    }
  }
  
  m2 = m * m1;

  EXPECT_EQ(5, m2[0][0]);
  EXPECT_EQ(14, m2[1][1]);  // 1*1 + 2*2 + 3*3 = 14;
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_no_equal_size)  // added
{
  TDynamicMatrix<int> m(3);
  TDynamicMatrix<int> m1(4);
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m.size(); j++) {
      m[i][j] = i + j;
      m1[i][j] = i + j;
    }
  }

  for (size_t i = 3; i < m1.size(); i++) {
    for (size_t j = 3; j < m1.size(); j++) {
      m1[i][j] = i + j;
    }
  }

  ASSERT_ANY_THROW(m1 * m);
}

