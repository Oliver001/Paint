// ShapeEllipse.h: interface for the CShapeEllipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEELLIPSE_H__15CAD421_1319_4B80_82A0_8258EBEA9107__INCLUDED_)
#define AFX_SHAPEELLIPSE_H__15CAD421_1319_4B80_82A0_8258EBEA9107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapeEllipse : public CShape  
{
public:
	virtual void Draw(CDC*pDC);
//	virtual void DrawStroke(CDC*pDC);
//	virtual BOOL IsPointIn(const CPoint &point);
//	virtual void SetCurrentPoint(CPoint &point);
	CShapeEllipse();
	virtual ~CShapeEllipse();

};

#endif // !defined(AFX_SHAPEELLIPSE_H__15CAD421_1319_4B80_82A0_8258EBEA9107__INCLUDED_)
