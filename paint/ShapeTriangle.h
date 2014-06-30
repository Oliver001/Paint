// ShapeTriangle.h: interface for the CShapeTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPETRIANGLE_H__06EE7575_5F94_40B0_8BDB_5F6973ADF1D0__INCLUDED_)
#define AFX_SHAPETRIANGLE_H__06EE7575_5F94_40B0_8BDB_5F6973ADF1D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapeTriangle : public CShape  
{
public:
	virtual void Draw(CDC*pDC);
	CShapeTriangle();
	virtual ~CShapeTriangle();

};

#endif // !defined(AFX_SHAPETRIANGLE_H__06EE7575_5F94_40B0_8BDB_5F6973ADF1D0__INCLUDED_)
