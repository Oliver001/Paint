// ShapeFont.h: interface for the CShapeFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEFONT_H__E8575ECB_8FFC_4C46_A786_149BF57C307C__INCLUDED_)
#define AFX_SHAPEFONT_H__E8575ECB_8FFC_4C46_A786_149BF57C307C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapeFont : public CShape  
{
public:
	LOGFONT m_Font;
	CString text;
//	void Draw(CDC* pDC);
	CShapeFont();
	virtual ~CShapeFont();
};

#endif // !defined(AFX_SHAPEFONT_H__E8575ECB_8FFC_4C46_A786_149BF57C307C__INCLUDED_)
