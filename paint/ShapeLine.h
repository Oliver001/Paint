// ShapeLine.h: interface for the CShapeLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPELINE_H__B831BF2D_866A_4890_9E1E_9C8C0F0F0421__INCLUDED_)
#define AFX_SHAPELINE_H__B831BF2D_866A_4890_9E1E_9C8C0F0F0421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapeLine : public CShape  
{
public:
	virtual void Draw(CDC*pDC);
//	virtual void DrawStroke(CDC*pDC);
//	virtual BOOL IsPointIn(const CPoint &point);
//	virtual void SetCurrentPoint(CPoint &point);
	CShapeLine();
	virtual ~CShapeLine();

};

#endif // !defined(AFX_SHAPELINE_H__B831BF2D_866A_4890_9E1E_9C8C0F0F0421__INCLUDED_)
