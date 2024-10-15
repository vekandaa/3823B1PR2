// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

//// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}


TSet::operator TBitField() { return BitField; }

int TSet::GetMaxPower(void) const 
{
    return MaxPower;
}

// элемент множества
int TSet::IsMember(const int Elem) const 
{
    return BitField.GetBit(Elem);
}

// включение элемента множества
void TSet::InsElem(const int Elem) 
{
    BitField.SetBit(Elem);
}

// исключение элемента множества
void TSet::DelElem(const int Elem) 
{
    BitField.ClrBit(Elem);
}

// присваивание
TSet& TSet::operator=(const TSet &s) 
{
    MaxPower = s.MaxPower;
    BitField = TBitField(s.BitField);
    return *this;
}

// сравнение
int TSet::operator==(const TSet &s) const 
{
    return BitField == s.BitField;
}


int TSet::operator!=(const TSet &s) const 
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s)
{
    return TSet(BitField|(s.BitField));
}

// объединение с элементом
TSet TSet::operator+(const int Elem) 
{
    TSet tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

// разность с элементом
TSet TSet::operator-(const int Elem) 
{
    TSet tmp(*this);
    tmp.DelElem(Elem);
    return tmp;    
}

 // пересечение
TSet TSet::operator*(const TSet &s) 
{
    return TSet(BitField & (s.BitField));
}

// дополнение
TSet TSet::operator~(void) 
{
    return TSet(~BitField);
}

istream &operator>>(istream &istr, TSet &s)
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) 
{
    ostr << s.BitField;
    return ostr;
}

