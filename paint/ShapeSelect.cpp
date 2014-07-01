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

	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	selectDC->CreateCompatibleDC(pDC);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,w,h);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=selectDC->SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	selectDC->FillSolidRect(0,0,w,h,RGB(255,255,255));  
	selectDC->StretchBlt(selectRect.left,selectRect.top,selectRect.Width(),selectRect.Height(),
		pDC,selectRect.left,selectRect.top,selectRect.Width(),selectRect.Height(),SRCCOPY);
	pOldBit->DeleteObject();
}
