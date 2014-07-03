// paintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "paint.h"
#include "Filter.h"
#include "paintDoc.h"
#include "paintView.h"
#include "ShapeSelect.h"
#include "TextDlg.h"

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
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_GREY, OnGrey)
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
	
	//bitmap.LoadBitmap(IDB_BG);///加载位图
//	bitmap.GetBitmap(&bmp);
}

CPaintView::~CPaintView()
{
	m_pDocument=pOldDoc;
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

//	x = pDoc->m_cavasW;
//	y = pDoc->m_cavasH;
	OnPrepareDC(pDC);

	CRect rect;
	GetClientRect(&rect);
	if (pDoc->m_bNet)
	{
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
		dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
		CPen pen(PS_DOT,1,RGB(128,128,128));
		CPen* oldPen = dc->SelectObject(&pen);	
		int i;
		for (i = 10;i<rect.Height();i+=10)
		{
			dc->MoveTo(0,i);
			dc->LineTo(rect.Width(),i);
		}
		
		for (i = 10;i<rect.Width();i+=10)
		{
			dc->MoveTo(i,0);
			dc->LineTo(i,rect.Height());
		}

		pDC->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,dc,0,0,SRCCOPY);
		dc->SelectObject(oldPen);
		pen.DeleteObject();
		delete dc;
	}
	else
	{
		pDC->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
	}


	if (pDoc->m_shape && pDoc->m_shape->m_bSelected)
	{
		pDoc->m_shape->m_color  = pDoc->clr;
		pDoc->m_shape->m_nPenStyle = pDoc->m_nLineStyle;
		pDoc->m_shape->m_nPenWidth = pDoc->m_nLineWidth;
		pDoc->m_shape->DrawStroke(pDC);
	}
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
	CPaintDoc*pDoc = GetDocument();
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
		pDoc->m_shape->ReDrawStroke(pDC, point);
		ReleaseDC(pDC);
		//	Invalidate();
	}
	
	CView::OnMouseMove(nFlags, point);
}
void CPaintView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CDC* pDC=GetDC();
	CPaintDoc* pDoc = GetDocument();
	pDoc->MyDC = new CDC();
	pDoc->MyDC->CreateCompatibleDC(pDC);

	CBitmap MemBitmap;   
	MemBitmap.CreateCompatibleBitmap(pDC,1400,800);
	//将位图选入到内存设备描述表  

	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=pDoc->MyDC->SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	pDoc->MyDC->FillSolidRect(0,0,1400,800,RGB(255,255,255));

 	pDoc->tempDC = new CDC();
 	pDoc->tempDC->CreateCompatibleDC(pDC);
	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(pDC,1400,800);
	pOldBit = pDoc->tempDC->SelectObject(&tempBitmap);
	pDoc->tempDC->FillSolidRect(0,0,1400,800,RGB(255,255,255));
// 	CDC* DC = new CDC();
// 	DC->CreateCompatibleDC(pDC);
// 	
// //	pDoc->MyDC->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));
// 	DC->SelectObject(&bitmap);
// 
// 	pDoc->MyDC->BitBlt(0,0,400,300,DC,0,0,SRCCOPY);
// 	ReleaseDC(pDC);
// 	delete DC;

}

void CPaintView::OnBackward() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Backward(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	
		Invalidate();
}
void CPaintView::OnExposure() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Exposure(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	
	Invalidate();
}
void CPaintView::OnNeonred() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Neonred(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnRelief() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Relief(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnSharpen() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Sharpen(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnSleek() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Sleek(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();

}

void CPaintView::OnInlay() 
{
	// TODO: Add your command handler code here
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->BackUp();
	fil.Inlay(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关
	pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
	
	CPaintDoc* pDoc = GetDocument();
	
	if (pDoc->m_DrawType == FILL)
	{
// 		CDC* dc = new CDC();
// 		dc->CreateCompatibleDC(pDC);
// 		CBitmap MemBitmap;  
// 		//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
// 		MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
// 		//将位图选入到内存设备描述表  
// 		//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
// 		CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
// 		//先用背景色将位图清除干净，这里我用的是白色作为背景  
// 		//你也可以用自己应该用的颜色  
// 		dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
// 		dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
// 		pDoc->m_stack.push(dc);
	
		pDoc->BackUp();
		
		FillColor(GetDocument()->MyDC,pDoc->clr,point);

		Invalidate(FALSE);
		return ;
	}

	if (pDoc->m_DrawType  == MYTEXT)
	{
		CTextDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			//dlg.ShowWindow(SW_HIDE);
			CString text = dlg.m_Text;

			CFont* m_pFont = new CFont();
			VERIFY(m_pFont->CreatePointFont(200,"Arial",pDoc->MyDC));
			LOGFONT logFont;
			
			m_pFont->GetLogFont(&logFont);
			CFontDialog dlg(&logFont);
			if (IDOK==dlg.DoModal())
			{
				dlg.GetCurrentFont(&logFont);
				delete m_pFont;
				m_pFont=new CFont();
				m_pFont->CreateFontIndirect(&logFont);
				this->SetFont(m_pFont,TRUE);
			}
			CFont*pOldFont = pDoc->MyDC->SelectObject(m_pFont);
			CRect rect = CRect(point.x,point.y,(logFont.lfWeight * text.GetLength()),logFont.lfHeight);
			pDoc->BackUp();
			pDoc->MyDC->TextOut(point.x,point.y,text);
			pDoc->MyDC->SelectObject(pOldFont);
		}
		Invalidate(FALSE);
		return;
	}

	if (pDoc->m_shape && pDoc->m_shape->m_bSelected)
	{	
		if (pDoc->m_shape->IsPointIn(point))
		{
			int hit = pDoc->m_shape->m_tracker.HitTest(point);
			if(hit >= 0 &&pDoc->m_shape->m_tracker.Track(this,point,TRUE))
			{
				pDoc->m_shape->ReSize(pDoc->m_shape->m_tracker.m_rect);
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
// 			CDC* dc = new CDC();
// 			dc->CreateCompatibleDC(pDC);
// 			CBitmap MemBitmap;  
// 			//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
// 			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
// 			//将位图选入到内存设备描述表  
// 			//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
// 			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
// 			//先用背景色将位图清除干净，这里我用的是白色作为背景  
// 			//你也可以用自己应该用的颜色  
// 			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
// 			dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
// 			pDoc->m_stack.push(dc);

			pDoc->BackUp();
			pDoc->m_shape->Draw(pDoc->MyDC);
			delete pDoc->m_shape;
			pDoc->m_shape = NULL;
		}
	}
	else if (pDoc->m_shape == NULL)
	{
		SetCapture();	
		pDoc->m_shape = pDoc->NewShape();
		pDoc->m_shape->SetCurrentPoint(point);
		pDoc->SetModifiedFlag();	
		ReleaseDC(pDC);	
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

void CPaintView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() == this)
	{
		CPaintDoc *pDoc = GetDocument();		
		CDC *pDC = GetDC();
		OnPrepareDC(pDC);
		pDC->DPtoLP(&point);
		//Step0.1 点下就松开，不绘制
		if(pDoc->m_shape->m_points.GetSize() == 1)
		{
			delete pDoc->m_shape;
			pDoc->m_shape = NULL;
		}
		//Step0.2 选择框
		else 
		{
			if(SELECT == pDoc->m_shape->m_nDrawType)
			{
				pDoc->m_shape->SetCurrentPoint(point);
// 				if (pDoc->m_shape->m_bSelected == false) 
// 				{
					 pDoc->m_shape->m_bSelected = true;
					 ((CShapeSelect*)pDoc->m_shape)->SetRect();
					 ((CShapeSelect*)pDoc->m_shape)->SetDC(pDoc->MyDC,pDoc->m_cavasW,pDoc->m_cavasH);
			//	 }
			}
			else//Step0.3 绘制
			{
				pDoc->m_shape->SetCurrentPoint(point);
				pDoc->m_shape->m_bSelected = true;
			}
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
	CPaintDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//设置DC的滚动属性，，与scrollview有关
	pDC->DPtoLP(&point);//转换当前点为逻辑位置坐标
	if (pDoc->m_shape && pDoc->m_shape->m_bSelected)
	{
		if (pDoc->m_shape->IsPointIn(point))
		{
			//////////////////////////////////////////////////////////////////////////
			//此处添加弹出式菜单
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{	
// 			CPaintDoc* pDoc = GetDocument();
// 			CDC* dc = new CDC();
// 			dc->CreateCompatibleDC(pDC);
// 			CBitmap MemBitmap;  
// 			//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
// 			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
// 			//将位图选入到内存设备描述表  
// 			//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
// 			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
// 			//先用背景色将位图清除干净，这里我用的是白色作为背景  
// 			//你也可以用自己应该用的颜色  
// 			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
// 			dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
// 			pDoc->m_stack.push(dc);

			CPaintDoc* pDoc = GetDocument();
			pDoc->BackUp();
			pDoc->m_shape->Draw(pDoc->MyDC);
			delete pDoc->m_shape;
			pDoc->m_shape = NULL;
		}
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

void CPaintView::OnDiffuse() 
{
	// TODO: Add your command handler code here
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->BackUp();
	fil.Diffuse(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

BOOL CPaintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CPaintDoc* pDoc = GetDocument();
	if(pWnd == this && pDoc->m_shape){
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
		if(pDoc->m_shape->m_tracker.HitTest(point) >= 0){
			//Step3. set cursor, **notice, use nHitTest instead of return of tracker
			pDoc->m_shape->m_tracker.SetCursor(pWnd, nHitTest);			
			return true;
		}
		
		ReleaseDC(pDC);
	}


	return CView::OnSetCursor(pWnd, nHitTest, message);
}

//DEL void CPaintView::OnEditUndo() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	CPaintDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL 	if (pDoc->m_shape && pDoc->m_shape->m_bSelected)
//DEL 	{
//DEL 		delete pDoc->m_shape;
//DEL 		pDoc->m_shape = NULL;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		if (!pDoc->m_stack.empty())
//DEL 		{
//DEL 			CDC* dc = pDoc->m_stack.top();
//DEL 			pDoc->MyDC->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,dc,0,0,SRCCOPY);
//DEL 			pDoc->m_stack.pop();
//DEL 			
//DEL 			delete dc;
//DEL 		}
//DEL 	}
//DEL 	Invalidate();
//DEL }

//DEL void CPaintView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
//DEL {
//DEL 	// TODO: Add your command update UI handler code here
//DEL 	pCmdUI->Enable(!m_stack.empty());
//DEL }
/////////////////////////////////////////
///////STL////////////////////////////#include "stack"
void CPaintView::FillColor(CDC* m_DC/*!!!!!!类对象 view类变量 */,COLORREF v_color/*被填充色*/,CPoint v_point/*鼠标此时的点*/ ) 
{
	//if(没填充)
	//{return}
	CPaintDoc* pDoc = GetDocument();
	stack<CPoint> coloStack;  //stl 保存要填充的点
	CDC dc;
	dc.CreateCompatibleDC(m_DC);
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
	MemBitmap.CreateCompatibleBitmap(m_DC,pDoc->m_cavasW,pDoc->m_cavasH);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=dc.SelectObject(&MemBitmap);  
	dc.FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));
	CRect rect;
	rect = CRect(0,0,GetDocument()->m_cavasW,GetDocument()->m_cavasH);
	//GetClientRect(&rect);
	CPoint currentpoint = v_point; // 鼠标的点设为种子点
	coloStack.push(currentpoint);  //种子压入栈中

	//m_DC
// 	if(!m_DC->m_hDC)  
// 	{
// 		dc.CreateCompatibleDC(m_DC);
// 		CBitmap bitmap;
// 		bitmap.CreateCompatibleBitmap(m_DC,rect.Width(),rect.Height());
// 		dc.SelectObject(&bitmap);
// 		//dc.BitBlt(0,0,rect.Width(),rect.Height(),m,0,0,SRCCOPY);
// 	}
	
	COLORREF seedColor = m_DC->GetPixel(currentpoint);  //获取种子点颜色

	while ( ! coloStack.empty() ) //栈不空？？？
	{
		currentpoint = coloStack.top();
		coloStack.pop();    //出栈
		CPoint ptArr[ 4 ];
		//上下左右
		ptArr[ 0 ] = CPoint( currentpoint.x - 1, currentpoint.y );
		ptArr[ 1 ] = CPoint( currentpoint.x + 1, currentpoint.y );
		ptArr[ 2 ] = CPoint( currentpoint.x, currentpoint.y - 1 );
		ptArr[ 3 ] = CPoint( currentpoint.x, currentpoint.y + 1 );
		//如果种子点周围四个点在客户区域内并且其颜色和种子点的颜色是相同的，那么将其放入堆栈中
		for ( int i = 0; i < 4; i ++ )
		{
			if( ptArr[ i ].x >= rect.left && ptArr[ i ].x <= rect.right && ptArr[ i ].y >= rect.top && ptArr[ i ].y <= rect.bottom )
				if( m_DC->GetPixel( ptArr[ i ] ) == seedColor )
					coloStack.push( ptArr[ i ] );
		}
		///m_DC->SetPixel( currentpoint, v_color ); //将当前需要填充的点的颜色设置为填充色
		dc.SetPixel( currentpoint, v_color ); 

	}
	m_DC->BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
	Invalidate(FALSE);
}


void CPaintView::OnGrey() 
{
	// TODO: Add your command handler code here
	CPaintDoc* pDoc = GetDocument();
	
	pDoc->BackUp();
	fil.Grey(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate(FALSE);
}
