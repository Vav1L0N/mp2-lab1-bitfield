// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField() noexcept {
    BitLen = 0;
    MemLen = 0;
    pMem = nullptr;
}

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw out_of_range("Size must be non-negative");
    }
    else {

        BitLen = len;
        if (len == 0) {
            pMem = nullptr;
            MemLen = 0;
        }
        else {
            MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);
            pMem = new TELEM[MemLen];
            for (int i = 0; i < MemLen; i++)
                pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    if (bf.BitLen != 0) {
        MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    else {
        MemLen = 0;
        pMem = nullptr;
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
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw out_of_range("n must be greater or eqals than 0 and less than BitLen ");
    else
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw out_of_range("n must be greater or eqals than 0 and less than BitLen ");
    else
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen))
        throw out_of_range("n must be greater or eqals than 0 and less than BitLen ");
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (*this != bf) {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    else
        return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen) {

        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i])
                return false;
        }
        return true;
    }
    else
        return false;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return (!(this->operator==(bf)));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField x = bf;
    if (BitLen > x.BitLen) {
        for (int i = 0; i < x.MemLen; i++)
            pMem[i] |= x.pMem[i];
        return(*this);
    }
    else {
        for (int i = 0; i < MemLen; i++)
            x.pMem[i] |= pMem[i];
        return(x);
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField x = bf;
    if (BitLen > x.BitLen) {
        for (int i = 0; i < x.MemLen; i++)
            pMem[i] &= x.pMem[i];
        return(*this);
    }
    else {
        for (int i = 0; i < MemLen; i++)
            x.pMem[i] &= pMem[i];
        return(x);
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField x(BitLen);
    for (int i = 0; i < BitLen; ++i)
    {
        if (!(GetBit(i)))
            x.SetBit(i);
        else
            x.ClrBit(i);
    }
    return x;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; ++i)
    {
        bool x;
        cin >> x;
        if (x) bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        cout << bf.GetBit(i);
    return ostr;
}
