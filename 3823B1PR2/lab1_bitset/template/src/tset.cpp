// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) 
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.MaxPower)
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= MaxPower)
        return 0;
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0) {
        throw "InsElem Elem < 0";
    }
    if (Elem >= MaxPower) {
        MaxPower = Elem + 1;
        TBitField buf(MaxPower);
        buf = BitField;
        BitField = buf;
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0) {
        throw "DelElem Elem < 0";
    }
    if (Elem < MaxPower) {
        BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (BitField.GetLength() < s.BitField.GetLength()) {
        MaxPower = s.MaxPower;
    }
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet t((BitField.GetLength() > s.BitField.GetLength() ? *this : s));
    const TSet &min = (BitField.GetLength() <= s.BitField.GetLength() ? *this : s);
    for (int i = 0; i < min.BitField.GetLength(); i++) {
        if (min.BitField.GetBit(i)) {
            t.BitField.SetBit(i);
        }
    }
    return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem >= MaxPower) {
        throw "operator+ Elem >= MaxPower";
    }
    TSet buf(*this);
    buf.BitField.SetBit(Elem);
    return buf;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= MaxPower) {
        return *this;
    }
    TSet buf(*this);
    buf.BitField.ClrBit(Elem);
    return buf;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet t((MaxPower <= s.MaxPower ? *this : s));
    const TSet &max = (MaxPower > s.MaxPower ? *this : s);
    for (int i = 0; i < t.BitField.GetLength(); i++) {
        if (!max.BitField.GetBit(i)) {
            t.BitField.ClrBit(i);
        }
    }
    return t;
}

TSet TSet::operator~(void) // дополнение
{
    TSet t(*this);
    for (int i = 0; i < t.MaxPower; i++) {
        if (BitField.GetBit(i)) {
            t.BitField.ClrBit(i);
        }
        else {
            t.BitField.SetBit(i);
        }
    }
    return t;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int m;
    istr >> m;
    TELEM *u = new TELEM[m];
    TELEM mm = 0;
    for (int i = 0; i < m; i++) {
        TELEM t;
        istr >> t;
        u[i] = t;
        mm = max(u[i], mm);
    }
    TSet buf(mm + 1);
    for (int i = 0; i < m; i++) {
        buf.BitField.SetBit(u[i]);
    }
    s = buf;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.BitField.GetBit(i)) {
            ostr << i << "\t";
        }
    }
    return ostr;
}