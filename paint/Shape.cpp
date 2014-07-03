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
: m_bSelected(false)
, m_nRorate(0)
, mirror(0)
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
	Draw(pDC);
	if(m_bSelected && m_points.GetSize() == 2)
	{
		m_tracker.m_nStyle = CRectTracker::resizeOutside;
		m_tracker.m_rect.SetRect(m_points.GetAt(0), m_points.GetAt(1));
		m_tracker.m_rect.NormalizeRect();
		m_tracker.Draw(pDC,1,m_color,0xff);
		
		//////////////////////////////////////////////////////////////////////////
		//m_tracker.Draw(pDC,1,m_color,0x05);//时间比较紧，直线也以矩形方式进行移动变换
		//绘制直线的类中加以重载即可
		//////////////////////////////////////////////////////////////////////////
	}
}
BOOL CShape::IsPointIn(const CPoint &point)
{
	int minx,maxx,miny,maxy;
	
	CRect rect;
	m_tracker.GetHandleRect(0,&rect);
	if (m_points[0].x<m_points[1].x)
	{
		minx = m_points[0].x - m_tracker.m_nHandleSize;
		maxx = m_points[1].x + m_tracker.m_nHandleSize;
	}
	else
	{
		minx = m_points[1].x - m_tracker.m_nHandleSize;
		maxx = m_points[0].x + m_tracker.m_nHandleSize;
	}
	if (m_points[0].y<m_points[1].y)
	{
		miny = m_points[0].y - m_tracker.m_nHandleSize;
		maxy = m_points[1].y + m_tracker.m_nHandleSize;
	}
	else
	{
		miny = m_points[1].y - m_tracker.m_nHandleSize;
		maxy = m_points[0].y + m_tracker.m_nHandleSize;
	}

	if (point.x >= minx && point.x <= maxx && point.y >= miny && point.y <= maxy)
	{
		return TRUE;
	}
	return FALSE;
}


void CShape::ReDrawStroke(CDC *pDC, CPoint point)
{
	if(m_points.GetSize() < 2)
	{
		if(m_points.GetSize() == 1)
		{
			m_points.Add(point);
			DrawStroke(pDC);
		}
		return ;
	}
	pDC->SetROP2(R2_NOTXORPEN);
	
	DrawStroke(pDC);
	SetCurrentPoint(point);
	DrawStroke(pDC);
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

void CShape::Rotate()
{
	m_nRorate = (m_nRorate+1)%4;
}

