// MyPaintView.cpp : implementation file
//

#include "stdafx.h"
#include "paint.h"
#include "MyPaintView.h"
#include "paintDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CScrollView)

CMyPaintView::CMyPaintView()
{
	EnableAutomation();
}

CMyPaintView::~CMyPaintView()
{
}

// void CMyPaintView::OnFinalRelease()
// {
// 	// When the last reference for an automation object is released
// 	// OnFinalRelease is called.  The base class will automatically
// 	// deletes the object.  Add additional cleanup required for your
// 	// object before calling the base class.
// 
// 	CScrollView::OnFinalRelease();
// }


BEGIN_MESSAGE_MAP(CMyPaintView, CScrollView)
	//{{AFX_MSG_MAP(CMyPaintView)
	ON_WM_CREATE()
	ON_WM_CANCELMODE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMyPaintView, CScrollView)
	//{{AFX_DISPATCH_MAP(CMyPaintView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMyPaintView to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {50224767-87DB-4E0E-A4B5-5AF0E20D00AF}
static const IID IID_IMyPaintView =
{ 0x50224767, 0x87db, 0x4e0e, { 0xa4, 0xb5, 0x5a, 0xf0, 0xe2, 0xd, 0x0, 0xaf } };

BEGIN_INTERFACE_MAP(CMyPaintView, CScrollView)
	INTERFACE_PART(CMyPaintView, IID_IMyPaintView, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView drawing

void CMyPaintView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_rectTracker.m_rect.SetRect(0,0,GetDocument()->m_cavasW, GetDocument()->m_cavasH);
	m_rectTracker.m_nHandleSize = 8;
	m_paintView->MoveWindow(m_rectTracker.m_rect);
}

void CMyPaintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	m_rectTracker.Draw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView diagnostics

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView message handlers

int CMyPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_rectTracker.m_rect.SetRect(0,0,GetDocument()->m_cavasW, GetDocument()->m_cavasH); 
	m_rectTracker.m_nStyle=CRectTracker::resizeOutside; 

	//*here must be pointer, if variable, crashed

	m_paintView = new CPaintView();
	// TODO: Add your specialized creation code here
	if (!m_paintView->CreateEx(WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,LoadCursor(NULL,IDC_CROSS),
			(HBRUSH)GetStockObject(WHITE_BRUSH),NULL),
		"",WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		m_rectTracker.m_rect.left,m_rectTracker.m_rect.top,
		m_rectTracker.m_rect.right-1,m_rectTracker.m_rect.bottom-1,
		this->m_hWnd,NULL))
	{
		TRACE0("创建画布失败!\n");
		return -1;      // fail to create
	}
	m_paintView->SetDocument((CPaintDoc*)m_pDocument);
	m_paintView->ShowWindow(SW_NORMAL);
	m_paintView->UpdateWindow();
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,(long)GetStockObject(LTGRAY_BRUSH));

//	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,(long)GetStockObject(GREEN_BRUSH));
	return 0;
}

void CMyPaintView::OnCancelMode() 
{
	CScrollView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
CPaintDoc* CMyPaintView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}

BOOL CMyPaintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(pWnd == this){
		CPoint point;
		//Step1. get cursor position
		GetCursorPos(&point);
		//Step2. convert point from screen to client
		ScreenToClient(&point);
		
		CDC* pDC = GetDC();//获得DC
		OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关
		pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
			
		//////////////////////////////////////////////////////////////////////////
		// 		CRectTracker::hitNothing    –1
		// 		CRectTracker::hitTopLeft   0
		// 		CRectTracker::hitTopRight   1
		// 		CRectTracker::hitBottomRight   2
		// 		CRectTracker::hitBottomLeft   3
		// 		CRectTracker::hitTop   4
		//		CRectTracker::hitRight   5
		//		CRectTracker::hitBottom   6
		//		CRectTracker::hitLeft   7
		// 		CRectTracker::hitMiddle   8
		//////////////////////////////////////////////////////////////////////////
		if(m_rectTracker.HitTest(point) >= 0){
			//Step3. set cursor, **notice, use nHitTest instead of return of tracker
			m_rectTracker.SetCursor(pWnd, nHitTest);			
			return true;
		}
		
		ReleaseDC(pDC);
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CMyPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
//	ScreenToClient(&point);
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetDC();//获得DC
	OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关

	
	pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
	
	int hit = m_rectTracker.HitTest(point);

	//////////////////////////////////////////////////////////////////////////
	// 		CRectTracker::hitNothing    –1
	// 		CRectTracker::hitTopLeft   0
	// 		CRectTracker::hitTopRight   1
	// 		CRectTracker::hitBottomRight   2
	// 		CRectTracker::hitBottomLeft   3
	// 		CRectTracker::hitTop   4
	//		CRectTracker::hitRight   5
	//		CRectTracker::hitBottom   6
	//		CRectTracker::hitLeft   7
	// 		CRectTracker::hitMiddle   8
	//////////////////////////////////////////////////////////////////////////

	switch(hit){
	case 2://右下
	case 5://右
	case 6://下
		if(m_rectTracker.Track(this,point)){
			//step1. cavas reset
			GetDocument()->m_cavasH = m_rectTracker.m_rect.bottom;
			GetDocument()->m_cavasW = m_rectTracker.m_rect.right;
			//step2. scroll or not
			CRect clientRect;
			GetClientRect(&clientRect);
			SetScrollSizes(MM_TEXT, CSize(m_rectTracker.m_rect.Width()+10, m_rectTracker.m_rect.Height()+10));
			
			m_paintView->MoveWindow(m_rectTracker.m_rect.left, m_rectTracker.m_rect.top,
				m_rectTracker.m_rect.right,m_rectTracker.m_rect.bottom);
		//	GetDocument()->BackUp();//??
			Invalidate();
		}
	}
	ReleaseDC(pDC);

	Invalidate();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CMyPaintView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	Invalidate();
	CString strPosition;
	CStatusBar* pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if (pStatus)
	{
		CPoint point;
		GetCursorPos(&point);
		strPosition.Format("X:%d",point.x);
		pStatus->SetPaneText(1,strPosition);
		strPosition.Format("Y:%d",point.y);
		pStatus->SetPaneText(2,strPosition);
	}
	CScrollView::OnMouseMove(nFlags, point);
}