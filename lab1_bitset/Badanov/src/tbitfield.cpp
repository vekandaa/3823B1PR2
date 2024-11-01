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
		throw "Incorrect values";
	}
	else {
		BitLen = len;
	}
	MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];

	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) {
		throw "Incorrect values";
	}

	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) {
		throw "Incorrect values";
	}

	return TELEM(1) << (n % (sizeof(TELEM) * 8));
}


// доступ к битам битового поля

int TBitField::GetLength() const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0) {
		throw "Incorrect values";
	}

	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0) {
		throw "Incorrect values";
	}

	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0) {
		throw "Incorrect values";
	}

	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}


// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{

	if (this != &bf) {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;

		if (pMem != nullptr) {
			delete[]pMem;
		}

		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;

}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{

	int cnt;
	if (BitLen == bf.BitLen ) {
		for(int i = 0; i < MemLen; i++) {
			if (pMem[i] == bf.pMem[i]) {
				cnt++;
			}
		}
		if (cnt == MemLen) return true;
	}
	else return false;
	
	
	
	// if (BitLen != bf.BitLen) {
	// 	return false;
	// }

	// for (int i = 0; i < MemLen; i++) {
	// 	if (pMem[i] != bf.pMem[i]) {
	// 		return false;
	// 	}
	// }

	// return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
	


	// int cnt;
	// if (BitLen == bf.BitLen ) {
	// 	for(int i = 0; i < MemLen; i++) {
	// 		if (pMem[i] != bf.pMem[i]) {
	// 			cnt++;
	// 		}
	// 	}
	// 	if (cnt == MemLen) return true;
	// }
	// else {
	// 	if (BitLen != bf.BitLen) return true;
	// 	else return false;
	// }

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
		temp.pMem[i] = temp.pMem[i] | bf.pMem[i];
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
	/*for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = pMem[i];
	}*/

	for (int i = 0; i < min(bf.MemLen, MemLen); i++) {
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{

	TBitField temp(BitLen);

	for (int i = 0; i < MemLen; i++){
		temp.pMem[i] = ~pMem[i];
	}

	int extraBits = BitLen % (sizeof(TELEM) * 8);
	if (extraBits != 0) {
		temp.pMem[MemLen - 1] = temp.pMem[MemLen - 1] & ((1 << extraBits) - 1);
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