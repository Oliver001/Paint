// ShapeSelect.cpp: implementation of the CShapeSelect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapeSelect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeSelect::CShapeSelect()
{

}

CShapeSelect::~CShapeSelect()
{

}

void CShapeSelect::Draw(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(m_points[0].x,m_points[0].y,m_points[1].x,m_points[1].y);
	
	pDC->SelectObject(pOld);
	pNew.DeleteObject();
	
}