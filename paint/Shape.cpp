// Shape.cpp: implementation of the CShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "Shape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape::CShape()
{

}

CShape::~CShape()
{

}

void CShape::ReSize(CRect newPos)
{
	ASSERT(m_points.GetSize()>=2);

	if ((m_points[0].x-m_points[1].x)*(m_points[0].y-m_points[1].y)<0)
	{
		m_points.ElementAt(0) = CPoint(newPos.left, newPos.bottom);
		m_points.ElementAt(1) = CPoint(newPos.right, newPos.top);
	}
	else
	{
		m_points.ElementAt(0) = CPoint(newPos.left, newPos.top);
		m_points.ElementAt(1) = CPoint(newPos.right, newPos.bottom);
	}
	
}

void CShape::Move(int x, int y)
{
	int n = m_points.GetSize();
	for(int i = 0; i < n; i ++){
		m_points.ElementAt(i).x += x;
		m_points.ElementAt(i).y += y;
	}
}

void CShape::DrawStroke(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	
	///
	/////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////



	if(m_bSelected && m_points.GetSize() == 2)
	{
		m_tracker.m_nStyle = CRectTracker::resizeOutside|CRectTracker::solidLine;
		m_tracker.m_rect.SetRect(m_points.GetAt(0), m_points.GetAt(1));
		m_tracker.m_rect.NormalizeRect();
		m_tracker.Draw(pDC);
	}
	pDC->SelectObject(pOld);
}

BOOL CShape::IsPointIn(const CPoint &point)
{
	
	return TRUE;
}

void CShape::ReDrawStroke(CDC *pDC, CPoint point)
{
// 	if(m_points.GetSize() < 2){
// 		if(m_points.GetSize() == 1){
// 			m_points.Add(point);
// 			DrawStroke(pDC);
// 		}
// 		return ;
// 	}
// 	pDC->SetROP2(R2_NOTXORPEN);
// 	
// 	DrawStroke(pDC);
// 	SetCurrentPoint(point);
// 	DrawStroke(pDC);
}

void CShape::SetCurrentPoint(CPoint point)
{
	if (m_points.GetSize()<2)
	{
		m_points.Add(point);
	}
	else
	{
		m_points.ElementAt(1) = point;
	}
}
