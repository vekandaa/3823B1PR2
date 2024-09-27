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
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
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
	if (n < 0 || n >= BitLen) {
		throw "Bit index out of range";
	}
	int index = GetMemIndex(n); // Определяем, в каком элементе массива находится бит n
	TELEM mask = 1 << (n % (sizeof(TELEM) * 8)); // Создаём маску для нужного бита в этом элементе
	return (pMem[index] & mask) != 0 ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) {
		delete [] pMem;

		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM [MemLen];

		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return false;
	}

	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return false;
		}
	}
	return true;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] == bf.pMem[i]) {
			return false;
		}
	}
	return true;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{	
	int MaxLen = max(BitLen, bf.BitLen);
	TBitField result(MaxLen);

	// Проходим по всем элементам массива
	for (int i = 0; i < result.MemLen; i++) {
		TELEM left = (i < MemLen) ? pMem[i] : 0; // Если текущий индекс в пределах текущего объекта, берем значение, иначе 0
		TELEM right = (i < bf.MemLen) ? bf.pMem[i] : 0; // Аналогично для второго объекта
		result.pMem[i] = left | right; // Выполняем побитовое ИЛИ
	}

	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int MaxLen = max(BitLen, bf.BitLen);
	TBitField result(MaxLen);

	// Проходим по всем элементам массива
	for (int i = 0; i < result.MemLen; i++) {
		TELEM left = (i < MemLen) ? pMem[i] : 0; 
		TELEM right = (i < bf.MemLen) ? bf.pMem[i] : 0;
		result.pMem[i] = left & right; 
	}

	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	//TBitField result(BitLen);
	//for (int i = 0; i < MemLen; i++) {
		//result.pMem[i] = ~pMem[i];
	//} 
	//return result;
	TBitField result(BitLen);

	// Инвертируем все элементы, кроме последнего
	for (int i = 0; i < MemLen - 1; i++) {
		result.pMem[i] = ~pMem[i];
	}

	// Инвертируем последний элемент с учётом реальной длины битов
	if (MemLen > 0) {
		int lastBits = BitLen % (sizeof(TELEM) * 8);
		if (lastBits == 0) {
			result.pMem[MemLen - 1] = ~pMem[MemLen - 1]; // Инвертируем полностью
		}
		else {
			TELEM mask = (1 << lastBits) - 1; // Маска для инвертирования только значимых битов
			result.pMem[MemLen - 1] = (~pMem[MemLen - 1]) & mask; // Инвертируем и применяем маску
		}
	}
	return result;

}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.GetLength(); i++) {
		int bitValue;
		istr >> bitValue; // Читаем значение бита (0 или 1)
		if (bitValue < 0 || bitValue > 1) {
			throw "Bit value must be 0 or 1";
		}
		if (bitValue == 1) {
			bf.SetBit(i); // Устанавливаем бит, если введено 1
		}
		else {
			bf.ClrBit(i); // Очищаем бит, если введено 0
		}
	}
	return istr; // Возвращаем поток для цепочки операций
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++) {
		ostr << bf.GetBit(i); // Выводим значения битов
	}
	return ostr; // Возвращаем поток для цепочки операций
}