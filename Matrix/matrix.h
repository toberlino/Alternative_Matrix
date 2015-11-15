#include "vector.h"

const int MAX_MATRIX = 10000;

template <class ValType>
class TMatrix {
private:
	TVector<ValType> **pMatrix;
	int Size;
public:

	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    
	TMatrix(const TVector<TVector<ValType> > &mt); 
	~TMatrix();
	int GetSize() const { return Size; }
	TVector<ValType>& operator[](int idx) const;            
	bool operator==(const TMatrix &mt) const;      
	bool operator!=(const TMatrix &mt) const;      
	TMatrix& operator= (const TMatrix &mt);        
	TMatrix  operator+ (const TMatrix &mt);       
	TMatrix  operator- (const TMatrix &mt);     

	template <class ValType>
	friend istream& operator>>(istream &in, TMatrix<ValType> &mt);
	template <class ValType>
	friend ostream & operator<<(ostream &out, const TMatrix<ValType> &mt);
	
};
template <class ValType>
istream& operator>>(istream &in, TMatrix<ValType> &mt) {
		in >> mt.Size;
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
 template <class ValType>
ostream & operator<<(ostream &out, const TMatrix<ValType> &mt) {
		out << mt.Size << endl;
		for (int i = 0; i < mt.Size; i++)
			out << *(mt.pMatrix[i]) << endl;
		return out;
	}

template <class ValType>
TMatrix<ValType>::TMatrix(int s){
	if (s<0) {
		throw invalid_argument("s<0");
	}
	if (s>MAX_MATRIX) {
		throw invalid_argument("MAX_MATRIX<s");
	}
	Size = s;
	pMatrix = new TVector<ValType>*[s];
	for (int i = 0; i<s; i++)
		pMatrix[i] = new TVector<ValType>(s-i,i);
} 

template <class ValType>
TMatrix<ValType>::~TMatrix()
{
	for (int i = 0; i < Size; i++)
	{
		delete pMatrix[i];
	}
	delete []pMatrix;
} 

template <class ValType> 
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt){
	Size = mt.GetSize();
	pMatrix = new  TVector<ValType>* [Size];
	for (int i = 0; i<Size; i++)
		pMatrix[i] = new TVector<ValType>(Size - i, i);
	for (int i = 0; i < Size;i++)
	{
		*pMatrix[i] = *(mt.pMatrix[i]);
	}
}

template <class ValType>
TVector<ValType>& TMatrix<ValType>::operator[](int idx) const {
	if (idx<0) {
		throw invalid_argument("idx<0");
	}if (idx>Size) {
		throw invalid_argument("[] idx>Size");
	}
	return *(pMatrix[idx]);
} 


template <class ValType> 
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
	if (this == &mt) {
		return true;
	}

	if (Size != mt.GetSize()) {
		return false;
	}

	for (int i = 0; i < Size; i++) {
		if (*pMatrix[i] != *(mt.pMatrix[i]))
			return false;
	}

	return true;
} 

template <class ValType> 
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
	return !(*this == mt);
} 

template <class ValType> 
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
	if (this != &mt) {
		if (Size!=mt.GetSize())
		{
			for (int i = 0; i < Size; i++) {
				delete pMatrix[i];
			}
			delete []pMatrix;
		Size = mt.Size;
			pMatrix = new  TVector<ValType>*[mt.GetSize()];
			for (int i = 0; i<Size; i++)
				pMatrix[i] = new TVector<ValType>(Size - i, i);
		}
		for (int i = 0; i < mt.GetSize(); i++) {
			*pMatrix[i] = *(mt.pMatrix[i]);
		}
	}
	return *this;
} 

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
	if (Size != mt.GetSize()) {
		throw invalid_argument("throw");
	}
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++) {
		res[i] = (*this)[i] + mt[i];
	}
	return res;
} 

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
	if (Size != mt.GetSize()) {
		throw invalid_argument("throw");
	}
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++) {
		res[i] = (*this)[i] - mt[i];
	}
	return res;
} 

