// ShapeFont.cpp: implementation of the CShapeFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "ShapeFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeFont::CShapeFont()
{
	
	text = "";
}

CShapeFont::~CShapeFont()
{

}
// void CShapeFont::Draw(CDC *pDC)
// {
// 	CPen *pOld, pNew; 
// 
// 	LOGFONT logFont;
// 	m_pFont->GetLogFont(&logFont);
// 	CFontDialog dlg(&logFont);
// 	if (IDOK==dlg.DoModal())
// 	{
// 		dlg.GetCurrentFont(&logFont);
// 		delete m_pFont;
// 		m_pFont=new CFont;
// 		m_pFont->CreateFontIndirect(&logFont);
// 		this->SetFont(m_pFont,TRUE);
//  }
// 	pNew.CreatePen(m_nPenStyle, m_nPenWidth, m_color);
// 	pOld = pDC->SelectObject(&pNew);
// 	
// 	if (m_nRorate % 2 )
// 	{
// 		pDC->MoveTo(m_points[0].x,m_points[1].y);
// 		pDC->LineTo(m_points[1].x,m_points[0].y);
// 	}
// 	else
// 	{
// 		pDC->MoveTo(m_points.GetAt(0));
// 		pDC->LineTo(m_points.GetAt(1));
// 	}
// 	pDC->SelectObject(pOld);
// }
