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
	if (len < 0) {
		throw "Length cannot be negative";
	}
	BitLen = len;  // Указываем количество битов
	MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);  // Вычисляем, сколько элементов нужно в массиве pMem
	pMem = new TELEM[MemLen];  // Выделяем память для массива pMem
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;  // Инициализируем массив нулями
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
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) {
		throw "Bit index out of range";
	}
	//int a = GetMemIndex(n); // находим индекс бита n
	//TELEM mask = 1 << (n % (sizeof(TELEM) * 8)); // делаем маску для n только в его поле
	//pMem[a] |= mask; //устанавливает в 1 те переменные что были 1 в маске (OR/и/сумма)
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) {
		throw "Bit index out of range";
	}
	//int a = GetMemIndex(n);
	//TELEM mask = ~(1 << (n % (sizeof(TELEM) * 8)));
	//pMem[a] &= mask;
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return FAKE_INT;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    return FAKE_INT;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    return ostr;
}
