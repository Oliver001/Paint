// ShapeEllipse.cpp: implementation of the CShapeEllipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapeEllipse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeEllipse::CShapeEllipse()
{
	m_nDrawType = CIRCLE;
	m_bSelected = false;
	m_tracker.m_nHandleSize = 8;
}

CShapeEllipse::~CShapeEllipse()
{

}

// void CShapeEllipse::SetCurrentPoint(CPoint &point)
// {
// 	if(m_points.GetSize() < 2){
// 		m_points.Add(point);
// 	}
// 	else{
// 		m_points.ElementAt(1) = point;
// 	}
// }

// BOOL CShapeEllipse::IsPointIn(const CPoint &point)
// {
// 	int minx,maxx,miny,maxy;
// 	
// 	CRect rect;
// 	m_tracker.GetHandleRect(0,&rect);
// 	if (m_points[0].x<m_points[1].x)
// 	{
// 		minx = m_points[0].x - m_tracker.m_nHandleSize;
// 		maxx = m_points[1].x + m_tracker.m_nHandleSize;
// 	}
// 	else
// 	{
// 		minx = m_points[1].x - m_tracker.m_nHandleSize;
// 		maxx = m_points[0].x + m_tracker.m_nHandleSize;
// 	}
// 	if (m_points[0].y<m_points[1].y)
// 	{
// 		miny = m_points[0].y - m_tracker.m_nHandleSize;
// 		maxy = m_points[1].y + m_tracker.m_nHandleSize;
// 	}
// 	else
// 	{
// 		miny = m_points[1].y - m_tracker.m_nHandleSize;
// 		maxy = m_points[0].y + m_tracker.m_nHandleSize;
// 	}
// 	
// 	if (point.x >= minx && point.x <= maxx && point.y >= miny && point.y <= maxy)
// 	{
// 		return TRUE;
// 	}
// 	return FALSE;
// }

// void CShapeEllipse::DrawStroke(CDC *pDC)
// {
// 	Draw(pDC);
// 	if(m_bSelected && m_points.GetSize() == 2)
// 	{
// 		m_tracker.m_nStyle = CRectTracker::resizeOutside;
// 		m_tracker.m_rect.SetRect(m_points.GetAt(0), m_points.GetAt(1));
// 		m_tracker.m_rect.NormalizeRect();
// 		m_tracker.Draw(pDC,1,m_color,0xff);
// 		//m_tracker.Draw(pDC,1,m_color,0x05);//时间比较紧，直线也以矩形方式进行移动变换
// 	}
// }

void CShapeEllipse::Draw(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
//	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(m_points[0].x,m_points[0].y,m_points[1].x,m_points[1].y);
	
	pDC->SelectObject(pOld);
}
