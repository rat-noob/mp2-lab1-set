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
    BitLen = len;
    MemLen = (BitLen+31)/(sizeof(MemLen)<<3);//сколько чисел(в данном случае инт) надо для представления Bitlen элементов. <<3 умножает на 8
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)//вроде нужнео чтоб оно при инициализации нулями заполнялось
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        this->pMem[i] =  bf.pMem[i];
    }
   
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int MemIndex;
    MemIndex = (n + 31)/ (sizeof(MemLen) << 3);
    return MemIndex;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    //(45 & ~(32)) - остаток от деления 45 на 32
    int MemMask;
    MemMask = 1<<(n& ~(sizeof(MemLen) << 3)) ;
    return MemMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    pMem[MemIndex] = pMem[MemIndex] | MemMask;

}

void TBitField::ClrBit(const int n) // очистить бит
{
    int MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    pMem[MemIndex] = pMem[MemIndex] & ~MemMask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int Bit;
    int MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    Bit = pMem[MemIndex] & MemMask;
    
    return Bit;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{   
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    delete pMem;
    pMem = new TELEM[MemLen];
    
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;//возможно другой ретерн
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    if (MemLen != bf.MemLen) return 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i]) return 0; /*break;*/
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    if (MemLen != bf.MemLen) return 1;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i]) return 1; /*break;*/
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = ~pMem[i];
    }
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{   
    
    for (int i = 0; i < bf.MemLen; i++)
    {
        cout << bf.pMem[i]<<endl;
    }
    
    
    /*for (int i = bf.MemLen - 1; i > (-1); i--) это если по 0 и 1 выводить
    {
        cout<<
    }*/
    return ostr;
}
