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
		throw "cannot create bitfield with length that < 0";
	}
	if (len == 0) {
		BitLen = MemLen = 0;
		pMem = NULL;
		return;
	}
	BitLen = len;
	MemLen = len / sizeof(TELEM) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for(int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen) {
		throw "out of range GetMemIndex";
	}
	return BitLen - n;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM locPos = n % sizeof(TELEM); // позиция в ячейке - на неё будем сдвигать
	TELEM mask = 1<<locPos;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) {
		throw "gg";
	}
	TELEM otstup = MemLen - (n / sizeof(TELEM)) - 1; // в какой ячейке справа надо искать бит
	TELEM locPos = n % sizeof(TELEM); // позиция в ячейке - на неё будем сдвигать
	pMem[otstup] |= 1<<locPos;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) {
		throw "gg";
	}
	TELEM otstup = MemLen - (n / sizeof(TELEM)) - 1; // в какой ячейке справа надо искать бит
	TELEM locPos = n % sizeof(TELEM); // позиция в ячейке - на неё будем сдвигать
	pMem[otstup] &= (TELEM(-1) ^ 1<<locPos);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
		throw "gg";
	}
	TELEM otstup = MemLen - (n / sizeof(TELEM)) - 1; // в какой ячейке справа надо искать бит
	TELEM locPos = n % sizeof(TELEM); // позиция в ячейке - на неё будем сдвигать
	return ((pMem[otstup] & 1<<locPos) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (bf.MemLen > this->MemLen) {
		if (pMem != NULL)  {
			delete[] pMem;
		}
		this->BitLen = bf.BitLen;
		this->MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	else {
		int i = 0;
		while (i < bf.MemLen) {
			pMem[MemLen - i - 1] = bf.pMem[bf.MemLen - i - 1];
			i++;
		}
		while (i < MemLen) {
			pMem[MemLen - i - 1] = 0;
			i++;
		}
		BitLen = bf.GetLength();
	}
	return *this;
}

/*
a slight issue:

in our sight (assuming indexes in bitfields start from the right according to the model):
buf: |___|___|___|___|___|___|___|___|___|___|
	   ^max.MemLen - 1	   ^min.MemLen - 1 ^0
max: |___|___|___|___|___|___|___|___|___|___|
	   ^max.MemLen - 1	   ^min.MemLen - 1 ^0
min:  					 |___|___|___|___|___|
						   ^min.MemLen - 1  ^0

in memory (how the cells are numerated in arrays):
buf: |___|___|___|___|___|___|___|___|___|___|
	   ^0			   ^min.MemLen - 1     ^max.memLen - 1
max: |___|___|___|___|___|___|___|___|___|___|
	   ^0			   ^min.MemLen - 1     ^max.memLen - 1
min: |___|___|___|___|___|
	   ^0			   ^min.MemLen - 1
*/



/*

Indexes in all operators are going throug arrays as illustrated below:

buf: |___|___|___|___|___|___|___|___|___|___|
	   ^0			   				       ^max.memLen - 1
						   ^<------------index
									(max.MemLen - i - 1)

max: |___|___|___|___|___|___|___|___|___|___|
	   ^0			   				       ^max.memLen - 1
						   ^<------------index
									(max.MemLen - i - 1)

min:					 |___|___|___|___|___|
						   ^0			   ^min.MemLen - 1
						   ^<------------index
									(min.MemLen - i - 1)
All the passed sub-arrays (from the right) remain the same size with min (i goes from 0 to min.MemLen - 1)

According to model:

buf: |___|___|___|___|___|___|___|___|___|___|
	   ^max.MemLen - 1	   ^min.MemLen - 1 ^0
						   ^<------------index

max: |___|___|___|___|___|___|___|___|___|___|
	   ^max.MemLen - 1	   ^min.MemLen - 1 ^0
						   ^<------------index

min:  					 |___|___|___|___|___|
						   ^min.MemLen - 1 ^0
						   ^<------------index


*/

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	const TBitField &min = (this->BitLen < bf.GetLength() ? *this : bf ), &max = (this->BitLen >= bf.GetLength() ? *this : bf );
	bool ans = true;
	int i = 0;
	while (i < min.MemLen) {
		ans &= max.pMem[max.MemLen - i - 1] == min.pMem[min.MemLen - i - 1];
		i++;
	}
	while (i < max.MemLen) {
		ans &= max.pMem[max.MemLen - i - 1] == 0;
		i++;
	}
	return ans;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	const TBitField &min = (this->BitLen < bf.GetLength() ? *this : bf ), &max = (this->BitLen >= bf.GetLength() ? *this : bf );
	bool ans = true;
	int i = 0;
	while (i < min.MemLen) {
		ans |= max.pMem[max.MemLen - i - 1] != min.pMem[min.MemLen - i - 1];
		i++;
	}
	while (i < max.MemLen) {
		ans |= max.pMem[max.MemLen - i - 1] != 0;
		i++;
	}
	return ans;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	const TBitField &min = (this->BitLen < bf.GetLength() ? *this : bf ), &max = (this->BitLen >= bf.GetLength() ? *this : bf );
	TBitField buf(max);
	int i = 0;
	while (i < min.MemLen) {
		buf.pMem[max.MemLen - i - 1] = max.pMem[max.MemLen - i - 1] | min.pMem[min.MemLen - i - 1];
		i++;
	}
	return buf;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	const TBitField &min = (this->BitLen < bf.BitLen ? *this : bf ), &max = (this->BitLen >= bf.BitLen ? *this : bf );
	TBitField buf(max.BitLen);
	int i = 0;
	while (i < min.MemLen) {
		buf.pMem[max.MemLen - i - 1] = max.pMem[max.MemLen - i - 1] & min.pMem[min.MemLen - i - 1];
		i++;
	}
	return buf;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField buf(*this);
	for (int i = 0; i < BitLen; i++) {
		if (GetBit(i)) {
			buf.ClrBit(i);
		}
		else {
			buf.SetBit(i);
		}
	}
	return buf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int m;
	istr >> m;
	TBitField buf(m);
	TELEM r;
	for (int i = 0; i < m; i++) {
		istr >> r;
		if (r == 1) {
			buf.SetBit(i);
		}
	}
	bf = buf;
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int m = 0; m < bf.GetLength(); m++)
			ostr << bf.GetBit(m) << " ";
}