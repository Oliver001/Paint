// ShapeRect.h: interface for the CShapeRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPERECT_H__521BD3CD_5DC9_4BB4_A025_7ED9B710283B__INCLUDED_)
#define AFX_SHAPERECT_H__521BD3CD_5DC9_4BB4_A025_7ED9B710283B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapeRect : public CShape  
{
public:
	virtual void Draw(CDC*pDC);
//	virtual void DrawStroke(CDC*pDC);
//	virtual BOOL IsPointIn(const CPoint &point);
//	virtual void SetCurrentPoint(CPoint &point);
	CShapeRect();
	virtual ~CShapeRect();

};

#endif // !defined(AFX_SHAPERECT_H__521BD3CD_5DC9_4BB4_A025_7ED9B710283B__INCLUDED_)
