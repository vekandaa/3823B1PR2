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
	TDynamicMatrix<int> m1(2), m2(m1);
	m1[0][0] = 100; m2[0][0] = 100;
	m1[0][1] = 200; m2[0][1] = 200;
	m1[1][0] = 300; m2[1][0] = 300;
	m1[1][1] = 400; m2[1][1] = 400;
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(5), m2(m1);
	EXPECT_NE(&m1[0], &m2[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	int z = 20;
	ASSERT_NO_THROW(TDynamicMatrix<int> m(z));
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(15);
	m[14][14] = 150;

	EXPECT_EQ(150, m[14][14]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(6);
	ASSERT_ANY_THROW(m[-1][-1] = 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(16);
	ASSERT_ANY_THROW(m[16][3] = 500);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(17);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 100; m2[0][0] = 500;
	m1[0][1] = 200; m2[0][1] = 600;
	m1[1][0] = 300; m2[1][0] = 700;
	m1[1][1] = 400; m2[1][1] = 800;
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3), m2(6);
	m2 = m1;
	ASSERT_NO_THROW(m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3), m2(6);
	
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 2; m2[0][0] = 2;
	m1[0][1] = 2; m2[0][1] = 2;
	m1[1][0] = 2; m2[1][0] = 2;
	m1[1][1] = 2; m2[1][1] = 2;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1;
	m1[0][1] = 1;
	m1[1][0] = 1;
	m1[1][1] = 1;
	EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(4);
	m1[0][0] = 1000; m2[0][0] = 1000;
	m1[0][1] = 1001; m2[0][1] = 1001;
	m1[1][0] = 1002; m2[1][0] = 1002;
	m1[1][1] = 1004; m2[1][1] = 1004;
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 555; m2[0][0] = 666;
	m1[0][1] = 444; m2[0][1] = 777;
	m1[1][0] = 333; m2[1][0] = 888;
	m1[1][1] = 222; m2[1][1] = 999;
	ASSERT_NO_THROW(m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(6);
	m1[0][0] = 555; m2[0][0] = 666;
	m1[0][1] = 444; m2[0][1] = 777;
	m1[1][0] = 333; m2[1][0] = 888;
	m1[1][1] = 222; m2[1][1] = 999;
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 555; m2[0][0] = 666;
	m1[0][1] = 444; m2[0][1] = 777;
	m1[1][0] = 333; m2[1][0] = 888;
	m1[1][1] = 222; m2[1][1] = 999;
	ASSERT_NO_THROW(m2 - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(6);
	m1[0][0] = 555; m2[0][0] = 666;
	m1[0][1] = 444; m2[0][1] = 777;
	m1[1][0] = 333; m2[1][0] = 888;
	m1[1][1] = 222; m2[1][1] = 999;
	ASSERT_ANY_THROW(m2 - m1);
}

