// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#define ONE_MEM_BITS (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len >= 0) {
		BitLen = len;
		MemLen = BitLen / ONE_MEM_BITS + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
	else throw "Negative len";
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
	return (n / ONE_MEM_BITS);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= 0 || n < BitLen) {
		return (1 << (n % ONE_MEM_BITS));
	}
	else throw "N is out of range";
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen) {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else throw "N is out of range";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen) {
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else throw "N is out of range";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen) {
		if (pMem[GetMemIndex(n)] & GetMemMask(n)) {
			return 1;
		}
		else return 0;
	}
	else throw "N is out of range";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
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
	int flag, bl, lb;

	if (BitLen > bf.BitLen) {
		flag = 0;
		bl = BitLen;
		lb = bf.BitLen;
	}
	else {
		flag = 1;
		bl = bf.BitLen;
		lb = BitLen;
	}

	TBitField temp(bl);

	for (int i = 0; i <= GetMemIndex(lb); i++) {
		temp.pMem[i] = bf.pMem[i] | pMem[i];
	}

	for (int i = GetMemIndex(lb) + 1; i < temp.MemLen; i++) {
		if (flag == 1) {
			temp.pMem[i] = bf.pMem[i];
		}
		else {
			temp.pMem[i] = pMem[i];
		}
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int length = std::max(BitLen, bf.BitLen);
	TBitField temp(length);

	for (int i = 0; i < temp.MemLen; i++) {
		TELEM thisValue = 0;
		TELEM bfValue = 0;
		if (i < MemLen) {
			thisValue = pMem[i];
		}
		if (i < bf.MemLen) {
			bfValue = bf.pMem[i];
		}
		temp.pMem[i] = thisValue & bfValue;
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < temp.MemLen - 1; i++) {
		temp.pMem[i] = ~temp.pMem[i];
	}
	for (int i = (temp.MemLen - 1) * ONE_MEM_BITS; i < temp.BitLen; i++) {
		if (temp.GetBit(i) == 1) {
			temp.ClrBit(i);
		}
		else {
			temp.SetBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int length;
	TELEM value;

	istr >> length;
	bf = TBitField(length);

	for (int i = 0; i < bf.MemLen; i++) {
		istr >> value;
		bf.pMem[i] = value;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	ostr << bf.BitLen << " ";

	for (int i = 0; i < bf.MemLen; i++) {
		ostr << bf.pMem[i] << " ";
	}
	return ostr;
}
