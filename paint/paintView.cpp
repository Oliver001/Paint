// paintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "paint.h"

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
			//修改鼠标样式，，
			//移动所绘制图形的样式
			//
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
		
		ReleaseCapture();
		ReleaseDC(pDC);
		Invalidate();
	}	
	CView::OnLButtonUp(nFlags, point);
}

void CPaintView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnRButtonDown(nFlags, point);
}
