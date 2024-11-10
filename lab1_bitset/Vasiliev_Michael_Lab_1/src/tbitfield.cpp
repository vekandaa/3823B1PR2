// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) {
		throw std::length_error("len less than zero.");
	}
	BitLen = len;
	MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) {
		throw std::out_of_range("bit is out of range.");
	}
	int mem_ind = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[mem_ind] = pMem[mem_ind] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) {
		throw std::out_of_range("bit is out of range.");
	}
	int mem_ind = GetMemIndex(n);
	TELEM mask = ~GetMemMask(n);
	pMem[mem_ind] = pMem[mem_ind] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) {
		throw std::out_of_range("bit is out of range.");
	}
	int mem_ind = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return (pMem[mem_ind] & mask);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf) {
        return *this;
    }
    if (BitLen != bf.BitLen) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    
	for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
        return 1;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
			return 1;
		}
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len) {
		len = bf.BitLen;
	}
	TBitField temp(len);

	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) {
		temp.pMem[i] |= bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) {
		len = bf.BitLen;
	}
	TBitField temp(len);
	
	int min_MemLen = MemLen;
	if (bf.MemLen < min_MemLen) {
		min_MemLen = bf.MemLen;
	}

	for (int i = 0; i < min_MemLen; i++) {
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);

	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = ~pMem[i];
	}

	int last_index = BitLen % (sizeof(TELEM) * 8);
	if (last_index > 0) {
		TELEM mask = (1 << last_index) - 1;
		temp.pMem[MemLen - 1] &= mask;
	}
	
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++) {
		istr >> bf.pMem[i];
	}
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++) {
        ostr << bf.pMem[i];
    }
    return ostr;
}
