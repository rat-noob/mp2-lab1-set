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
const int sz = (sizeof(TELEM));

TBitField::TBitField(int len)
{
    if (len < 0) throw - 1;
    BitLen = len;
    MemLen = (BitLen+31)/(sz << 3);//сколько чисел(в данном случае u_int) надо для представления Bitlen элементов. <<3 умножает на 8
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
    if (n > BitLen) throw - 1;
    if (n < 0) throw "err";
    int MemIndex;
    MemIndex = n / (sz << 3);    /*(n + 31)/ (sizeof(MemLen) << 3);*/
    return MemIndex;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
   
    if (n < 0) throw "err";
    //(45 & ~(32)) - остаток от деления 45 на 32
    TELEM MemMask;
    TELEM Bit = n % (sz << 3);

    MemMask = 1<<Bit;
    return MemMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > BitLen) throw - 1;
    if (n < 0) throw "err";
    TELEM MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    pMem[MemIndex] = pMem[MemIndex] | MemMask;

}

void TBitField::ClrBit(const int n) // очистить бит
{   
    if (n > BitLen) throw - 1;
    if (n < 0) throw "err";
    TELEM MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    pMem[MemIndex] = pMem[MemIndex] & ~MemMask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n > BitLen) throw - 1;
    if (n < 0) throw "err";
    int Bit;
    TELEM MemMask = GetMemMask(n);
    int MemIndex = GetMemIndex(n);
    Bit = pMem[MemIndex] & MemMask;
    
    return Bit;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{   
    if (*this != bf) {
        this->BitLen = bf.BitLen;
        this->MemLen = bf.MemLen;
        delete pMem;
        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    if (MemLen != bf.MemLen) return 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i]) return 0; 
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    if (MemLen != bf.MemLen) return 1;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i]) return 1; 
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField result(bf.BitLen);
    /*if (this->GetLength() != bf.GetLength()) throw - 1;*/
    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = this->pMem[i] | bf.pMem[i];
    }

    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{   
    /*if (this->GetLength() != bf.GetLength()) throw - 1;*/
    TBitField result = (bf.BitLen);
    for (int i = 0; i < bf.MemLen; i++)
    {
        result.pMem[i] = (this->pMem[i]) & (bf.pMem[i]);
    }
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    
    for (int i = 0; i < MemLen; i++)
    {
        if (i == MemLen - 1) {
            int BitsInLastElem = BitLen % (sz <<3);
            if (BitsInLastElem == 0) pMem[i] = ~(pMem[i]);
            else {
                TELEM mask = (1 << BitsInLastElem) - 1;
                pMem[i] = (~pMem[i]) & mask;
            }

        }else pMem[i] = ~(pMem[i]);
        
    }
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int n;
    cout << "Для выхода из ввода введите -1" << endl;
    do {
        cout << "Введите число <= " << bf.BitLen << endl;
        cin >> n;
        bf.SetBit(n);
    } while (n != -1);
    

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{   
    int num,BigHalf,SmallHalf;
    
    for (int i = 0; i < bf.MemLen; i++)
    {
        BigHalf = i  * (sz << 3);
        for (int j = 0; j < (sz <<3); j++)
        {
            num = BigHalf + j;
            if (bf.GetBit(num)!= 0) cout << num <<" ";
        }
        
       
    }
    
    return ostr;
}
