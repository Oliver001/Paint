// ShapeTriangle.cpp: implementation of the CShapeTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapeTriangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeTriangle::CShapeTriangle()
{

}

CShapeTriangle::~CShapeTriangle()
{

}

void CShapeTriangle::Draw(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	pDC->SelectStockObject(NULL_BRUSH);
	int minx,maxx,miny,maxy;
	
	if (m_points[0].x<m_points[1].x)
	{
		minx = m_points[0].x;
		maxx = m_points[1].x;
	}
	else
	{
		minx = m_points[1].x;
		maxx = m_points[0].x;
	}
	if (m_points[0].y<m_points[1].y)
	{
		miny = m_points[0].y;
		maxy = m_points[1].y;
	}
	else
	{
		miny = m_points[1].y;
		maxy = m_points[0].y;
	}

	
	CRgn rgn;
	CPoint point[3];
	CBrush brush;
	brush.CreateStockObject(NULL_BRUSH);
	
	if (m_nRorate == 0)
	{
		point[0].x =(minx+maxx)>>1;point[0].y = miny;
		point[1].x = minx;point[1].y = maxy;
		point[2].x = maxx;point[2].y = maxy;
	}
	else if (m_nRorate  == 1)
	{
		point[0].x = minx;point[0].y = miny;
		point[1].x = minx;point[1].y = maxy;
		point[2].x = maxx;point[2].y = (miny+maxy)>>1;
	}
	else if (m_nRorate  == 2)
	{
		point[0].x = minx;point[0].y = miny;
		point[1].x = (minx+maxx)>>1;point[1].y = maxy;
		point[2].x = maxx;point[2].y = miny;
	}
	else if (m_nRorate  == 3)
	{
		point[0].x = minx;point[0].y = (miny+maxy)>>1;
		point[1].x = maxx;point[1].y = maxy;
		point[2].x = maxx;point[2].y = miny;
	}
// 	point[0].x =(minx+maxx)>>1;point[0].y = miny;
// 	point[1].x = minx;point[1].y = maxy;
// 	point[2].x = maxx;point[2].y = maxy;
	if (rgn.CreatePolygonRgn(point,3,ALTERNATE))
	{
		pDC->FillRgn(&rgn,&brush);
		pDC->MoveTo(point[0]);
		pDC->LineTo(point[1]);
		pDC->MoveTo(point[1]);
		pDC->LineTo(point[2]);
		pDC->MoveTo(point[2]);
		pDC->LineTo(point[0]);
	}
	rgn.DeleteObject();
	pDC->SelectObject(pOld);
	pNew.DeleteObject();
}