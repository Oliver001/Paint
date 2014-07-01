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
	m_nDrawType = SELECT;
	selectDC = NULL;
	selectRect = CRect(0,0,0,0);
}

CShapeSelect::~CShapeSelect()
{
	if(selectDC)
	{
		delete selectDC;
	}
}

void CShapeSelect::Draw(CDC *pDC)
{
	CPen *pOld, pNew; 
	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
	pOld = pDC->SelectObject(&pNew);
	pDC->SelectStockObject(NULL_BRUSH);
	
///////////////
	////
	/////
	/////
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	pDC->FillRect(&selectRect,&brush);
	int x1 = m_points[0].x < m_points[1].x?m_points[0].x : m_points[1].x;
	int x2 =  m_points[0].x > m_points[1].x?m_points[0].x : m_points[1].x;
	int y1 = m_points[0].y < m_points[1].y?m_points[0].y : m_points[1].y;
	int y2 =  m_points[0].y > m_points[1].y?m_points[0].y : m_points[1].y;


	pDC->StretchBlt(x1,y1,x2-x1,y2-y1,selectDC,selectRect.left,selectRect.top,selectRect.Width(),selectRect.Height(),SRCCOPY);
//	pDC->BitBlt(x1,y1,x2,y2,selectDC,0,0,SRCCOPY);
//	pDC->Rectangle(m_points[0].x,m_points[0].y,m_points[1].x,m_points[1].y);
	
	pDC->SelectObject(pOld);
	pNew.DeleteObject();
}

void CShapeSelect::SetRect()
{
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
	selectRect.left = minx;
	selectRect.top = miny;
	selectRect.right = maxx;
	selectRect.bottom = maxy;
}

void CShapeSelect::SetDC(CDC *pDC,int w,int h)
{
	if (selectDC != NULL)
	{
		delete selectDC;
		selectDC = NULL;
	}

	selectDC = new CDC();

	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	selectDC->CreateCompatibleDC(pDC);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,w,h);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=selectDC->SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	selectDC->FillSolidRect(0,0,w,h,RGB(255,255,255));  
	selectDC->StretchBlt(selectRect.left,selectRect.top,selectRect.Width(),selectRect.Height(),
		pDC,selectRect.left,selectRect.top,selectRect.Width(),selectRect.Height(),SRCCOPY);
	pOldBit->DeleteObject();
}
