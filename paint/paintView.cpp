// paintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "paint.h"

#include "paintDoc.h"
#include "paintView.h"
#include "Shape.h"


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
}

CPaintView::~CPaintView()
{
	m_pDocument=pOldDoc;

	if (m_shape)
	{
		delete m_shape;
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

	CRect rect;
	GetClientRect(&rect);
	int i;

	CPen pen(PS_DOT,1,RGB(128,128,128));
	CPen* oldPen = pDC->SelectObject(&pen);

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
// 	CString strPosition;
// 	CStatusBar* pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
// 	if (pStatus)
// 	{
// 		CPoint point;
// 		GetCursorPos(&point);
// 		strPosition.Format("X:%d",point.x);
// 		pStatus->SetPaneText(1,strPosition);
// 		strPosition.Format("Y:%d",point.y);
// 		pStatus->SetPaneText(2,strPosition);
// 	}
// 	
// 	CDC *pDC = GetDC();
// 	OnPrepareDC(pDC);
// 	pDC->DPtoLP(&point);
// 	
// 	//state1: ??????,??
// // 	if(GetCapture() == this){
// // 		m_stroke->ReDrawStroke(pDC, point);
// // 	}
// // 	//state2: ?????,??
// // 	else{	
// 		bool refresh = false;
// 		for(int i = 0; i < GetDocument()->m_strokeList.GetSize(); i ++)
// 		{
// 			if(GetDocument()->m_strokeList.GetAt(i)->IsPointIn(point)){
// 				//????
// 				SetCursor(LoadCursor(NULL, IDC_ARROW));
// 				//if state changed from NOT selected to selected
// 				if(!GetDocument()->m_strokeList.GetAt(i)->IsHightLight())
// 					refresh = true;
// 				GetDocument()->m_strokeList.GetAt(i)->SetHighLight(TRUE);
// 			}
// 			else{
// 				//if state changed from selected to NOT selected
// 				if(GetDocument()->m_strokeList.GetAt(i)->IsHightLight())
// 					refresh = true;
// 				GetDocument()->m_strokeList.GetAt(i)->SetHighLight(FALSE);
// 			}
// 		}
// 		if(refresh)
// 			Invalidate();
// //	}
// 	ReleaseDC(pDC);

	CView::OnMouseMove(nFlags, point);
}

void CPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);
	pDC->DPtoLP(&point);
	
	CPaintDoc* pDoc = GetDocument();
	
	if (m_shape && m_shape->m_bSelected)
	{
		if (m_shape->IsPointIn(point))
		{
			return;
		}
		else
		{
			//将m_shape写入到mydc里面
			//
			delete m_shape;
			m_shape = NULL;
			return;
		}
	}

	SetCapture();
	if (m_shape == NULL)
	{
		m_shape = pDoc->NewShape();
		
		m_shape->SetCurrentPoint(point);
		m_shape->m_bSelected = true;

		pDoc->SetModifiedFlag();
	}
		
	ReleaseDC(pDC);	
	
	Invalidate();
// 	CDC* pDC = GetDC();
// 	OnPrepareDC(pDC);
// 	pDC->DPtoLP(&point);
// 	
// 	CPaintDoc* pDoc = GetDocument();
// 	BOOL refresh = FALSE, bTrack = false, ctrlPressed = nFlags & MK_CONTROL;
//	int i;
// 	//??Ctrl, Track
// 	
// 	for(i = 0; i < pDoc->m_strokeList.GetSize(); i ++){
// 		if(pDoc->m_strokeList.GetAt(i)->IsPointIn(point)){
// 			//??1. ??,Ctrl??,???????
// 			if(ctrlPressed){
// 				//select/deselect
// 				pDoc->m_strokeList.GetAt(i)->m_bSelected = 
// 					!pDoc->m_strokeList.GetAt(i)->m_bSelected;
// 			}
// 			//??2. ??,??Ctrl,??
// 			else{
// 				//select
// 				pDoc->m_strokeList.GetAt(i)->m_bSelected = true;
// 			}
// 			refresh = true;
// 		}
// 		//??3. ????,??Ctrl,????
// 		else if(!ctrlPressed)
// 			pDoc->m_strokeList.GetAt(i)->m_bSelected = false;
// 	}
// 	if(refresh){
// 		Invalidate();
// 	}
// 	else{
// 		//??
// 		if(!bTrack && !ctrlPressed){
// 			//Step1. ????
// 			SetCapture();
// 			//Step2. ?????
// 			m_stroke = pDoc->NewStroke();
// 			//Step3. ????
// 			m_stroke->SetCurrentPoint(point);
// 			//Step4. ??????????
// 			pDoc->SetModifiedFlag();
// 		}
//	}
	
//	ReleaseDC(pDC);

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
			//Step1. 加入新点
			m_shape->SetCurrentPoint(point);
		
		}
		//Step2. 释放捕获
		ReleaseCapture();
		ReleaseDC(pDC);
		
		//Step3. 全部重绘
		Invalidate();
	}	
	CView::OnLButtonUp(nFlags, point);
}

void CPaintView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnRButtonDown(nFlags, point);
}
