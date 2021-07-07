/* --------------------------------------------------- */
/* Automatically generated by mwrap                    */
/* --------------------------------------------------- */

/* Code generated by mwrap 1.0 */
/*
  Copyright statement for mwrap:

  mwrap -- MEX file generation for MATLAB and Octave
  Copyright (c) 2007-2008 David Bindel

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  You may distribute a work that contains part or all of the source code
  generated by mwrap under the terms of your choice.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <mex.h>

#if MX_HAS_INTERLEAVED_COMPLEX
#include <matrix.h>
#endif


/*
 * Records for call profile.
 */
int* mexprofrecord_= NULL;


/*
 * Support routines for copying data into and out of the MEX stubs, R2018a
 */

#if MX_HAS_INTERLEAVED_COMPLEX

void* mxWrapGetP(const mxArray* a, const char* fmt, const char** e)
{
    void* p = NULL;
#ifdef R2008OO
    mxArray* ap;
#endif
    if (mxGetClassID(a) == mxDOUBLE_CLASS && mxIsComplex(a) )
    {
        if( mxGetM(a)*mxGetN(a) == 1 && (*mxGetComplexDoubles(a)).real == 0 )
        return NULL;
    }
    if (mxGetClassID(a) == mxDOUBLE_CLASS && !mxIsComplex(a) )
    {
        if( mxGetM(a)*mxGetN(a) == 1 && *mxGetDoubles(a) == 0)
        return NULL;
    }
    if (mxIsChar(a)) {
        char pbuf[128];
        mxGetString(a, pbuf, sizeof(pbuf));
        sscanf(pbuf, fmt, &p);
    } 
#ifdef R2008OO
    else if (ap = mxGetProperty(a, 0, "mwptr")) {
        return mxWrapGetP(ap, fmt, e);
    }
#endif
    if (p == 0)
        *e = "Invalid pointer";
    return p;
}

mxArray* mxWrapCreateP(void* p, const char* fmt)
{
    if (p == 0) {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetDoubles(z) = 0;
        return z;
    } else {
        char pbuf[128];
        sprintf(pbuf, fmt, p);
        return mxCreateString(pbuf);
    }
}

mxArray* mxWrapStrncpy(const char* s)
{
    if (s) {
        return mxCreateString(s);
    } else {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetDoubles(z) = 0;
        return z;
    }
}

char* mxWrapGetString(const mxArray* a, const char** e)
{
    char* s;
    mwSize slen;
    if (!a || (!mxIsChar(a) && mxGetM(a)*mxGetN(a) > 0)) {
        *e = "Invalid string argument";
        return NULL;
    }
    slen = mxGetM(a)*mxGetN(a) + 1;
    s = (char*) mxMalloc(slen);
    if (mxGetM(a)*mxGetN(a) == 0)
        *s = 0;
    else
        mxGetString(a, s, slen);
    return s;
}


double mxWrapGetScalar(const mxArray* a, const char** e)
{
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS || mxGetM(a)*mxGetN(a) != 1) {
        *e = "Invalid scalar argument";
        return 0;
    }
    if( mxIsComplex(a) )
      return (double) (*mxGetComplexDoubles(a)).real;
    else
      return (double) (*mxGetDoubles(a));
}

#define mxWrapGetArrayDef(func, T) \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* q; \
    mxComplexDouble* z; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument, mxDOUBLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexDoubles(a);	   \
	for (i = 0; i < arraylen; ++i)		\
	  *p++ = (T) (*z++).real;			\
      } \
    else \
      {				   \
	q = mxGetDoubles(a);	   \
	for (i = 0; i < arraylen; ++i)		\
	  *p++ = (T) (*q++);			\
      } \
    return array; \
}


#define mxWrapCopyDef(func, T) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* p;	\
    mxComplexDouble* z; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexDoubles(a);	   \
	for (i = 0; i < n; ++i)		\
	  (*z++).real = (double) *q++;	\
	  (*z++).imag = 0;	\
      } \
    else \
      {				   \
	p = mxGetDoubles(a);	   \
	for (i = 0; i < n; ++i)		\
	  *p++ = (double) *q++;		\
      } \
}


#define mxWrapReturnDef(func, T) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    double* p; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxREAL); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxREAL); \
        p = mxGetDoubles(a); \
        for (i = 0; i < m*n; ++i) \
	  *p++ = (double) *q++;	  \
        return a; \
    } \
}


#define mxWrapGetScalarZDef(func, T, ZT, setz)	\
void func(T* z, const mxArray* a) \
{ \
    if( mxIsComplex(a) ) \
      { \
  setz(z, (ZT) (*mxGetComplexDoubles(a)).real, (ZT) (*mxGetComplexDoubles(a)).imag); \
      } \
    else \
      {				   \
  setz(z, (ZT) (*mxGetComplexDoubles(a)).real, (ZT) 0);	\
      } \
}


#define mxWrapGetArrayZDef(func, T, ZT, setz)      \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* q; \
    mxComplexDouble* z; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument, mxDOUBLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexDoubles(a);	   \
	for (i = 0; i < arraylen; ++i) {	\
	  setz(p, (ZT) (*z).real, (ZT) (*z).imag);	\
  	  ++p; ++z; }					\
      } \
    else \
      {				   \
	q = mxGetDoubles(a);	   \
	for (i = 0; i < arraylen; ++i)	{	\
	  setz(p, (ZT) (*q), (ZT) 0 );		\
          ++p; ++q; }			\
      }						\
    return array; \
}


#define mxWrapCopyZDef(func, T, freal, fimag)	    \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* p;	\
    mxComplexDouble* z; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexDoubles(a);	   \
	for (i = 0; i < n; ++i)	{		\
          (*z).real = freal(*q);			\
	  (*z).imag = fimag(*q);			\
	  ++z; ++q; 	}			\
      } \
    else \
      {				   \
	p = mxGetDoubles(a);	   \
	for (i = 0; i < n; ++i)		\
	  *p++ = freal(*q++);		\
      } \
}


#define mxWrapReturnZDef(func, T, freal, fimag)	      \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    mxComplexDouble* p; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxCOMPLEX); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxCOMPLEX); \
        p = mxGetComplexDoubles(a); \
        for (i = 0; i < m*n; ++i) {	  \
          (*p).real = freal(*q);			\
	  (*p).imag = fimag(*q);			\
	  ++p; ++q; 	}			\
        return a; \
    } \
}






void* mxWrapGetP_single(const mxArray* a, const char* fmt, const char** e)
{
    void* p = NULL;
#ifdef R2008OO
    mxArray* ap;
#endif
    if (mxGetClassID(a) == mxSINGLE_CLASS && mxIsComplex(a) )
    {
        if( mxGetM(a)*mxGetN(a) == 1 && (*mxGetComplexSingles(a)).real == 0 )
        return NULL;
    }
    if (mxGetClassID(a) == mxSINGLE_CLASS && !mxIsComplex(a) )
    {
        if( mxGetM(a)*mxGetN(a) == 1 && *mxGetSingles(a) == 0)
        return NULL;
    }
    if (mxIsChar(a)) {
        char pbuf[128];
        mxGetString(a, pbuf, sizeof(pbuf));
        sscanf(pbuf, fmt, &p);
    } 
#ifdef R2008OO
    else if (ap = mxGetProperty(a, 0, "mwptr")) {
        return mxWrapGetP(ap, fmt, e);
    }
#endif
    if (p == 0)
        *e = "Invalid pointer";
    return p;
}

mxArray* mxWrapCreateP_single(void* p, const char* fmt)
{
    if (p == 0) {
        mxArray* z = mxCreateNumericMatrix(1,1, mxSINGLE_CLASS, mxREAL);
        *mxGetSingles(z) = 0;
        return z;
    } else {
        char pbuf[128];
        sprintf(pbuf, fmt, p);
        return mxCreateString(pbuf);
    }
}

mxArray* mxWrapStrncpy_single(const char* s)
{
    if (s) {
        return mxCreateString(s);
    } else {
        mxArray* z = mxCreateNumericMatrix(1,1, mxSINGLE_CLASS, mxREAL);
        *mxGetSingles(z) = 0;
        return z;
    }
}

char* mxWrapGetString_single(const mxArray* a, const char** e)
{
    char* s;
    mwSize slen;
    if (!a || (!mxIsChar(a) && mxGetM(a)*mxGetN(a) > 0)) {
        *e = "Invalid string argument";
        return NULL;
    }
    slen = mxGetM(a)*mxGetN(a) + 1;
    s = (char*) mxMalloc(slen);
    if (mxGetM(a)*mxGetN(a) == 0)
        *s = 0;
    else
        mxGetString(a, s, slen);
    return s;
}


float mxWrapGetScalar_single(const mxArray* a, const char** e)
{
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS || mxGetM(a)*mxGetN(a) != 1) {
        *e = "Invalid scalar argument";
        return 0;
    }
    if( mxIsComplex(a) )
      return (float) (*mxGetComplexSingles(a)).real;
    else
      return (float) (*mxGetSingles(a));
}

#define mxWrapGetArrayDef_single(func, T) \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    float* q; \
    mxComplexSingle* z; \
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS) { \
        *e = "Invalid array argument, mxSINGLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexSingles(a);	   \
	for (i = 0; i < arraylen; ++i)		\
	  *p++ = (T) (*z++).real;			\
      } \
    else \
      {				   \
	q = mxGetSingles(a);	   \
	for (i = 0; i < arraylen; ++i)		\
	  *p++ = (T) (*q++);			\
      } \
    return array; \
}


#define mxWrapCopyDef_single(func, T) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    float* p;	\
    mxComplexSingle* z; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexSingles(a);	   \
	for (i = 0; i < n; ++i)		\
	  (*z++).real = (float) *q++;	\
	  (*z++).imag = 0;	\
      } \
    else \
      {				   \
	p = mxGetSingles(a);	   \
	for (i = 0; i < n; ++i)		\
	  *p++ = (float) *q++;		\
      } \
}


#define mxWrapReturnDef_single(func, T) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    float* p; \
    if (!q) { \
        return mxCreateNumericMatrix(0,0, mxSINGLE_CLASS, mxREAL); \
    } else { \
        mxArray* a = mxCreateNumericMatrix(m,n, mxSINGLE_CLASS, mxREAL); \
        p = mxGetSingles(a); \
        for (i = 0; i < m*n; ++i) \
	  *p++ = (float) *q++;	  \
        return a; \
    } \
}


#define mxWrapGetScalarZDef_single(func, T, ZT, setz)	\
void func(T* z, const mxArray* a) \
{ \
    if( mxIsComplex(a) ) \
      { \
  setz(z, (ZT) (*mxGetComplexSingles(a)).real, (ZT) (*mxGetComplexSingles(a)).imag); \
      } \
    else \
      {				   \
  setz(z, (ZT) (*mxGetComplexSingles(a)).real, (ZT) 0);	\
      } \
}


#define mxWrapGetArrayZDef_single(func, T, ZT, setz)      \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    float* q; \
    mxComplexSingle* z; \
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS) { \
        *e = "Invalid array argument, mxSINGLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexSingles(a);	   \
	for (i = 0; i < arraylen; ++i) {	\
	  setz(p, (ZT) (*z).real, (ZT) (*z).imag);	\
  	  ++p; ++z; }					\
      } \
    else \
      {				   \
	q = mxGetSingles(a);	   \
	for (i = 0; i < arraylen; ++i)	{	\
	  setz(p, (ZT) (*q), (ZT) 0 );		\
          ++p; ++q; }			\
      }						\
    return array; \
}


#define mxWrapCopyZDef_single(func, T, freal, fimag)	    \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    float* p;	\
    mxComplexSingle* z; \
    if( mxIsComplex(a) ) \
      { \
	z = mxGetComplexSingles(a);	   \
	for (i = 0; i < n; ++i)	{		\
          (*z).real = freal(*q);			\
	  (*z).imag = fimag(*q);			\
	  ++z; ++q; 	}			\
      } \
    else \
      {				   \
	p = mxGetSingles(a);	   \
	for (i = 0; i < n; ++i)		\
	  *p++ = freal(*q++);		\
      } \
}


#define mxWrapReturnZDef_single(func, T, freal, fimag)	      \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    mxComplexSingle* p; \
    if (!q) { \
        return mxCreateNumericMatrix(0,0, mxSINGLE_CLASS, mxCOMPLEX); \
    } else { \
        mxArray* a = mxCreateNumericMatrix(m,n, mxSINGLE_CLASS, mxCOMPLEX); \
        p = mxGetComplexSingles(a); \
        for (i = 0; i < m*n; ++i) {	  \
          (*p).real = freal(*q);			\
	  (*p).imag = fimag(*q);			\
	  ++p; ++q; 	}			\
        return a; \
    } \
}



#else

/*
 * Support routines for copying data into and out of the MEX stubs, -R2017b
 */

void* mxWrapGetP(const mxArray* a, const char* fmt, const char** e)
{
    void* p = 0;
#ifdef R2008OO
    mxArray* ap;
#endif
    if (mxGetClassID(a) == mxDOUBLE_CLASS && 
        mxGetM(a)*mxGetN(a) == 1 && *mxGetPr(a) == 0)
        return p;
    if (mxIsChar(a)) {
        char pbuf[128];
        mxGetString(a, pbuf, sizeof(pbuf));
        sscanf(pbuf, fmt, &p);
    } 
#ifdef R2008OO
    else if (ap = mxGetProperty(a, 0, "mwptr")) {
        return mxWrapGetP(ap, fmt, e);
    }
#endif
    if (p == 0)
        *e = "Invalid pointer";
    return p;
}

mxArray* mxWrapCreateP(void* p, const char* fmt)
{
    if (p == 0) {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetPr(z) = 0;
        return z;
    } else {
        char pbuf[128];
        sprintf(pbuf, fmt, p);
        return mxCreateString(pbuf);
    }
}

mxArray* mxWrapStrncpy(const char* s)
{
    if (s) {
        return mxCreateString(s);
    } else {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetPr(z) = 0;
        return z;
    }
}

double mxWrapGetScalar(const mxArray* a, const char** e)
{
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS || mxGetM(a)*mxGetN(a) != 1) {
        *e = "Invalid scalar argument";
        return 0;
    }
    return *mxGetPr(a);
}

char* mxWrapGetString(const mxArray* a, const char** e)
{
    char* s;
    mwSize slen;
    if (!a || (!mxIsChar(a) && mxGetM(a)*mxGetN(a) > 0)) {
        *e = "Invalid string argument";
        return NULL;
    }
    slen = mxGetM(a)*mxGetN(a) + 1;
    s = (char*) mxMalloc(slen);
    if (mxGetM(a)*mxGetN(a) == 0)
        *s = 0;
    else
        mxGetString(a, s, slen);
    return s;
}


#define mxWrapGetArrayDef(func, T) \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* q; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument, mxDOUBLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    q = mxGetPr(a); \
    for (i = 0; i < arraylen; ++i) \
        *p++ = (T) (*q++); \
    return array; \
}


#define mxWrapCopyDef(func, T) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* p = mxGetPr(a); \
    for (i = 0; i < n; ++i) \
        *p++ = *q++; \
}


#define mxWrapReturnDef(func, T) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    double* p; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxREAL); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxREAL); \
        p = mxGetPr(a); \
        for (i = 0; i < m*n; ++i) \
            *p++ = *q++; \
        return a; \
    } \
}


#define mxWrapGetScalarZDef(func, T, ZT, setz) \
void func(T* z, const mxArray* a) \
{ \
    double* pr = mxGetPr(a); \
    double* pi = mxGetPi(a); \
    setz(z, (ZT) *pr, (pi ? (ZT) *pi : (ZT) 0)); \
}


#define mxWrapGetArrayZDef(func, T, ZT, setz) \
T* func(const mxArray* a, const char** e) \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* qr; \
    double* qi; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument, mxDOUBLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    qr = mxGetPr(a); \
    qi = mxGetPi(a); \
    for (i = 0; i < arraylen; ++i) { \
        ZT val_qr = *qr++; \
        ZT val_qi = (qi ? (ZT) *qi++ : (ZT) 0); \
        setz(p, val_qr, val_qi); \
        ++p; \
    } \
    return array; \
}


#define mxWrapCopyZDef(func, T, real, imag) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* pr = mxGetPr(a); \
    double* pi = mxGetPi(a); \
    for (i = 0; i < n; ++i) { \
        *pr++ = real(*q); \
        *pi++ = imag(*q); \
        ++q; \
    } \
}


#define mxWrapReturnZDef(func, T, real, imag) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    double* pr; \
    double* pi; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxCOMPLEX); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxCOMPLEX); \
        pr = mxGetPr(a); \
        pi = mxGetPi(a); \
        for (i = 0; i < m*n; ++i) { \
            *pr++ = real(*q); \
            *pi++ = imag(*q); \
            ++q; \
        } \
        return a; \
    } \
}






void* mxWrapGetP_single(const mxArray* a, const char* fmt, const char** e)
{
    void* p = 0;
#ifdef R2008OO
    mxArray* ap;
#endif
    if (mxGetClassID(a) == mxSINGLE_CLASS && 
        mxGetM(a)*mxGetN(a) == 1 && *((float*)mxGetData(a)) == 0)
        return p;
    if (mxIsChar(a)) {
        char pbuf[128];
        mxGetString(a, pbuf, sizeof(pbuf));
        sscanf(pbuf, fmt, &p);
    } 
#ifdef R2008OO
    else if (ap = mxGetProperty(a, 0, "mwptr")) {
        return mxWrapGetP(ap, fmt, e);
    }
#endif
    if (p == 0)
        *e = "Invalid pointer";
    return p;
}

mxArray* mxWrapCreateP_single(void* p, const char* fmt)
{
    if (p == 0) {
        mxArray* z = mxCreateNumericMatrix(1,1, mxSINGLE_CLASS, mxREAL);
        *((float*)mxGetData(z)) = 0;
        return z;
    } else {
        char pbuf[128];
        sprintf(pbuf, fmt, p);
        return mxCreateString(pbuf);
    }
}
mxArray* mxWrapStrncpy_single(const char* s)
{
    if (s) {
        return mxCreateString(s);
    } else {
        mxArray* z = mxCreateNumericMatrix(1,1, mxSINGLE_CLASS, mxREAL);
        *((float*)mxGetData(z)) = 0;
        return z;
    }
}

float mxWrapGetScalar_single(const mxArray* a, const char** e)
{
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS || mxGetM(a)*mxGetN(a) != 1) {
        *e = "Invalid scalar argument";
        return 0;
    }
    return *((float*)mxGetData(a));
}

char* mxWrapGetString_single(const mxArray* a, const char** e)
{
    char* s;
    mwSize slen;
    if (!a || (!mxIsChar(a) && mxGetM(a)*mxGetN(a) > 0)) {
        *e = "Invalid string argument, mxSINGLE_CLASS expected";
        return NULL;
    }
    slen = mxGetM(a)*mxGetN(a) + 1;
    s = (char*) mxMalloc(slen);
    if (mxGetM(a)*mxGetN(a) == 0)
        *s = 0;
    else
        mxGetString(a, s, slen);
    return s;
}


#define mxWrapGetArrayDef_single(func, T) \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    float* q; \
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS) { \
        *e = "Invalid array argument, mxSINGLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    q = (float*) mxGetData(a);	   \
    for (i = 0; i < arraylen; ++i) \
        *p++ = (T) (*q++); \
    return array; \
}


#define mxWrapCopyDef_single(func, T) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    float* p = (float*) mxGetData(a);		\
    for (i = 0; i < n; ++i) \
        *p++ = *q++; \
}


#define mxWrapReturnDef_single(func, T) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    float* p; \
    if (!q) { \
      return mxCreateNumericMatrix(0,0, mxSINGLE_CLASS, mxREAL); \
    } else { \
        mxArray* a = mxCreateNumericMatrix(m,n, mxSINGLE_CLASS, mxREAL);\
        p = (float*) mxGetData(a);				\
        for (i = 0; i < m*n; ++i) \
            *p++ = *q++; \
        return a; \
    } \
}


#define mxWrapGetScalarZDef_single(func, T, ZT, setz) \
void func(T* z, const mxArray* a) \
{ \
    float* pr = (float*) mxGetData(a);		\
    float* pi = (float*) mxGetImagData(a);		 \
    setz(z, (ZT) *pr, (pi ? (ZT) *pi : (ZT) 0)); \
}


#define mxWrapGetArrayZDef_single(func, T, ZT, setz) \
T* func(const mxArray* a, const char** e) \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    float* qr; \
    float* qi; \
    if (!a || mxGetClassID(a) != mxSINGLE_CLASS) { \
        *e = "Invalid array argument, mxSINGLE_CLASS expected"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    qr = (float*) mxGetData(a);			\
    qi = (float*) mxGetImagData(a);			\
    for (i = 0; i < arraylen; ++i) { \
        ZT val_qr = *qr++; \
        ZT val_qi = (qi ? (ZT) *qi++ : (ZT) 0); \
        setz(p, val_qr, val_qi); \
        ++p; \
    } \
    return array; \
}


#define mxWrapCopyZDef_single(func, T, real, imag) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    float* pr = (float*) mxGetData(a);		\
    float* pi = (float*) mxGetImagData(a);		\
    for (i = 0; i < n; ++i) { \
        *pr++ = real(*q); \
        *pi++ = imag(*q); \
        ++q; \
    } \
}


#define mxWrapReturnZDef_single(func, T, real, imag) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    float* pr; \
    float* pi; \
    if (!q) { \
      return mxCreateNumericMatrix(0,0, mxSINGLE_CLASS, mxCOMPLEX); \
    } else { \
        mxArray* a = mxCreateNumericMatrix(m,n, mxSINGLE_CLASS, mxCOMPLEX);\
        pr = (float*) mxGetData(a);					\
        pi = (float*) mxGetImagData(a);					\
        for (i = 0; i < m*n; ++i) { \
            *pr++ = real(*q); \
            *pi++ = imag(*q); \
            ++q; \
        } \
        return a; \
    } \
}





#endif

 #include <lapacke.h>
 #include <omp.h>

 void factor_banded_batch(int n, int kl, int ku, double *A, int *ipiv, int nbatch, int nthreads)
 {
     int info;
     int ldab = 2*kl+ku+1;
     #pragma omp parallel for num_threads(nthreads) schedule(static)
     for (int k=0; k<nbatch; ++k) {
         LAPACKE_dgbtrf(LAPACK_COL_MAJOR, n, n, kl, ku, A+k*ldab*n, ldab, ipiv+k*n);
     }
 }

 void solve_banded_batch(int n, int kl, int ku, double *A, int *ipiv, double *b, int nbatch, int nthreads)
 {
     char trans = 'n';
     int nrhs = 1;
     int info;
     int ldab = 2*kl+ku+1;
     int ldb = n;
     #pragma omp parallel for num_threads(nthreads) schedule(static)
     for (int k=0; k<nbatch; ++k) {
         LAPACKE_dgbtrs(LAPACK_COL_MAJOR, trans, n, kl, ku, nrhs, A+k*ldab*n, ldab, ipiv+k*n, b+k*n, ldb);
     }
 }




/* Array copier definitions */
mxWrapGetArrayDef(mxWrapGetArray_bool, bool)
mxWrapCopyDef    (mxWrapCopy_bool,     bool)
mxWrapReturnDef  (mxWrapReturn_bool,   bool)
mxWrapGetArrayDef_single(mxWrapGetArray_single_bool, bool)
mxWrapCopyDef_single    (mxWrapCopy_single_bool,     bool)
mxWrapReturnDef_single  (mxWrapReturn_single_bool,   bool)
mxWrapGetArrayDef(mxWrapGetArray_char, char)
mxWrapCopyDef    (mxWrapCopy_char,     char)
mxWrapReturnDef  (mxWrapReturn_char,   char)
mxWrapGetArrayDef_single(mxWrapGetArray_single_char, char)
mxWrapCopyDef_single    (mxWrapCopy_single_char,     char)
mxWrapReturnDef_single  (mxWrapReturn_single_char,   char)
mxWrapGetArrayDef(mxWrapGetArray_double, double)
mxWrapCopyDef    (mxWrapCopy_double,     double)
mxWrapReturnDef  (mxWrapReturn_double,   double)
mxWrapGetArrayDef_single(mxWrapGetArray_single_double, double)
mxWrapCopyDef_single    (mxWrapCopy_single_double,     double)
mxWrapReturnDef_single  (mxWrapReturn_single_double,   double)
mxWrapGetArrayDef(mxWrapGetArray_float, float)
mxWrapCopyDef    (mxWrapCopy_float,     float)
mxWrapReturnDef  (mxWrapReturn_float,   float)
mxWrapGetArrayDef_single(mxWrapGetArray_single_float, float)
mxWrapCopyDef_single    (mxWrapCopy_single_float,     float)
mxWrapReturnDef_single  (mxWrapReturn_single_float,   float)
mxWrapGetArrayDef(mxWrapGetArray_int, int)
mxWrapCopyDef    (mxWrapCopy_int,     int)
mxWrapReturnDef  (mxWrapReturn_int,   int)
mxWrapGetArrayDef_single(mxWrapGetArray_single_int, int)
mxWrapCopyDef_single    (mxWrapCopy_single_int,     int)
mxWrapReturnDef_single  (mxWrapReturn_single_int,   int)
mxWrapGetArrayDef(mxWrapGetArray_long, long)
mxWrapCopyDef    (mxWrapCopy_long,     long)
mxWrapReturnDef  (mxWrapReturn_long,   long)
mxWrapGetArrayDef_single(mxWrapGetArray_single_long, long)
mxWrapCopyDef_single    (mxWrapCopy_single_long,     long)
mxWrapReturnDef_single  (mxWrapReturn_single_long,   long)
mxWrapGetArrayDef(mxWrapGetArray_ptrdiff_t, ptrdiff_t)
mxWrapCopyDef    (mxWrapCopy_ptrdiff_t,     ptrdiff_t)
mxWrapReturnDef  (mxWrapReturn_ptrdiff_t,   ptrdiff_t)
mxWrapGetArrayDef_single(mxWrapGetArray_single_ptrdiff_t, ptrdiff_t)
mxWrapCopyDef_single    (mxWrapCopy_single_ptrdiff_t,     ptrdiff_t)
mxWrapReturnDef_single  (mxWrapReturn_single_ptrdiff_t,   ptrdiff_t)
mxWrapGetArrayDef(mxWrapGetArray_short, short)
mxWrapCopyDef    (mxWrapCopy_short,     short)
mxWrapReturnDef  (mxWrapReturn_short,   short)
mxWrapGetArrayDef_single(mxWrapGetArray_single_short, short)
mxWrapCopyDef_single    (mxWrapCopy_single_short,     short)
mxWrapReturnDef_single  (mxWrapReturn_single_short,   short)
mxWrapGetArrayDef(mxWrapGetArray_size_t, size_t)
mxWrapCopyDef    (mxWrapCopy_size_t,     size_t)
mxWrapReturnDef  (mxWrapReturn_size_t,   size_t)
mxWrapGetArrayDef_single(mxWrapGetArray_single_size_t, size_t)
mxWrapCopyDef_single    (mxWrapCopy_single_size_t,     size_t)
mxWrapReturnDef_single  (mxWrapReturn_single_size_t,   size_t)

/* ---- BandedBatch.mw: 77 ----
 * factor_banded_batch(int n, int kl, int ku, inout double[na] A, output int[nb] ipiv, int nbatch, int nthreads);
 */
static const char* stubids1_ = "factor_banded_batch(i int, i int, i int, io double[x], o int[x], i int, i int)";

void mexStub1(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    int         in0_;    /* n          */
    int         in1_;    /* kl         */
    int         in2_;    /* ku         */
    double*     in3_ =0; /* A          */
    int         in4_;    /* nbatch     */
    int         in5_;    /* nthreads   */
    int*        out1_=0; /* ipiv       */
    mwSize      dim6_;   /* na         */
    mwSize      dim7_;   /* nb         */

    dim6_ = (mwSize) mxWrapGetScalar(prhs[6], &mw_err_txt_);
    dim7_ = (mwSize) mxWrapGetScalar(prhs[7], &mw_err_txt_);

    if (mxGetM(prhs[3])*mxGetN(prhs[3]) != dim6_) {
        mw_err_txt_ = "Bad argument size: A";        goto mw_err_label;
    }

    if( mxGetClassID(prhs[0]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in0_ = (int) mxWrapGetScalar(prhs[0], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[1]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[2]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[3])*mxGetN(prhs[3]) != 0) {
        in3_ = mxWrapGetArray_double(prhs[3], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in3_ = NULL;
    if( mxGetClassID(prhs[4]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in4_ = (int) mxWrapGetScalar(prhs[4], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[5]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in5_ = (int) mxWrapGetScalar(prhs[5], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    out1_ = (int*) mxMalloc(dim7_*sizeof(int));
    if (mexprofrecord_)
        mexprofrecord_[1]++;
    factor_banded_batch(in0_, in1_, in2_, in3_, out1_, in4_, in5_);
    plhs[0] = mxCreateDoubleMatrix(dim6_, 1, mxREAL);
    mxWrapCopy_double(plhs[0], in3_, dim6_);
    plhs[1] = mxCreateDoubleMatrix(dim7_, 1, mxREAL);
    mxWrapCopy_int(plhs[1], out1_, dim7_);

mw_err_label:
    if (in3_)  mxFree(in3_);
    if (out1_) mxFree(out1_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ---- BandedBatch.mw: 107 ----
 * solve_banded_batch(int n, int kl, int ku, double[na] A, int[nb] ipiv, inout double[nb] x, int nbatch, int nthreads);
 */
static const char* stubids2_ = "solve_banded_batch(i int, i int, i int, i double[x], i int[x], io double[x], i int, i int)";

void mexStub2(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    int         in0_;    /* n          */
    int         in1_;    /* kl         */
    int         in2_;    /* ku         */
    double*     in3_ =0; /* A          */
    int*        in4_ =0; /* ipiv       */
    double*     in5_ =0; /* x          */
    int         in6_;    /* nbatch     */
    int         in7_;    /* nthreads   */
    mwSize      dim8_;   /* na         */
    mwSize      dim9_;   /* nb         */
    mwSize      dim10_;   /* nb         */

    dim8_ = (mwSize) mxWrapGetScalar(prhs[8], &mw_err_txt_);
    dim9_ = (mwSize) mxWrapGetScalar(prhs[9], &mw_err_txt_);
    dim10_ = (mwSize) mxWrapGetScalar(prhs[10], &mw_err_txt_);

    if (mxGetM(prhs[3])*mxGetN(prhs[3]) != dim8_) {
        mw_err_txt_ = "Bad argument size: A";        goto mw_err_label;
    }

    if (mxGetM(prhs[4])*mxGetN(prhs[4]) != dim9_) {
        mw_err_txt_ = "Bad argument size: ipiv";        goto mw_err_label;
    }

    if (mxGetM(prhs[5])*mxGetN(prhs[5]) != dim10_) {
        mw_err_txt_ = "Bad argument size: x";        goto mw_err_label;
    }

    if( mxGetClassID(prhs[0]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in0_ = (int) mxWrapGetScalar(prhs[0], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[1]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[2]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[3])*mxGetN(prhs[3]) != 0) {
        if( mxGetClassID(prhs[3]) != mxDOUBLE_CLASS )
            mw_err_txt_ = "Invalid array argument, mxDOUBLE_CLASS expected";
        if (mw_err_txt_) goto mw_err_label;
#if MX_HAS_INTERLEAVED_COMPLEX
        in3_ = mxGetDoubles(prhs[3]);
#else
        in3_ = mxGetPr(prhs[3]);
#endif
    } else
        in3_ = NULL;
    if (mxGetM(prhs[4])*mxGetN(prhs[4]) != 0) {
        in4_ = mxWrapGetArray_int(prhs[4], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in4_ = NULL;
    if (mxGetM(prhs[5])*mxGetN(prhs[5]) != 0) {
        in5_ = mxWrapGetArray_double(prhs[5], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in5_ = NULL;
    if( mxGetClassID(prhs[6]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in6_ = (int) mxWrapGetScalar(prhs[6], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if( mxGetClassID(prhs[7]) != mxDOUBLE_CLASS )
        mw_err_txt_ = "Invalid scalar argument, mxDOUBLE_CLASS expected";
    if (mw_err_txt_) goto mw_err_label;
    in7_ = (int) mxWrapGetScalar(prhs[7], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mexprofrecord_)
        mexprofrecord_[2]++;
    solve_banded_batch(in0_, in1_, in2_, in3_, in4_, in5_, in6_, in7_);
    plhs[0] = mxCreateDoubleMatrix(dim10_, 1, mxREAL);
    mxWrapCopy_double(plhs[0], in5_, dim10_);

mw_err_label:
    if (in4_)  mxFree(in4_);
    if (in5_)  mxFree(in5_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ----
 */
void mexFunction(int nlhs, mxArray* plhs[],
                 int nrhs, const mxArray* prhs[])
{
    char id[512];
    if (nrhs == 0) {
        mexPrintf("Mex function installed\n");
        return;
    }

    if (mxGetString(prhs[0], id, sizeof(id)) != 0)
        mexErrMsgTxt("Identifier should be a string");
    else if (strcmp(id, stubids1_) == 0)
        mexStub1(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, stubids2_) == 0)
        mexStub2(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, "*profile on*") == 0) {
        if (!mexprofrecord_) {
            mexprofrecord_ = (int*) malloc(3 * sizeof(int));
            mexLock();
        }
        memset(mexprofrecord_, 0, 3 * sizeof(int));
    } else if (strcmp(id, "*profile off*") == 0) {
        if (mexprofrecord_) {
            free(mexprofrecord_);
            mexUnlock();
        }
        mexprofrecord_ = NULL;
    } else if (strcmp(id, "*profile report*") == 0) {
        if (!mexprofrecord_)
            mexPrintf("Profiler inactive\n");
        mexPrintf("%d calls to BandedBatch.mw:77\n", mexprofrecord_[1]);
        mexPrintf("%d calls to BandedBatch.mw:107\n", mexprofrecord_[2]);
    } else if (strcmp(id, "*profile log*") == 0) {
        FILE* logfp;
        if (nrhs != 2 || mxGetString(prhs[1], id, sizeof(id)) != 0)
            mexErrMsgTxt("Must have two string arguments");
        logfp = fopen(id, "w+");
        if (!logfp)
            mexErrMsgTxt("Cannot open log for output");
        if (!mexprofrecord_)
            fprintf(logfp, "Profiler inactive\n");
        fprintf(logfp, "%d calls to BandedBatch.mw:77\n", mexprofrecord_[1]);
        fprintf(logfp, "%d calls to BandedBatch.mw:107\n", mexprofrecord_[2]);
        fclose(logfp);
    } else
        mexErrMsgTxt("Unknown identifier");
}
