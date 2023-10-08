// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet() noexcept {
    MaxPower = 0;
}

TSet::TSet(int mp) 
{
    TBitField x(mp);
    MaxPower = mp;
    BitField = x;
}

// конструктор копирования
TSet::TSet(const TSet &s) 
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) 
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (BitField.GetBit(Elem))
        return 1;
    else
        return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции



int TSet::operator==(const TSet &s) const // сравнение
{
    if ((BitField == s.BitField) && (MaxPower==s.MaxPower))
        return 1;
    else
        return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s)
        return 0;
    else
        return 1;
}

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (*this != s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return(*this);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    BitField = BitField | s.BitField;
    int Max_len = 0;
    MaxPower = max(MaxPower, s.MaxPower);
    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem >= MaxPower || Elem < 0)
        throw out_of_range("Elem must be >=0 and <MaxPower");
    else {
        TSet x(*this);
        x.InsElem(Elem);
        return x;
    }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= MaxPower || Elem < 0)
        throw out_of_range("Elem must be >=0 and <MaxPower");
    else {
        TSet x(*this);
        x.DelElem(Elem);
        return x;
    }
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet x = s;
    x.BitField = this->BitField & s.BitField;
    return x;
}

TSet TSet::operator~(void) // дополнение
{
    TSet x(*this);
    x.BitField = ~x.BitField;
    return x;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (int i = 0; i < s.MaxPower; i++) {
        bool x;
        cin >> x;
        if (x) s.InsElem(i);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
        cout << s.IsMember(i);
    return ostr;
}
