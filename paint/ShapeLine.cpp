// ShapeLine.cpp: implementation of the CShapeLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapeLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeLine::CShapeLine()
{
	m_nDrawType = LINE;
	m_bSelected=true;
}

CShapeLine::~CShapeLine()
{

}

void CShapeLine::SetCurrentPoint(CPoint &point)
{
	if(m_points.GetSize() < 2){
		m_points.Add(point);
	}
	else{
		m_points.ElementAt(1) = point;
	}
}

// void CShapeLine::ReDrawStroke(CDC *pDC, CPoint point)
// {
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
// }

BOOL CShapeLine::IsPointIn(const CPoint &point)
{
	int x1 = point.x - m_points.GetAt(0).x;
	int x2 = point.x - m_points.GetAt(1).x;
	int y1 = point.y - m_points.GetAt(0).y;
	int y2 = point.y - m_points.GetAt(1).y;
	//y1/x1=y2/x2 => x1*y2=x2*y1
	int measure = x1*y2 - x2*y1;
	
	//tolerable distance
	int rule = abs(m_points.GetAt(1).x - m_points.GetAt(0).x)
		+abs(m_points.GetAt(0).y - m_points.GetAt(1).y);
	rule *= m_nPenWidth;
	
	if(measure < rule && measure > -rule){
		//between the two points
		if(x1 * x2 < 0)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

void CShapeLine::DrawStroke(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	
	pDC->MoveTo(m_points.GetAt(0));
	pDC->LineTo(m_points.GetAt(1));

	
	if(m_bSelected && m_points.GetSize() == 2)
	{
		m_tracker.m_nStyle = CRectTracker::resizeOutside;
		m_tracker.m_rect.SetRect(m_points.GetAt(0), m_points.GetAt(1));
		m_tracker.m_rect.NormalizeRect();
		m_tracker.Draw(pDC,1,m_color,0x04);
	}
	pDC->SelectObject(pOld);
	CShape::DrawStroke(pDC);
}
