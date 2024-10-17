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
	TDynamicVector<int> v(3);
	v[0] = 5;
	v[1] = 4;
	v[2] = 10;
	TDynamicVector<int> v1 = v;
	EXPECT_EQ(5, v1[0]);
	EXPECT_EQ(4, v1[1]);
	EXPECT_EQ(10, v1[2]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(v1);
	EXPECT_NE(&v1[0], &v2[0]);
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
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-3) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(6);
	ASSERT_ANY_THROW(v.at(8) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(7);
	v = v;
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(8);
	TDynamicVector<int> v2(8);
	v1 = v2;
	EXPECT_EQ(8, v1.size());
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(9);
	TDynamicVector<int> v2(15);
	v1 = v2;
	EXPECT_EQ(15, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v1[0] = 1;
	v1[1] = 3;
	v1[2] = 5;
	v2 = v1;
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(3, v2[1]);
	EXPECT_EQ(5, v2[2]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<double> v1(4), v2(4);
	v1[0] = 1.0; v2[0] = 1.0;
	v1[1] = 11.1; v2[1] = 11.1;
	v1[2] = 15.3; v2[2] = 15.3;
	v1[3] = 2.5; v2[3] = 2.5;
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<double> v1(3);
	v1[0] = 3;
	EXPECT_EQ(true, v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<double> v(4), vv(6);
	EXPECT_FALSE(v == vv);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	v[0] = 9;
	v[1] = 8;
	v[2] = 7;
	v[3] = 6;
	v[4] = 5;
	v = v + 5;
	EXPECT_EQ(14, v[0]);
	EXPECT_EQ(13, v[1]);
	EXPECT_EQ(12, v[2]);
	EXPECT_EQ(11, v[3]);
	EXPECT_EQ(10, v[4]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	v[0] = 9;
	v[1] = 8;
	v[2] = 7;
	v[3] = 6;
	v[4] = 5;
	v = v - 4;
	EXPECT_EQ(5, v[0]);
	EXPECT_EQ(4, v[1]);
	EXPECT_EQ(3, v[2]);
	EXPECT_EQ(2, v[3]);
	EXPECT_EQ(1, v[4]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	v[0] = 9;
	v[1] = 8;
	v[2] = 7;
	v[3] = 6;
	v[4] = 5;
	v = v * 6;
	EXPECT_EQ(54, v[0]);
	EXPECT_EQ(48, v[1]);
	EXPECT_EQ(42, v[2]);
	EXPECT_EQ(36, v[3]);
	EXPECT_EQ(30, v[4]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), v3(3);
	v1[0] = 10; v2[0] = 20;
	v1[1] = 20; v2[1] = 30;
	v1[2] = 30; v2[2] = 40;
	v3 = v1 + v2;
	EXPECT_EQ(30, v3[0]);
	EXPECT_EQ(50, v3[1]);
	EXPECT_EQ(70, v3[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4), v2(3);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), v3(3);
	v1[0] = 10; v2[0] = 20;
	v1[1] = 20; v2[1] = 30;
	v1[2] = 30; v2[2] = 40;
	v3 = v1 - v2;
	EXPECT_EQ(-10, v3[0]);
	EXPECT_EQ(-10, v3[1]);
	EXPECT_EQ(-10, v3[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4), v2(3);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	v1 = v1 + 1;
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(5, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4), v2(2);
	ASSERT_ANY_THROW(v1 * v2);
}

