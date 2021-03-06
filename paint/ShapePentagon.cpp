// ShapePentagon.cpp: implementation of the CShapePentagon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapePentagon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapePentagon::CShapePentagon()
{

}

CShapePentagon::~CShapePentagon()
{

}
void CShapePentagon::Draw(CDC *pDC)
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
	CPoint point[5];
	CBrush brush;
	brush.CreateStockObject(NULL_BRUSH);
	if (m_nRorate  == 0)
	{
		point[0].x =(minx+maxx)>>1;
		point[0].y = miny;
		point[1].x = minx;
		point[1].y = long(0.4*maxy+0.6*miny);
		point[2].x = long(0.8*minx+0.2*maxx);
		point[2].y = maxy;
		point[3].x = long(0.8*maxx+0.2*minx);
		point[3].y = maxy;
		point[4].x = maxx;
		point[4].y = long(0.4*maxy+0.6*miny);
	}
	else if (m_nRorate  == 1)
	{
		point[0].x =0.4*minx+0.6*maxx;
		point[0].y = miny;

		point[1].x = maxx;
		point[1].y = (maxy+miny)>>1;
		point[2].x = 0.4*minx+0.6*maxx;
		point[2].y = maxy;
		point[3].x = minx;
		point[3].y = (0.8*maxy+0.2*miny);
		point[4].x = minx;
		point[4].y = long(0.8*miny+0.2*maxy);
	}

	else if (m_nRorate  == 2)
	{
		point[0].x =(minx+maxx)>>1;
		point[0].y = maxy;

		point[1].x = minx;
		point[1].y = long(0.6*maxy+0.4*miny);

		point[3].x = long(0.8*maxx+0.2*minx);
		point[2].y = miny;

		point[2].x = long(0.8*minx+0.2*maxx);
		point[3].y = miny;

		point[4].x = maxx;
		point[4].y = long(0.6*maxy+0.4*miny);
	}

	else if (m_nRorate  == 3)
	{
		point[0].x =minx;
		point[0].y = (maxy+miny)>>1;

		point[1].x = long(0.6*minx+0.4*maxx);
		point[1].y = miny;
		//	;

		point[2].x = maxx;
		point[2].y = long(0.2*maxy+0.8*miny);

		point[3].x = maxx;
		point[3].y = long(0.8*maxy+0.2*miny);

		point[4].x = long(0.6*minx+0.4*maxx);
		point[4].y = maxy;
	}
	if (rgn.CreatePolygonRgn(point,5,ALTERNATE))
	{
		pDC->FillRgn(&rgn,&brush);
		pDC->MoveTo(point[0]);
		pDC->LineTo(point[1]);
		pDC->MoveTo(point[1]);
		pDC->LineTo(point[2]);
		pDC->MoveTo(point[2]);
		pDC->LineTo(point[3]);
		pDC->MoveTo(point[3]);
		pDC->LineTo(point[4]);
		pDC->MoveTo(point[4]);
		pDC->LineTo(point[0]);
	}
	rgn.DeleteObject();
	pDC->SelectObject(pOld);
	pNew.DeleteObject();
}
