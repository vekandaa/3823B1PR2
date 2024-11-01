#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5)); // вектор нормальной длины
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));  // вектор большей длины
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));  // вектор отрицательной длины
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);                   // создаем вектор
	ASSERT_NO_THROW(TDynamicVector<int> v1(v));  // проверяем копирование
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < 10; i++) {
		v1[i] = i + 1;
	}
	TDynamicVector<int> v2(v1);                  // копируем элементы
	EXPECT_EQ(v1.size(), v2.size());             // проверяем  равенство длин
	for (size_t i = 0; i < v1.size(); i++) {     // равенство элементов
		EXPECT_EQ(v1[i], v2[i]);
	}
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < 10; i++) {
		v1[i] = i + 1;
	}
	TDynamicVector<int> v2(v1);
	v1[0] = 10;                // изменяем элемент
	EXPECT_NE(v1[0], v2[0]);   // проверяем что не равны
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v1(10);
	EXPECT_EQ(v1.size(), 10);   // сверяем полученный размер
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(10);
	for (size_t i = 0; i < v.size(); i++) {         // устанавливаем элементы
		v[i] = static_cast<int>(i) + 1;             // (преобразование size_t в int)
	}
	for (size_t i = 0; i < v.size(); i++) {         // проверяем что установили верно
		EXPECT_EQ(v[i], static_cast<int>(i) + 1);
	}
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	EXPECT_THROW(v.at(-1) = 10, out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	EXPECT_THROW(v.at(6) = 10, out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself)  // самоприсваивание
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = static_cast<int>(i);
	}
	ASSERT_NO_THROW(v = v);   // присвоение самому себе без ошибки
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) // присваивание векторов равного размера
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i) * 2;
	}
	ASSERT_NO_THROW(v2 = v1);      // проверка копирования 1 в 2
	for (size_t i = 0; i < v2.size(); i++) {
		EXPECT_EQ(v2[i], v1[i]);   // проверка корректности элементов
	}
}

TEST(TDynamicVector, assign_operator_change_vector_size)  // изменяем размер вектора
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);
	v1 = v2;
	EXPECT_EQ(v1.size(), 10);  // проверяем что 1 присвоился размер 2
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);
	}
	for (size_t i = 0; i < v2.size(); ++i) {
		v2[i] = static_cast<int>(i) * 2;
	}
	ASSERT_NO_THROW(v1 = v2);                 // присваиваем 2 в 1
	EXPECT_EQ(v1.size(), v2.size());          // сравниваем размеры
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], v2[i]);              // проверяем элементы
	}
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < v1.size(); i++) {  // заполняем одним и тем же
		v1[i] = static_cast<int>(i);
		v2[i] = static_cast<int>(i);
	}
	EXPECT_TRUE(v1 == v2);  // проверяем что одинаковые
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) // самопроверка
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = static_cast<int>(i);
	}
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i);
	}
	EXPECT_FALSE(v1 == v2);  // проверяем что не равны по размеру
}

TEST(TDynamicVector, can_add_scalar_to_vector) // сложение с константой
{
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = static_cast<int>(i);      // [0,1,2]
	}
	TDynamicVector<int> result = v + 5;
	EXPECT_EQ(result[0], 5);
	EXPECT_EQ(result[1], 6);
	EXPECT_EQ(result[2], 7);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)  // разность с константой
{
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = static_cast<int>(i) + 5; // [5,6,7]
	}
	TDynamicVector<int> result = v - 3;
	EXPECT_EQ(result[0], 2);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 4);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = static_cast<int>(i) + 1;  // [1,2,3]
	}
	TDynamicVector<int> result = v * 5;
	EXPECT_EQ(result[0], 5);
	EXPECT_EQ(result[1], 10);
	EXPECT_EQ(result[2], 15);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)  // складываем равные по размеру вектора
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);      // [0,1,2]
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 2;  // [2,3,4]
	}
	TDynamicVector<int> result = v1 + v2;
	EXPECT_EQ(result[0], 0 + 2);  // 0 + 2 = 2
	EXPECT_EQ(result[1], 1 + 3);  // 1 + 3 = 4
	EXPECT_EQ(result[2], 2 + 4);  // 2 + 4 = 6
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 2;
	}
	EXPECT_THROW(v1 + v2, out_of_range);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i) + 5;  // [5,6,7]
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 1;  // [1,2,3]
	}
	TDynamicVector<int> result = v1 - v2;
	EXPECT_EQ(result[0], 5 - 1);  // 5 - 1 = 4
	EXPECT_EQ(result[1], 6 - 2);  // 6 - 2 = 4
	EXPECT_EQ(result[2], 7 - 3);  // 7 - 3 = 4
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 2;
	}
	EXPECT_THROW(v1 - v2, out_of_range);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i) + 5;  // [5,6,7]
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 1;  // [1,2,3]
	}
	int result = v1 * v2;
	EXPECT_EQ(result, 38);  // (1*5 + 2*6 + 3*7 = 5 + 12 + 21 = 38)
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = static_cast<int>(i);
	}
	for (size_t i = 0; i < v2.size(); i++) {
		v2[i] = static_cast<int>(i) + 2;
	}
	EXPECT_THROW(v1 * v2, out_of_range);
}

