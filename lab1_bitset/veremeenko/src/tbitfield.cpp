// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле


#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
    if (len < 0) throw std::invalid_argument("Incorrect");
    MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}


TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}


TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n > BitLen)) throw std::invalid_argument("Incorrect");
    return n / (8 * sizeof(TELEM));
}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n > BitLen)) throw std::invalid_argument("Incorrect");
    TELEM result = (1 << (n % (sizeof(TELEM) * 8)));
    return result;
}

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen)) throw std::invalid_argument("Incorrect");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen)) throw std::invalid_argument("Incorrect");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen)) throw std::invalid_argument("Incorrect");

    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0) return 1;
    else return 0;
    
}


TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) != bf.GetBit(i)) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) != bf.GetBit(i))
            return 1;
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField result = (BitLen > bf.BitLen)?*this : bf;
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
    {
        result.pMem[i] = pMem[i] |= bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{   
    TBitField result(max(BitLen, bf.BitLen));
    for(int i = 0; i < min(MemLen, bf.MemLen); i++)
    {
        result.pMem[i] = bf.pMem[i] & pMem[i];
    }
    return result;
}


TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i)) result.ClrBit(i);
        else result.SetBit(i);
    return result;
}


// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf)
{
    int bit = 0;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        if (bit) 
            bf.SetBit(i);
        else 
            bf.ClrBit(i);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) 
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i) << ' ';
    }
    ostr << '\n';
    return ostr;
}