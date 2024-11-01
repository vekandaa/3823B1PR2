// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
using namespace std;

// Конструктор с максимальной мощностью множества
TSet::TSet(int mp) : BitField(mp)
{
	if (mp < 0) throw("mp<0");
	MaxPower = mp;
}

// Конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// Конструктор преобразования типа (из битового поля)
TSet::TSet(const TBitField& bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

// Оператор преобразования множества в битовое поле
TSet::operator TBitField()
{
	return BitField;
}

// Получение максимальной мощности множества
int TSet::GetMaxPower(void) const
{
	return MaxPower;
}

// Проверка, является ли элемент членом множества
int TSet::IsMember(const int Elem) const
{
	if (Elem < 0 || Elem >= MaxPower) throw ("Bad Elem");
	return BitField.GetBit(Elem);
}

// Включение элемента в множество
void TSet::InsElem(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) throw ("Bad Elem");
	return BitField.SetBit(Elem);
}

// Исключение элемента из множества
void TSet::DelElem(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) throw("Bad Elem");
	return BitField.ClrBit(Elem);
}

// Оператор присваивания
TSet& TSet::operator=(const TSet& s)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

// Оператор сравнения на равенство
int TSet::operator==(const TSet& s) const
{
	return(MaxPower == s.MaxPower && BitField == s.BitField);
}

// Оператор сравнения на неравенство
int TSet::operator!=(const TSet& s) const
{
	return(MaxPower != s.MaxPower || BitField != s.BitField);
}

// Объединение множеств
TSet TSet::operator+(const TSet& s)
{
	int _MaxPower = max(MaxPower, s.MaxPower);
	TSet result(_MaxPower);
	result.BitField = BitField | s.BitField;
	return result;	
}

// Объединение множества с элементом
TSet TSet::operator+(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) throw("Bad Elem");
	TSet result(*this);
	result.InsElem(Elem);
	return result;
}

// Разность множества с элементом
TSet TSet::operator-(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) throw("BadElem");
	TSet result(*this);
	result.DelElem(Elem);
	return result;
}

// Пересечение множеств
TSet TSet::operator*(const TSet& s)
{
	int _MaxPower = max(MaxPower, s.MaxPower);
	TSet result(_MaxPower);
	result.BitField = BitField & s.BitField;
	return result;
}

// Дополнение множества
TSet TSet::operator~(void)
{
	TSet result(MaxPower);
	result.BitField = ~BitField;
	return result;
}

// Перегрузка ввода
istream& operator>>(istream& istr, TSet& s)
{
	return istr;
}

// Перегрузка вывода
ostream& operator<<(ostream& ostr, const TSet& s)
{
	return ostr;
}
