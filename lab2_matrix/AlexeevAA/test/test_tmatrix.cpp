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
  TDynamicMatrix<int> t(5);
  TDynamicMatrix<int> t2(t);

  EXPECT_EQ(t,t2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> a1(3);
	TDynamicMatrix<int> a2(a1);

	a1[0][0] = 3;

	ASSERT_EQ(a1,a2);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_NO_THROW(m[3][3]);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1;
  EXPECT_EQ(m[0][0], 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_ANY_THROW(m[0][-1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_ANY_THROW(m[0][100]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(4);
  EXPECT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(4);
  TDynamicMatrix<int> m1(4);
  EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(4);
  TDynamicMatrix<int> m1(5);
  m = m1;
  ASSERT_NO_THROW(m[4][4]);
  }

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(4);
  TDynamicMatrix<int> m1(5);
  ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
      m1[i][j] = 1;
    }
  }
  EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
    }
  }
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(4);
  EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
      m1[i][j] = 1;
    }
  }
  EXPECT_NO_THROW(m + m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(4);
  TDynamicMatrix<int> m1(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
      m1[i][j] = 1;
    }
  }
  EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
      m1[i][j] = 1;
    }
  }
  EXPECT_NO_THROW(m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(4);
  TDynamicMatrix<int> m1(2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2;j++){
      m[i][j] = 1;
      m1[i][j] = 1;
    }
  }
  EXPECT_ANY_THROW(m - m1);
}

