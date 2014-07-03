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
	m_bSelected = false;
	m_tracker.m_nHandleSize = 8;
}

CShapeLine::~CShapeLine()
{

}

// void CShapeLine::SetCurrentPoint(CPoint &point)
// {
// 	if(m_points.GetSize() < 2){
// 		m_points.Add(point);
// 	}
// 	else{
// 		m_points.ElementAt(1) = point;
// 	}
// }

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

// BOOL CShapeLine::IsPointIn(const CPoint &point)
// {
// // 	int x1 = point.x - m_points.GetAt(0).x;
// // 	int x2 = point.x - m_points.GetAt(1).x;
// // 	int y1 = point.y - m_points.GetAt(0).y;
// // 	int y2 = point.y - m_points.GetAt(1).y;
// // 	//y1/x1=y2/x2 => x1*y2=x2*y1
// // 	int measure = x1*y2 - x2*y1;
// // 	
// // 	//tolerable distance
// // 	int rule = abs(m_points.GetAt(1).x - m_points.GetAt(0).x)
// // 		+abs(m_points.GetAt(0).y - m_points.GetAt(1).y);
// // 	rule *= m_nPenWidth;
// // 	
// // 	if(measure < rule && measure > -rule){
// // 		//between the two points
// // 		if(x1 * x2 < 0)
// // 			return TRUE;
// // 		else
// // 			return FALSE;
// // 	}
// // 	else
// // 		return FALSE;
// 	
// 	//////////////////////////////////////////////////////////////////////////
// 	//以上这一段代码用来确定点是否在直线上，由于时间原因，我们将直线当做矩形来
// 	//即，点只要在以此直线为对角线即可
// 	//////////////////////////////////////////////////////////////////////////
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

// void CShapeLine::DrawStroke(CDC *pDC)
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

void CShapeLine::Draw(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	
	if (m_nRorate % 2 )
	{
		pDC->MoveTo(m_points[0].x,m_points[1].y);
		pDC->LineTo(m_points[1].x,m_points[0].y);
	}
	else
	{
		pDC->MoveTo(m_points.GetAt(0));
		pDC->LineTo(m_points.GetAt(1));
	}
	pDC->SelectObject(pOld);
}
