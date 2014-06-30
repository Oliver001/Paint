// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__D1974F44_FF36_4F31_B929_08D3C9DEB899__INCLUDED_)
#define AFX_SHAPE_H__D1974F44_FF36_4F31_B929_08D3C9DEB899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxwin.h>
#include <math.h>
#include <afxplex_.h>
#include <afxtempl.h>
#include "MyTracker.h"
enum DrawType{LINE,CIRCLE,RECTANGLE,TRIANGLE,FIVEANGLE,SELECT};

class CShape : public CObject  
{
public:
	CShape();
	virtual ~CShape();
public:
	virtual void Draw(CDC*pDC)=0;
	virtual void SetCurrentPoint(CPoint point);
	virtual void ReDrawStroke(CDC *pDC, CPoint point);
	virtual BOOL IsPointIn(const CPoint &point);
	virtual void DrawStroke(CDC *pDC);
	virtual void Move(int x, int y);
	virtual void ReSize(CRect newPos);
	COLORREF m_color;
	int m_nPenStyle;
	int m_nPenWidth;
	int m_nDrawType;
	bool m_bSelected;
	CArray<CPoint, CPoint> m_points;
	CMyTracker m_tracker;
};

#endif // !defined(AFX_SHAPE_H__D1974F44_FF36_4F31_B929_08D3C9DEB899__INCLUDED_)