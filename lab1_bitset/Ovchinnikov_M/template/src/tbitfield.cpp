// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) // конструктор создания битового поля
{
	if (len <= 0) throw ("Лена отрицательна, чел");
	BitLen = len;
	MemLen = (BitLen / ((sizeof(TELEM)) * 8)) + (BitLen % ((sizeof(TELEM)) * 8) != 0);
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
	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() //диструктор
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n<0 || n>=BitLen) throw ("Индекс не подходит");
	return n / (sizeof(TELEM) * 8); //нам нужно знать в каком инте сидит наш бит
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)  throw ("Индекс не подходит");
	return 1 << n; // мы сдвигаем единицу на n влево, потому что маска возвращает единицу вместо бита, номер которого n, а всё остальное 0 
}

	// доступ к битам битового поля


int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)  throw ("Индекс не подходит");
	pMem[GetMemIndex(n)] |= GetMemMask(n); //побитовая операция OR
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)  throw ("Индекс не подходит");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n); // побитовая операция AND ( ~ - это инверсия)
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)  throw ("Индекс не подходит");
	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{

	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) return 1;
		}
		return 0;
	}
	else return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField result = (BitLen > bf.BitLen) ? *this : bf;
	for (int i = 0; i < min(MemLen, bf.MemLen); i++) {
		result.pMem[i] = pMem[i] |= bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField result(max(BitLen, bf.BitLen));
	for (int i = 0; i < min(MemLen, bf.MemLen); i++)
	{
		result.pMem[i] = bf.pMem[i] & pMem[i];
	}
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	const int totalBits = sizeof(TELEM) * 8;
	const int extraBits = BitLen % totalBits;

	// Инвертируем все слова
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = ~pMem[i];
	}

	// Если есть остаток, обнуляем лишние биты в последнем элементе
	if (extraBits > 0)
	{
		result.pMem[MemLen - 1] &= (1 << extraBits) - 1; // Используем маску только если есть остаток
	}

	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	return ostr;
}
