#ifndef _NR3_H_
#define _NR3_H_

//#define _CHECKBOUNDS_ 1
//#define _USESTDVECTOR_ 1
//#define _USENRERRORCLASS_ 1
//#define _TURNONFPES_ 1

// all the system #include's we'll ever need
#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

using namespace std;
typedef double Doub;
// macro-like inline functions

template<class T>
inline T SQR(const T a) {return a*a;}

template<class T>
inline const T &MAX(const T &a, const T &b)
{return b > a ? (b) : (a);}

inline float MAX(const double &a, const float &b)
{return b > a ? (b) : float(a);}

inline float MAX(const float &a, const double &b)
{return b > a ? float(b) : (a);}

template<class T>
inline const T &MIN(const T &a, const T &b)
{return b < a ? (b) : (a);}

inline float MIN(const double &a, const float &b)
{return b < a ? (b) : float(a);}

inline float MIN(const float &a, const double &b)
{return b < a ? float(b) : (a);}

template<class T>
inline T SIGN(const T &a, const T &b)
{return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}

inline float SIGN(const float &a, const double &b)
{return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}

inline float SIGN(const double &a, const float &b)
{return (float)(b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));}

template<class T>
inline void SWAP(T &a, T &b)
{T dum=a; a=b; b=dum;}

// exception handling

#ifndef _USENRERRORCLASS_
#define throw(message) \
	{printf("ERROR: %s\n     in file %s at line %d\n", message,__FILE__,__LINE__); throw(1);}
#else
struct NRerror {
	char *message;
	char *file;
	int line;
	NRerror(char *m, char *f, int l) : message(m), file(f), line(l) {}
};
#define throw(message) throw(NRerror(message,__FILE__,__LINE__));
void NRcatch(NRerror err) {
	printf("ERROR: %s\n     in file %s at line %d\n",
			err.message, err.file, err.line);
	exit(1);
}
#endif

// usage example:
//
//	try {
//		somebadroutine();
//	}
//	catch(NRerror s) {NRcatch(s);}
//
// (You can of course substitute any other catch body for NRcatch(s).)


// Vector and Matrix Classes

#ifdef _USESTDVECTOR_
#define NRvector vector
#else

template <class T>
class NRvector {
protected:
	int nn;	// size of array. upper index is nn-1
	T *v;
public:
	NRvector();
	explicit NRvector(int n);		// Zero-based array
	NRvector(int n, const T &a);	//initialize to constant value
	NRvector(int n, const T *a);	// Initialize to array
	NRvector(const NRvector &rhs);	// Copy constructor
	NRvector & operator=(const NRvector &rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T & operator[](const int i);	//i'th element
	inline const T & operator[](const int i) const;
	inline int size() const;
	void resize(int newn); // resize (contents not preserved)
	void assign(int newn, const T &a); // resize and assign a constant value
	virtual ~NRvector();

	inline void Clean()
	{
		for( int i=0; i<nn; i++)
			v[i]=0;
	}
	//***********************************************************************
	//my functions
	//***********************************************************************
	inline void Rand(int v_iFrom = 0, int v_iCut = 0, Doub v_dDiv = 1.0)
	{
		for( unsigned long ulIt=0; ulIt<nn; ulIt++)
			v[ulIt] = ( v_iFrom + ( !v_iCut ? rand() : rand()%v_iCut) )/v_dDiv;
	}


	inline NRvector Abs()
	{
		NRvector<T> oVec ( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = fabs( v[ulIt] );
		return oVec;
	}

	inline Doub Max()
	{
		Doub dMax = v[0];
		for( long ulIt=0; ulIt<nn; ulIt++)
			dMax = v[ulIt] > dMax ? v[ulIt] : dMax;
			return dMax;
	}

	inline Doub MaxIdx()
	{
		Doub dMax = v[0];
		Doub ulItMax = 0;
		for( long ulIt=1; ulIt<nn; ulIt++)
			if( v[ulIt] > dMax )
			{
				dMax = v[ulIt];
				ulItMax = ulIt;
			}
		return ulItMax;
	}

	NRvector<T>
	UnionAndSort( NRvector<T> &v_rVec )
	{

		if( !v_rVec.size() )
		{
			NRvector<T> oVec = *this;
			sort(oVec);
			return oVec;
		}//if
		
		NRvector<T> oVec( v_rVec.size() + nn, 0.0 );

		for( int i=0; i<nn; i++ )
			oVec[i] = v[i];
		
		for( int i=nn; i<nn+v_rVec.size(); i++ )
			oVec[i] = v_rVec[i-nn];

		sort(oVec);
		NRvector<T> oVecFinal( v_rVec.size() + nn, 0.0 );

		int iFin=0;
		int iTmp=0;
		while( iTmp < oVec.size() )
		{
			if( iTmp==0 )
			{
				oVecFinal[iFin++] = oVec[iTmp++];
				continue;
			}//if

			if( oVec[iTmp] != oVecFinal[iFin-1] )
				oVecFinal[iFin++] = oVec[ iTmp++ ];
			else
				iTmp++;
		}//while

		NRvector<T> oVecReturn( iFin, 0.0 );
		for( int i=0; i<iFin; i++ )
			oVecReturn[i] = oVecFinal[i];

		return oVecReturn;

	}//Union

	inline Doub MinIdx()
	{
		Doub dMin = v[0];
		Doub ulItMin = 0;
		for( long ulIt=0; ulIt<nn; ulIt++)
			if( v[ulIt] < dMin )
			{
				dMin = v[ulIt];
				ulItMin = ulIt;
			}
		return ulItMin;
	}

	inline Doub AbsMax()
	{
		Doub dMax = v[0];
		for( long ulIt=0; ulIt<nn; ulIt++)
			dMax = fabs(v[ulIt]) > dMax ? fabs(v[ulIt]) : dMax;
			return dMax;
	}

	inline NRvector operator*( Doub v_dVal )
	{
		NRvector oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v_dVal*v[ulIt];
		return oVec;
	}

	inline Doub operator*( NRvector<T> &v_rVec )
	{
		Doub dVal = 0.0;
		for( long ulIt=0; ulIt<nn; ulIt++)
			dVal += v_rVec[ulIt]*v[ulIt];
		return dVal;
	}


	inline NRvector DivInv( Doub v_dVal )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v_dVal/v[ulIt];
		return oVec;
	}

	inline void AddFieldAtEnd( T j )
	{
		nn = nn ? nn+1 : 1;

		T *pData = new T[nn];
		for(int i=0; i<nn-1; i++)
			pData[i] = v[i];

		pData[nn-1] = j;
		if(v) delete [] v;
		v = pData;
	}

	inline NRvector DivInv( NRvector<T> &v_rVec )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v[ulIt]/v_rVec[ulIt];
		return oVec;
	}

	inline NRvector MulInv( NRvector<T> &v_rVec )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v[ulIt]*v_rVec[ulIt];
		return oVec;
	}

	inline NRvector operator+( NRvector<T> &v_rVec )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v_rVec[ulIt]+v[ulIt];
		return oVec;
	}

	inline NRvector operator+( Doub v_dVal )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v[ulIt]+v_dVal;
		return oVec;
	}

	NRvector operator-( NRvector<T> &v_rVec )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v[ulIt]-v_rVec[ulIt];
		return oVec;
	}

	NRvector operator-( Doub v_dVal )
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = v[ulIt]-v_dVal;
		return oVec;
	}

	NRvector operator-()
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = -v[ulIt];
		return oVec;
	}


	inline NRvector PowInv(Doub v_dVal)
	{
		NRvector<T> oVec( nn, 0.0 );
		for( long ulIt=0; ulIt<nn; ulIt++)
			oVec[ulIt] = pow(v[ulIt], v_dVal);
		return oVec;
	}

	inline Doub Norm()
	{
		Doub dVal = 0;
		for( long i=0; i<nn; i++)
			dVal += SQR( v[i] );
		return dVal;
	}

	inline Doub Sum()
	{
		Doub dVal = 0;
		for( long i=0; i<nn; i++)
			dVal += v[i];
		return dVal;
	}

	inline NRvector FindLT(Doub v_dVal)
	{
		unsigned int uiCount = 0;
		for( long i=0; i<nn; i++)
			if( v[i] < v_dVal )
				uiCount++;

		NRvector<T> oVec( uiCount );
		int iIdx = 0;
		for( long i=0; i<nn; i++ )
			if( v[i] < v_dVal )
			{
				oVec[iIdx] = i;//this->operator [](i);
				iIdx++;
			}
		return oVec;
	}

	inline NRvector FindGT(Doub v_dVal)
	{
		unsigned int uiCount = 0;
		for( long i=0; i<nn; i++)
			if( v[i] > v_dVal )
				uiCount++;

		NRvector<T> oVec( uiCount );
		int iIdx = 0;
		for( long i=0; i<nn; i++ )
			if( v[i] > v_dVal )
			{
				oVec[iIdx] = i;//this->operator [](i);
				iIdx++;
			}
		return oVec;
	}

	inline NRvector FindEqual(Doub v_dVal)
	{
		unsigned int uiCount = 0;
		for( long i=0; i<nn; i++)
			if( v[i] == v_dVal )
				uiCount++;

		NRvector<T> oVec( uiCount );
		int iIdx = 0;
		for( long i=0; i<nn; i++ )
			if( v[i] == v_dVal )
			{
				oVec[iIdx] = i;//this->operator [](i);
				iIdx++;
			}
		return oVec;
	}

	inline NRvector operator()(NRvector<T> &v_rVec)
	{
		NRvector<T> oVec( v_rVec.size() );
		for( long i=0; i<v_rVec.size(); i++ )
		{
			T tVal = v[(int)v_rVec[i]];
			oVec[i] = tVal;
		}
		return oVec;
	}

	inline void Set(int v_iPos, NRvector<T> &v_rVec)
	{
		for( long i=0; i<v_rVec.size(); i++ )
			v[i+v_iPos] = v_rVec[i];
	}

	inline void Set(int v_iPos, Doub v_dVal)
	{
		for( long i=v_iPos; i<nn; i++ )
			v[i] = v_dVal;
	}

	inline Doub Min()
	{
		Doub dVal = v[0];
		for(int i=0; i<nn; i++)
		{
			if( v[i] < dVal )
				dVal = v[i];
		}
		return dVal;
	}
};

// NRvector definitions

template <class T>
NRvector<T>::NRvector() : nn(0), v(NULL) {}

template <class T>
NRvector<T>::NRvector(int n) : nn(n), v(n>0 ? new T[n] : NULL) {}

template <class T>
NRvector<T>::NRvector(int n, const T& a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = a;
}

template <class T>
NRvector<T>::NRvector(int n, const T *a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = *a++;
}

template <class T>
NRvector<T>::NRvector(const NRvector<T> &rhs) : nn(rhs.nn), v(nn>0 ? new T[nn] : NULL)
{
	for(int i=0; i<nn; i++) v[i] = rhs[i];
}

template <class T>
NRvector<T> & NRvector<T>::operator=(const NRvector<T> &rhs)
// postcondition: normal assignment via copying has been performed;
//		if NRvector and rhs were different sizes, NRvector
//		has been resized to match the size of rhs
{
	if (this != &rhs)
	{
		if (nn != rhs.nn) {
			if (v != NULL) delete [] (v);
			nn=rhs.nn;
			v= nn>0 ? new T[nn] : NULL;
		}
		for (int i=0; i<nn; i++)
			v[i]=rhs[i];
	}
	return *this;
}

template <class T>
inline T & NRvector<T>::operator[](const int i)	//subscripting
{
#ifdef _CHECKBOUNDS_
	if (i<0 || i>=nn) {
		throw("NRvector subscript out of bounds");
	}
#endif
	return v[i];
}

template <class T>
inline const T & NRvector<T>::operator[](const int i) const	//subscripting
{
#ifdef _CHECKBOUNDS_
	if (i<0 || i>=nn) {
		throw("NRvector subscript out of bounds");
	}
#endif
	return v[i];
}

template <class T>
inline int NRvector<T>::size() const
{
	return nn;
}

template <class T>
void NRvector<T>::resize(int newn)
{
	if (newn != nn) {
		if (v != NULL) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : NULL;
	}
}

template <class T>
void NRvector<T>::assign(int newn, const T& a)
{
	if (newn != nn) {
		if (v != NULL) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : NULL;
	}
	for (int i=0;i<nn;i++) v[i] = a;
}

template <class T>
NRvector<T>::~NRvector()
{
	if (v != NULL) delete[] (v);
	v = NULL;
}

// end of NRvector definitions

#endif //ifdef _USESTDVECTOR_

template <class T>
class NRmatrix {
private:
	int nn;
	int mm;
	T **v;
public:
	NRmatrix();
	NRmatrix(int n, int m);			// Zero-based array
	NRmatrix(int n, int m, const T &a);	//Initialize to constant
	NRmatrix(int n, int m, const T *a);	// Initialize to array
	NRmatrix(const NRmatrix &rhs);		// Copy constructor
	NRmatrix & operator=(const NRmatrix &rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T* operator[](const int i);	//subscripting: pointer to row i
	inline const T* operator[](const int i) const;
	inline int nrows() const;
	inline int ncols() const;
	void resize(int newn, int newm); // resize (contents not preserved)
	void assign(int newn, int newm, const T &a); // resize and assign a constant value
	~NRmatrix();



	inline Doub Norm()
	{
		Doub dVal = 0;
		for( long i=0; i<nn; i++)
			for( long j=0; j<mm; j++)
				dVal += SQR( v[i][j] );
		return dVal;
	}

	inline NRmatrix<T> Abs()
	{
		NRmatrix<T> oMat(nn, mm, 0.0);
		for( long i=0; i<nn; i++)
			for( long j=0; j<mm; j++)
				oMat[i][j] = fabs( v[i][j] );
		return oMat;
	}

	inline void Rand(int v_iFrom = 0, int v_iCut = 0, Doub v_iDiv = 1.0)
	{
		for( long i=0; i<nn; i++)
			for( long j=0; j<mm; j++)
				v[i][j] = (v_iFrom + ( !v_iCut ? rand() : rand()%v_iCut))/v_iDiv;
	}

	inline NRmatrix Tr()
	{
		NRmatrix<T> oMat( mm, nn, 0.0 );
		for(int i=0; i<nn; i++)
			for(int j=0; j<mm; j++)
				oMat[j][i] = v[i][j];
		return oMat;
	}

	inline NRmatrix operator*( Doub v_dVal )
	{
		NRmatrix<T> oMat( nn, mm, 0.0 );
		for(int i=0; i<nn; i++)
			for(int j=0; j<mm; j++)
				oMat[i][j] = v[i][j]*v_dVal;
		return oMat;
	}

	inline NRmatrix operator-()
	{
		NRmatrix<T> oMat( nn, mm, 0.0 );
		for(int i=0; i<nn; i++)
			for(int j=0; j<mm; j++)
				oMat[i][j] = -v[i][j];
		return oMat;
	}

	inline NRmatrix operator-(Doub v_dVal)
	{
		NRmatrix<T> oMat( nn, mm, 0.0 );
		for(int i=0; i<nn; i++)
			for(int j=0; j<mm; j++)
				oMat[i][j] = v[i][j] - v_dVal;
		return oMat;
	}


	inline NRmatrix operator+(NRmatrix<T> &v_rMat)
	{
		NRmatrix<T> oMat( nn, mm, 0.0 );
		for(int i=0; i<nn; i++)
			for(int j=0; j<mm; j++)
				oMat[i][j] = v[i][j] + v_rMat[i][j];
		return oMat;
	}

	inline NRmatrix operator*(NRmatrix<T> &v_rMat)
	{
		NRmatrix<T> oMat( nn, v_rMat.ncols(), 0.0 );

		for(int i=0; i<nn; i++)
			for(int j=0; j<v_rMat.ncols(); j++)
			{
				Doub dSum = 0.0;
				for(int k=0; k<mm; k++)
					dSum += v[i][k]*v_rMat[k][j];
				oMat[i][j] = dSum;
			}
		return oMat;
	}

	inline void Copy( NRmatrix<T> &v_rMat )
	{
		if( v_rMat.nrows() <= nn && v_rMat.ncols() <= mm )
			for(int i=0; i<v_rMat.nrows(); i++)
				for(int j=0; j<v_rMat.ncols(); j++)
					v[i][j] = v_rMat[i][j];
		else
		{
			cout << "Wrong matrix sizes" << endl;
			system("PAUSE");
			exit(1);
		}//if
	}//Copy

	NRmatrix& Diag(NRvector<T> &v_rVec)
	{
		NRmatrix<T> oMat( mm, nn, 0.0 );
		for(int i=0; i<nn; i++)
			v[i][i] = v_rVec[i];
		return *this;
	}

	void SetCol(int v_iColumn, Doub v_dVal)
	{
		for(int i=0; i<nn; i++)
			v[i][v_iColumn] = v_dVal;
	}

	void SetCol(int v_iCol, NRvector<T> &v_rVec)
	{
		for(int i=0; i<nn; i++)
			v[i][v_iCol] = v_rVec[v_iCol];
	}

	NRvector<T> GetCol(int v_iCol)
	{
		NRvector<T> oVec( nn, 0.0 );

		for(int i=0; i<nn; i++)
			oVec[i] = v[i][v_iCol];
		return oVec;
	}

	void SetRow(int v_iRow, NRvector<T> &v_rVec)
	{
		for(int i=0; i<mm; i++)
			v[v_iRow][i] = v_rVec[v_iRow];
	}

	Doub Min()
	{
		Doub dVal = this->operator[](0)[0];
		for(int i=0; i<mm; i++)
			for(int j=0; j<nn; j++)
				if( this->operator[](i)[j] < dVal )
					dVal = v[i][j];
		return dVal;
	}
};

template <class T>
NRmatrix<T>::NRmatrix() : nn(0), mm(0), v(NULL) {}

template <class T>
NRmatrix<T>::NRmatrix(int n, int m) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1;i<n;i++) v[i] = v[i-1] + m;
}

template <class T>
NRmatrix<T>::NRmatrix(int n, int m, const T &a) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i=0; i< n; i++) for (j=0; j<m; j++) v[i][j] = a;
}

template <class T>
NRmatrix<T>::NRmatrix(int n, int m, const T *a) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i=0; i< n; i++) for (j=0; j<m; j++) v[i][j] = *a++;
}

template <class T>
NRmatrix<T>::NRmatrix(const NRmatrix &rhs) : nn(rhs.nn), mm(rhs.mm), v(nn>0 ? new T*[nn] : NULL)
{
	int i,j,nel=mm*nn;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
}

template <class T>
NRmatrix<T> & NRmatrix<T>::operator=(const NRmatrix<T> &rhs)
// postcondition: normal assignment via copying has been performed;
//		if matrix and rhs were different sizes, matrix
//		has been resized to match the size of rhs
{
	if (this != &rhs) {
		int i,j,nel;
		if (nn != rhs.nn || mm != rhs.mm) {
			if (v != NULL) {
				delete[] (v[0]);
				delete[] (v);
			}
			nn=rhs.nn;
			mm=rhs.mm;
			v = nn>0 ? new T*[nn] : NULL;
			nel = mm*nn;
			if (v) v[0] = nel>0 ? new T[nel] : NULL;
			for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
		}
		for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
	}
	return *this;
}

template <class T>
inline T* NRmatrix<T>::operator[](const int i)	//subscripting: pointer to row i
{
#ifdef _CHECKBOUNDS_
	if (i<0 || i>=nn) {
		throw("NRmatrix subscript out of bounds");
	}
#endif
	return v[i];
}

template <class T>
inline const T* NRmatrix<T>::operator[](const int i) const
{
#ifdef _CHECKBOUNDS_
	if (i<0 || i>=nn) {
		throw("NRmatrix subscript out of bounds");
	}
#endif
	return v[i];
}

template <class T>
inline int NRmatrix<T>::nrows() const
{
	return nn;
}

template <class T>
inline int NRmatrix<T>::ncols() const
{
	return mm;
}

template <class T>
void NRmatrix<T>::resize(int newn, int newm)
{
	int i,nel;
	if (newn != nn || newm != mm) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		nn = newn;
		mm = newm;
		v = nn>0 ? new T*[nn] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	}
}

template <class T>
void NRmatrix<T>::assign(int newn, int newm, const T& a)
{
	int i,j,nel;
	if (newn != nn || newm != mm) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		nn = newn;
		mm = newm;
		v = nn>0 ? new T*[nn] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	}
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = a;
}

template <class T>
NRmatrix<T>::~NRmatrix()
{
	if (v != NULL) {
		delete[] (v[0]);
		delete[] (v);
	}
}

template <class T>
ostream& operator<<( ostream& v_rStream, NRmatrix<T> &v_rMatrix)
{
	for(int i=0; i<v_rMatrix.nrows(); i++)
	{
		for(int j=0; j<v_rMatrix.ncols(); j++)
			v_rStream<<setw(10)<<setprecision(4)<<fixed<<v_rMatrix[i][j];
		v_rStream<<endl;
	}
	return v_rStream;
}

template <class T>
ostream& operator<<(ostream& v_rStream, NRvector<T> &v_rVec)
{
	for(int i=0; i<v_rVec.size(); i++)
		v_rStream<<setw(10)<<setprecision(4)<<fixed<<v_rVec[i];
	v_rStream<<endl;
	return v_rStream;
}

template <class T>
NRvector<T> operator*(NRmatrix<T> &v_rMat, NRvector<T> &v_rVec)
{
	NRvector<T> oVec( v_rMat.nrows(), 0.0 );
	for(int i=0; i<v_rMat.nrows(); i++)
		for(int j=0; j<v_rMat.ncols(); j++)
			oVec[i] += v_rMat[i][j]*v_rVec[j];
	return oVec;
}



template <class T>
class NRMat3d {
private:
	int nn;
	int mm;
	int kk;
	T ***v;
public:
	NRMat3d();
	NRMat3d(int n, int m, int k);
	inline T** operator[](const int i);	//subscripting: pointer to row i
	inline const T* const * operator[](const int i) const;
	inline int dim1() const;
	inline int dim2() const;
	inline int dim3() const;
	~NRMat3d();
};

template <class T>
NRMat3d<T>::NRMat3d(): nn(0), mm(0), kk(0), v(NULL) {}

template <class T>
NRMat3d<T>::NRMat3d(int n, int m, int k) : nn(n), mm(m), kk(k), v(new T**[n])
{
	int i,j;
	v[0] = new T*[n*m];
	v[0][0] = new T[n*m*k];
	for(j=1; j<m; j++) v[0][j] = v[0][j-1] + k;
	for(i=1; i<n; i++) {
		v[i] = v[i-1] + m;
		v[i][0] = v[i-1][0] + m*k;
		for(j=1; j<m; j++) v[i][j] = v[i][j-1] + k;
	}
}

template <class T>
inline T** NRMat3d<T>::operator[](const int i) //subscripting: pointer to row i
{
	return v[i];
}

template <class T>
inline const T* const * NRMat3d<T>::operator[](const int i) const
{
	return v[i];
}

template <class T>
inline int NRMat3d<T>::dim1() const
{
	return nn;
}

template <class T>
inline int NRMat3d<T>::dim2() const
{
	return mm;
}

template <class T>
inline int NRMat3d<T>::dim3() const
{
	return kk;
}

template <class T>
NRMat3d<T>::~NRMat3d()
{
	if (v != NULL) {
		delete[] (v[0][0]);
		delete[] (v[0]);
		delete[] (v);
	}
}


// basic type names (redefine if your bit lengths don't match)

typedef int Int; // 32 bit integer
typedef unsigned int Uint;

#ifdef _MSC_VER
typedef __int64 Llong; // 64 bit integer
typedef unsigned __int64 Ullong;
#else
typedef long long int Llong; // 64 bit integer
typedef unsigned long long int Ullong;
#endif

typedef char Char; // 8 bit integer
typedef unsigned char Uchar;

typedef double Doub; // default floating type
typedef long double Ldoub;

typedef complex<double> Complex; // default complex type

typedef bool Bool;

// NaN: uncomment one of the following 3 methods of defining a global NaN
// you can test by verifying that (NaN != NaN) is true

static const Doub NaN = numeric_limits<Doub>::quiet_NaN();

//Uint proto_nan[2]={0xffffffff, 0x7fffffff};
//double NaN = *( double* )proto_nan;

//Doub NaN = sqrt(-1.);

// NRvector types

typedef const NRvector<Int> VecInt_I;
typedef NRvector<Int> VecInt, VecInt_O, VecInt_IO;

typedef const NRvector<Uint> VecUint_I;
typedef NRvector<Uint> VecUint, VecUint_O, VecUint_IO;

typedef const NRvector<Llong> VecLlong_I;
typedef NRvector<Llong> VecLlong, VecLlong_O, VecLlong_IO;

typedef const NRvector<Ullong> VecUllong_I;
typedef NRvector<Ullong> VecUllong, VecUllong_O, VecUllong_IO;

typedef const NRvector<Char> VecChar_I;
typedef NRvector<Char> VecChar, VecChar_O, VecChar_IO;

typedef const NRvector<Char*> VecCharp_I;
typedef NRvector<Char*> VecCharp, VecCharp_O, VecCharp_IO;

typedef const NRvector<Uchar> VecUchar_I;
typedef NRvector<Uchar> VecUchar, VecUchar_O, VecUchar_IO;

typedef const NRvector<Doub> VecDoub_I;
typedef NRvector<Doub> VecDoub, VecDoub_O, VecDoub_IO;

typedef const NRvector<Doub*> VecDoubp_I;
typedef NRvector<Doub*> VecDoubp, VecDoubp_O, VecDoubp_IO;

typedef const NRvector<Complex> VecComplex_I;
typedef NRvector<Complex> VecComplex, VecComplex_O, VecComplex_IO;

typedef const NRvector<Bool> VecBool_I;
typedef NRvector<Bool> VecBool, VecBool_O, VecBool_IO;

// matrix types

typedef const NRmatrix<Int> MatInt_I;
typedef NRmatrix<Int> MatInt, MatInt_O, MatInt_IO;

typedef const NRmatrix<Uint> MatUint_I;
typedef NRmatrix<Uint> MatUint, MatUint_O, MatUint_IO;

typedef const NRmatrix<Llong> MatLlong_I;
typedef NRmatrix<Llong> MatLlong, MatLlong_O, MatLlong_IO;

typedef const NRmatrix<Ullong> MatUllong_I;
typedef NRmatrix<Ullong> MatUllong, MatUllong_O, MatUllong_IO;

typedef const NRmatrix<Char> MatChar_I;
typedef NRmatrix<Char> MatChar, MatChar_O, MatChar_IO;

typedef const NRmatrix<Uchar> MatUchar_I;
typedef NRmatrix<Uchar> MatUchar, MatUchar_O, MatUchar_IO;

typedef const NRmatrix<Doub> MatDoub_I;
typedef NRmatrix<Doub> MatDoub, MatDoub_O, MatDoub_IO;

typedef const NRmatrix<Bool> MatBool_I;
typedef NRmatrix<Bool> MatBool, MatBool_O, MatBool_IO;

// 3D matrix types

typedef const NRMat3d<Doub> Mat3DDoub_I;
typedef NRMat3d<Doub> Mat3DDoub, Mat3DDoub_O, Mat3DDoub_IO;

// Floating Point Exceptions for Microsoft compilers

#ifdef _TURNONFPES_
#ifdef _MSC_VER
struct turn_on_floating_exceptions {
	turn_on_floating_exceptions() {
		int cw = _controlfp( 0, 0 );
		cw &=~(EM_INVALID | EM_OVERFLOW | EM_ZERODIVIDE );
		_controlfp( cw, MCW_EM );
	}
};
turn_on_floating_exceptions yes_turn_on_floating_exceptions;
#endif /* _MSC_VER */
#endif /* _TURNONFPES */

#endif /* _NR3_H_ */

