#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
using namespace std;

const int MAX_VECTOR = 100000000;

template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       
  int StartIndex; 
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);               
  ~TVector();
  int GetSize() const      { return Size;       }
  int GetStartIndex() const { return StartIndex; }
  ValType& operator[](int idx) const;           
  bool operator==(const TVector &v) const; 
  bool operator!=(const TVector &v) const;  
  TVector& operator=(const TVector &v);    
  TVector  operator+(const TVector &v);     
  TVector  operator-(const TVector &v);     
  ValType  operator*(const TVector &v);     

  // ввод-вывод
template <class ValType>
  friend istream& operator>>(istream &in, TVector<ValType> &v);
  
template <class ValType>
  friend ostream& operator<<(ostream &out, const TVector<ValType> &v);
};

template <class ValType>
  istream& operator>>(istream &in, TVector<ValType> &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  
  template <class ValType>
  ostream& operator<<(ostream &out, const TVector<ValType> &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] <<' ';
    return out;
  }

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s<0)
		throw "s<0";
	else if(s>MAX_VECTOR)
		throw "s>MAX_VECTOR";
	else if (si<0)
		throw "start index<0";
	else
	{
		Size=s;
		pVector=new ValType[Size];
		StartIndex=si;
	}	
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{   
	Size=v.Size;
	StartIndex=v.StartIndex;
	pVector=new ValType[Size];
	for (int i=0; i<Size; i++)
		pVector[i]=v.pVector[i];
} 

template <class ValType> //Деструктор
TVector<ValType>::~TVector()
{
		delete []pVector;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int idx) const
{
	if (idx<0) 
		throw invalid_argument(" idx<0");
	if(idx<StartIndex)
		return *new ValType();
	if(idx>=Size+StartIndex)
		throw "idx>MAX_VECTOR";	
	else
		return pVector[idx-StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
 {
 	if(Size!=v.Size)
 		return false;
 	else if (StartIndex!=v.StartIndex)
 		return false;
 	else
 	{
 		for (int i=StartIndex;i<StartIndex+Size;i++)
 			if (pVector[i]!=v.pVector[i])
 			{
 				return false;
 				break;
 			}
 	}
 	return true;
 } /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
 {
 	if (Size!=v.Size)
 		return true;
 	else if (StartIndex!=v.StartIndex)
 		return true;
 	else
 	{
 		for (int i=StartIndex; i<StartIndex+Size;i++)
 			if (pVector[i]!=v.pVector[i])
 			{
 				return true;
 				break;
 			}
 			else
 				return false;
 	}
	return true;
 } /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
 	if(this == &v)
 		return *this;
 	if(Size!=v.Size)
 	{
 		delete[]pVector;
 		pVector=new ValType [v.Size];
 		Size=v.Size;
 	}
	for (int i=0; i<Size;i++)
		pVector[i]=v.pVector[i];
 	return *this;
} /*-------------------------------------------------------------------------*/


template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size!=v.Size)
 		throw "Error";
 	else if(StartIndex!=v.StartIndex)
 		throw "Error";
 	else
 	{
 		TVector <ValType> res(Size,StartIndex);
 		for (int i=StartIndex; i<StartIndex+Size;i++)
 			res[i]=(*this)[i]+v[i];
 		return res;
 	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size!=v.Size)
 		throw "Error";
 	else if(StartIndex!=v.StartIndex)
 		throw "Error";
 	else
 	{
 		TVector <ValType> res(Size,StartIndex);
 		for (int i=StartIndex; i<StartIndex+Size;i++)
 			res[i]=(*this)[i] - v[i];
 		return res;
 	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size!=v.Size)
 		throw "Error";
 	else if(StartIndex!=v.StartIndex)
 		throw "Error";
 	else
 	{
 		ValType res=0;
 		for (int i=StartIndex; i<StartIndex+Size;i++)
 			res=res+pVector[i]*v.pVector[i];
 		return res;
 	}
} 
#endif