// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp): BitField(1) {
    MaxPower = mp;
    BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf) {
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower() const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower && BitField == s.BitField) return true;
    return false;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower || BitField != s.BitField) return true;
    return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    if (MaxPower > s.MaxPower) {
        TSet a(MaxPower);
        a.BitField = BitField | s.BitField;
        return a;
    }
    else {
        TSet a(s.MaxPower);
        a.BitField = BitField | s.BitField;
        return a;
    }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet a(MaxPower);
    a.BitField.SetBit(Elem);
    return a;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet a(MaxPower);
    a.BitField.ClrBit(Elem);
    return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    if (MaxPower > s.MaxPower) {
        TSet a(MaxPower);
        a.BitField = BitField & s.BitField;
        return a;
    }
    else {
        TSet a(s.MaxPower);
        a.BitField = BitField & s.BitField;
        return a;
    }
    return TSet(1);
}

TSet TSet::operator~() // дополнение
{
    TSet a(MaxPower);
    a.BitField = ~BitField;
    return a;
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
