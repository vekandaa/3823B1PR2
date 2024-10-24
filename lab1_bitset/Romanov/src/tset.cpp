// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{

}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
}

TSet::operator TBitField()
{
    return 0;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return BitField.GetLength();
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
    if (this != &s) {
        BitField = s.BitField;
    }
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
    TSet res(GetMaxPower());
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet res(GetMaxPower());
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(GetMaxPower());
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        int bit;
        istr >> bit;
        if (bit) {
            s.InsElem(i);
        }
        else {
            s.DelElem(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << "{ ";
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    ostr << "}";
    return ostr;
}