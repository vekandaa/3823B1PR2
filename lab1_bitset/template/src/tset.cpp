// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)  // конструктор
{
    MaxPower = mp;
}

TSet::TSet(const TSet& s) : BitField(s.BitField)  // конструктор копирования
{
    MaxPower = s.MaxPower;
}

TSet::TSet(const TBitField& bf) : BitField(bf)  // конструктор преобразования типа
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()  // преобразование типа к битовому полю
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
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

TSet& TSet::operator=(const TSet& s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return ((MaxPower == s.MaxPower) && (BitField == s.BitField));
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return ((MaxPower != s.MaxPower) || (BitField != s.BitField));
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TBitField newBitField = BitField | s.BitField;
    return TSet(newBitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TBitField newBitField = BitField & s.BitField;
    return TSet(newBitField);
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~BitField;
    return result;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.BitField;
    return ostr;
}