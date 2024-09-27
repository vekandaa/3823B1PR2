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
		throw invalid_argument("Error _ Negative len");
	}
	BitLen = len;
	MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() // деструктор 
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen))
		throw invalid_argument("Error _ index out of range");

	return n / (sizeof(TELEM) * 8); // делим номер бита на количество битов в одном элементе массива
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen))
		throw invalid_argument("Error _ index out of range");

	return 1 << (n % (sizeof(TELEM) * 8)); // сдвигаем бит на указанную позицию
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw invalid_argument("Error _ index out of range");

	int i = GetMemIndex(n); // получили индекс
	TELEM t = GetMemMask(n); // получили маску
	pMem[i] = pMem[i] | t; //  установили бит
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw invalid_argument("Error _ index out of range");

	int i = GetMemIndex(n);
	TELEM t = ~GetMemMask(n); // получили маску + инвертировали
	pMem[i] = pMem[i] & t;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw invalid_argument("Error _ index out of range");

	int i = GetMemIndex(n);
	TELEM t = GetMemMask(n);
	if ((pMem[i] & t) > 0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) // самоприсваивание
	{
		if (MemLen != bf.MemLen) // если разных размеров
		{
			delete[] pMem; // удаляем старое, заводим новое
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		BitLen = bf.BitLen; // копируем кол-во битов 
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i]; // поэлементно копируем
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) // сравниваем длину
		return 0;

	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) // сравниваем поэлементно
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение (аналогично)
{
	if (BitLen != bf.BitLen) 
		return 1;
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField result(1);  // временный объект
	
	if (BitLen >= bf.BitLen) // проверяем какое  поле длиннее, наибольшее копируем
		result = *this;
	else
		result = bf;

	int minLen; // минимальная длина
	if (BitLen < bf.BitLen)
		minLen = BitLen;
	else
		minLen = bf.BitLen;

	for (int i = 0; i < minLen; i++) 
	{
		if (GetBit(i) == 1 || bf.GetBit(i) == 1) // проверяем поля на наличие бита
			result.SetBit(i);
	}

	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int maxLen;
	if (BitLen > bf.BitLen)
		maxLen = BitLen;
	else
		maxLen = bf.BitLen;
	TBitField result(maxLen); // новое поле с максимальной длиной

	for (int i = 0; i < maxLen; i++)
	{
		if (i < BitLen && i < bf.BitLen)
			if (GetBit(i) && bf.GetBit(i))
				result.SetBit(i);
	}

	return result;
}

TBitField TBitField::operator~(void) // отрицание (меняем биты на противоположные)
{
	TBitField result(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i)) 
			result.ClrBit(i);
		else 
			result.SetBit(i);
	}
	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		int bit;
		istr >> bit;
		if (bit)
			bf.SetBit(i);
		else
			bf.ClrBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}