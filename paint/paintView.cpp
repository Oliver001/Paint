// paintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "paint.h"
#include "Filter.h"
#include "paintDoc.h"
#include "paintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CView)

BEGIN_MESSAGE_MAP(CPaintView, CView)
	//{{AFX_MSG_MAP(CPaintView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_BACKWARD, OnBackward)
	ON_COMMAND(IDM_EXPOSURE, OnExposure)
	ON_COMMAND(IDM_NEONRED, OnNeonred)
	ON_COMMAND(IDM_RELIEF, OnRelief)
	ON_COMMAND(IDM_SHARPEN, OnSharpen)
	ON_COMMAND(IDM_SLEEK, OnSleek)
	ON_COMMAND(IDM_INLAY, OnInlay)
	ON_COMMAND(IDM_DIFFUSE, OnDiffuse)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaintView construction/destruction

CPaintView::CPaintView()
{
	// TODO: add construction code here
	m_shape = NULL;
	bitmap.LoadBitmap(IDB_BG);///加载位图
	bitmap.GetBitmap(&bmp);
    x = bmp.bmWidth;
    y = bmp.bmHeight;

}

CPaintView::~CPaintView()
{
	m_pDocument=pOldDoc;

	if (m_shape)
	{
		delete m_shape;
	}
	while(!m_stack.empty())
	{
		CDC* dc = (CDC*)m_stack.top();
		m_stack.pop();
	
		delete dc;
	}
}

BOOL CPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPaintView drawing

void CPaintView::OnDraw(CDC* pDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	OnPrepareDC(pDC);

	CRect rect;
	GetClientRect(&rect);
	int i;

	CPen pen(PS_DOT,1,RGB(128,128,128));
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->BitBlt(0,0,x,y,MyDC,0,0,SRCCOPY);
	
	for (i = 10;i<rect.Height();i+=10)
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(rect.Width(),i);
	}
	
	for (i = 10;i<rect.Width();i+=10)
	{
		pDC->MoveTo(i,0);
		pDC->LineTo(i,rect.Height());
	}


	if (m_shape && m_shape->m_bSelected)
	{
		m_shape->DrawStroke(pDC);
	}

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPaintView printing

BOOL CPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPaintView diagnostics

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaintView message handlers

void CPaintView::SetDocument(CPaintDoc *pDoc)
{
	pOldDoc = m_pDocument;
	m_pDocument = pDoc;
}

void CPaintView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
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
	if(GetCapture() == this)
	{
		CDC *pDC = GetDC();
		OnPrepareDC(pDC);
		pDC->DPtoLP(&point);
		m_shape->ReDrawStroke(pDC, point);
		ReleaseDC(pDC);
		//	Invalidate();
	}
	
	CView::OnMouseMove(nFlags, point);
}
void CPaintView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CDC* pDC=GetDC();
	MyDC = new CDC();
 	MyDC->CreateCompatibleDC(pDC);
// 	BITMAP  bmp;
// 	bitmap.GetBitmap(&bmp);
// 	int x = bmp.bmWidth;
// 	int y = bmp.bmHeight;

// 	MyDC->SelectObject(&bitmap);

	CPaintDoc* pDoc = GetDocument();
	CBitmap MemBitmap;   
	MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MyDC->SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MyDC->FillSolidRect(0,0,800,600,RGB(255,255,255));

	ReleaseDC(pDC);
}

void CPaintView::OnBackward() 
{
	// TODO: Add your command handler code here

	fil.Backward(MyDC,0,0,x,y);
	
		Invalidate();
}
void CPaintView::OnExposure() 
{
	// TODO: Add your command handler code here

	fil.Exposure(MyDC,0,0,x,y);
	
	Invalidate();
}
void CPaintView::OnNeonred() 
{
	// TODO: Add your command handler code here

	fil.Neonred(MyDC,0,0,x,y);
	Invalidate();
}

void CPaintView::OnRelief() 
{
	// TODO: Add your command handler code here

	fil.Relief(MyDC,0,1,x,y);
	Invalidate();
}

void CPaintView::OnSharpen() 
{
	// TODO: Add your command handler code here

	fil.Sharpen(MyDC,0,0,x,y);
	Invalidate();
}

void CPaintView::OnSleek() 
{
	// TODO: Add your command handler code here

	fil.Sleek(MyDC,0,0,x,y);
	Invalidate();

}

void CPaintView::OnInlay() 
{
	// TODO: Add your command handler code here
	
	fil.Inlay(MyDC,0,0,x,y);
	Invalidate();
}

void CPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//

	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关
	pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
	
	CPaintDoc* pDoc = GetDocument();
	
	if (m_shape && m_shape->m_bSelected)
	{	
		if (m_shape->IsPointIn(point))
		{
			int hit = m_shape->m_tracker.HitTest(point);
			if(hit >= 0 &&m_shape->m_tracker.Track(this,point,TRUE))
			{
				m_shape->ReSize(m_shape->m_tracker.m_rect);
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
			}
		}
		else
		{
			
			CPaintDoc* pDoc = GetDocument();
			CDC* dc = new CDC();
			dc->CreateCompatibleDC(pDC);
			CBitmap MemBitmap;  
			//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
			//将位图选入到内存设备描述表  
			//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
			//先用背景色将位图清除干净，这里我用的是白色作为背景  
			//你也可以用自己应该用的颜色  
			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
			dc->BitBlt(0,0,x,y,MyDC,0,0,SRCCOPY);
			m_stack.push(dc);

			m_shape->Draw(MyDC);
			delete m_shape;
			m_shape = NULL;
		}
	}
	else if (m_shape == NULL)
	{
		SetCapture();	
		m_shape = pDoc->NewShape();
		m_shape->SetCurrentPoint(point);
		pDoc->SetModifiedFlag();	
		ReleaseDC(pDC);	
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

void CPaintView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() == this){
		CPaintDoc *pDoc = GetDocument();		
		CDC *pDC = GetDC();
		OnPrepareDC(pDC);
		pDC->DPtoLP(&point);
		//Step0.1 点下就松开，不绘制
		if(m_shape->m_points.GetSize() == 1){
			delete m_shape;
			m_shape = NULL;
		}
		//Step0.2 选择框
		else if(SELECT == m_shape->m_nDrawType){
// 			bool refresh = false;
// 			CRect rect(m_stroke->m_points[0], m_stroke->m_points[1]);
// 			rect.NormalizeRect();//?????????
// 			for(int i = 0; i < pDoc->m_strokeList.GetSize(); i ++){
// 				if(rect.PtInRect(pDoc->m_strokeList.GetAt(i)->m_points.GetAt(0)) &&
// 					rect.PtInRect(pDoc->m_strokeList.GetAt(i)->m_points.GetAt(1))){
// 					pDoc->m_strokeList.GetAt(i)->m_bSelected = true;
// 					refresh = true;
// 				}
// 			}
// 			if(refresh)
// 				Invalidate();
// 			delete m_stroke;
		}
		//Step0.3 绘制
		else{
			
			m_shape->SetCurrentPoint(point);
			m_shape->m_bSelected = true;
		}
		
		ReleaseCapture();
		ReleaseDC(pDC);
		Invalidate();
	}	
	CView::OnLButtonUp(nFlags, point);
}

void CPaintView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关
	pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
	if (m_shape && m_shape->m_bSelected)
	{
		if (m_shape->IsPointIn(point))
		{
			//////////////////////////////////////////////////////////////////////////
			//此处添加弹出式菜单
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{	
			CPaintDoc* pDoc = GetDocument();
			CDC* dc = new CDC();
			dc->CreateCompatibleDC(pDC);
			CBitmap MemBitmap;  
			//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
			//将位图选入到内存设备描述表  
			//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
			//先用背景色将位图清除干净，这里我用的是白色作为背景  
			//你也可以用自己应该用的颜色  
			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
			dc->BitBlt(0,0,x,y,MyDC,0,0,SRCCOPY);
			m_stack.push(dc);

			m_shape->Draw(MyDC);
			delete m_shape;
			m_shape = NULL;
		}
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

void CPaintView::OnDiffuse() 
{
	// TODO: Add your command handler code here
	fil.Diffuse(MyDC,0,0,x,y);
	Invalidate();
}

BOOL CPaintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

	
	if(pWnd == this && m_shape){
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
		if(m_shape->m_tracker.HitTest(point) >= 0){
			//Step3. set cursor, **notice, use nHitTest instead of return of tracker
			m_shape->m_tracker.SetCursor(pWnd, nHitTest);			
			return true;
		}
		
		ReleaseDC(pDC);
	}


	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CPaintView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	if (m_shape && m_shape->m_bSelected)
	{
		delete m_shape;
		m_shape = NULL;
	}
	else
	{
		if (!m_stack.empty())
		{
			CDC* dc = m_stack.top();
			MyDC->BitBlt(0,0,x,y,dc,0,0,SRCCOPY);
			m_stack.pop();
			
			delete dc;
		}
	}
	Invalidate();
}

void CPaintView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_stack.empty());
}
