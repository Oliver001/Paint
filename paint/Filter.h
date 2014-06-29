// Filter.h: interface for the CFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTER_H__C2C9EFF4_8AD6_4FB7_83F9_C9E23528A65E__INCLUDED_)
#define AFX_FILTER_H__C2C9EFF4_8AD6_4FB7_83F9_C9E23528A65E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"
class CFilter  
{
public:
	void Diffuse(CDC *pDC, int x1, int y1, int x2, int y2);
	void Inlay(CDC *pDC, int x1, int y1, int x2, int y2);
	void Relief(CDC *pDC, int x1, int y1, int x2, int y2);
	void Sharpen(CDC *pDC, int x1, int y1, int x2, int y2);
	void Neonred(CDC *pDC, int x1, int y1, int x2, int y2);
	void Sleek(CDC *pDC, int x1, int y1, int x2, int y2);
	void Backward(CDC *pDC,int x1,int y1,int x2,int y2);
	void Exposure(CDC *pDC,int x1,int y1,int x2,int y2);
	CFilter();
	virtual ~CFilter();

};

#endif // !defined(AFX_FILTER_H__C2C9EFF4_8AD6_4FB7_83F9_C9E23528A65E__INCLUDED_)
