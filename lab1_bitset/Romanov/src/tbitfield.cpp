// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"



const int SIZE = sizeof(TELEM)*8;

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw -1;
    }
    BitLen = len;
    MemLen = len/SIZE + 1;
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++){
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) : BitLen(bf.BitLen), MemLen(bf.MemLen)// конструктор копирования
{
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++){
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/SIZE;

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n%SIZE);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if((n < 0) || (n >= BitLen)){
        throw -1;
    } 
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{  
    if((n < 0) || (n >= BitLen)){
        throw -1;
    } 
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if((n < 0) || (n >= BitLen)){
        throw -1;
    } 
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf)  // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++){
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  for(int i = 0; i < MemLen; i++){
    if(pMem[i] != bf.pMem[i]) return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField& bf) const 
{
   if (BitLen != bf.BitLen) return 1;
   for(int i = 0; i < MemLen; i++){
     if(pMem[i] != bf.pMem[i]) return 1;
   }
   return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if(BitLen > bf.BitLen){

        TBitField temp(BitLen);
        for(int i = 0; i < bf.MemLen; i++){
            temp.pMem[i] = bf.pMem[i] | pMem[i];
        }
        for(int i = bf.MemLen; i < MemLen; i++){
            temp.pMem[i] = pMem[i] | 0;
        }
        return temp;
    }
    else {
        TBitField temp(bf.BitLen);
        for(int i = 0; i < MemLen; i++){
            temp.pMem[i] = bf.pMem[i] | pMem[i];
        }
        for(int i = MemLen; i < bf.MemLen; i++){
            temp.pMem[i] = bf.pMem[i] | 0;
        }
        return temp;       
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int tempLen;

    if(BitLen > bf.BitLen){
        tempLen = BitLen;
        TBitField temp(tempLen);
        for(int i = 0; i < bf.MemLen; i++){
            temp.pMem[i] = bf.pMem[i] & pMem[i]; 
        }
        for(int i = bf.MemLen; i < MemLen; i++){
            temp.pMem[i] = pMem[i] & 0;
        }
        return temp;
    }
    else {
        tempLen = bf.BitLen;
        TBitField temp(tempLen);
        for(int i = 0; i < MemLen; i++){
            temp.pMem[i] = bf.pMem[i] & pMem[i];
        }
        for(int i = bf.MemLen; i < MemLen; i++){
            temp.pMem[i] = bf.pMem[i] & 0;
        }
        return temp;       
    }
}

TBitField TBitField::operator~() {
    TBitField tmp(BitLen);
    for (int u = 0; u < MemLen; u++) {
        tmp.pMem[u] = (unsigned int)~pMem[u];
    }
    int last = BitLen % (SIZE * 8);
    if (last > 0) {
        unsigned int mask = (1 << last) - 1; 
        tmp.pMem[MemLen - 1] &= (unsigned int)mask;
    }
    return tmp;
}


istream& operator>>(istream& istr, TBitField& bf) {
    for (int i = 0; i < bf.GetLength(); i++) {
        unsigned int bit;
        istr >> bit;
        if (bit) {
            bf.SetBit(i);
        }
        else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) { 
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}