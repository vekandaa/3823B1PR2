// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

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
    return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return FAKE_INT;
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
    return FAKE_BITFIELD;
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
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
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