// ShapeSelect.h: interface for the CShapeSelect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPESELECT_H__838B91B6_25B0_4EA7_A0BE_DF98861639D9__INCLUDED_)
#define AFX_SHAPESELECT_H__838B91B6_25B0_4EA7_A0BE_DF98861639D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

enum selectType {ONLYSELECT,SELECTCOPY,SELECTCUT,SELECTPASTE};

class CShapeSelect : public CShape  
{
public:
	selectType type;
	void SetDC(CDC* pDC,int w,int h);
	void SetRect();
	CRect selectRect;
	CDC* selectDC;
	virtual void Draw(CDC*pDC);
	CShapeSelect();
	virtual ~CShapeSelect();
};

#endif // !defined(AFX_SHAPESELECT_H__838B91B6_25B0_4EA7_A0BE_DF98861639D9__INCLUDED_)
