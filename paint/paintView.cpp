// paintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "paint.h"
#include "Filter.h"
#include "paintDoc.h"
#include "paintView.h"
#include "ShapeSelect.h"

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
	bitmap.LoadBitmap(IDB_BG);///����λͼ
//	bitmap.GetBitmap(&bmp);
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

//	x = pDoc->m_cavasW;
//	y = pDoc->m_cavasH;
	OnPrepareDC(pDC);

	CRect rect;
	GetClientRect(&rect);
	int i;

	CPen pen(PS_DOT,1,RGB(128,128,128));
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
	
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
	CPaintDoc* pDoc = GetDocument();
	pDoc->MyDC = new CDC();
	pDoc->MyDC->CreateCompatibleDC(pDC);

	CBitmap MemBitmap;   
	MemBitmap.CreateCompatibleBitmap(pDC,1400,800);
	//��λͼѡ�뵽�ڴ��豸������  

	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=pDoc->MyDC->SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	pDoc->MyDC->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));
	
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
	fil.Backward(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	
		Invalidate();
}
void CPaintView::OnExposure() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Exposure(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	
	Invalidate();
}
void CPaintView::OnNeonred() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Neonred(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnRelief() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Relief(pDoc->MyDC,0,1,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnSharpen() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Sharpen(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnSleek() 
{
	// TODO: Add your command handler code here
CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Sleek(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();

}

void CPaintView::OnInlay() 
{
	// TODO: Add your command handler code here
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Inlay(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
	Invalidate();
}

void CPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//����DC�Ĺ������ԣ�����scrollview�й�
	pDC->DPtoLP(&point);//ת����ǰ��Ϊ�߼�λ������
	
	CPaintDoc* pDoc = GetDocument();
	
	if (pDoc->m_DrawType == FILL)
	{
		CDC* dc = new CDC();
		dc->CreateCompatibleDC(pDC);
		CBitmap MemBitmap;  
		//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������   
		MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
		//��λͼѡ�뵽�ڴ��豸������  
		//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
		CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
		//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
		//��Ҳ�������Լ�Ӧ���õ���ɫ  
		dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
		dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
		pDoc->m_stack.push(dc);
	
		CDC* mDC = new CDC();
		FillColor(mDC,pDoc->clr,point);

		return ;
	}


	if (m_shape && m_shape->m_bSelected)
	{	
		if (m_shape->IsPointIn(point))
		{
			int hit = m_shape->m_tracker.HitTest(point);
			if(hit >= 0 &&m_shape->m_tracker.Track(this,point,TRUE))
			{
				m_shape->ReSize(m_shape->m_tracker.m_rect);
				//////////////////////////////////////////////////////////////////////////
				// 		CRectTracker::hitNothing    �C1
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
			CDC* dc = new CDC();
			dc->CreateCompatibleDC(pDC);
			CBitmap MemBitmap;  
			//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������   
			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
			//��λͼѡ�뵽�ڴ��豸������  
			//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
			//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
			//��Ҳ�������Լ�Ӧ���õ���ɫ  
			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
			dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
			pDoc->m_stack.push(dc);

			m_shape->Draw(pDoc->MyDC);
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
	if(GetCapture() == this)
	{
		CPaintDoc *pDoc = GetDocument();		
		CDC *pDC = GetDC();
		OnPrepareDC(pDC);
		pDC->DPtoLP(&point);
		//Step0.1 ���¾��ɿ���������
		if(m_shape->m_points.GetSize() == 1)
		{
			delete m_shape;
			m_shape = NULL;
		}
		//Step0.2 ѡ���
		else 
		{
			if(SELECT == m_shape->m_nDrawType)
			{
				m_shape->SetCurrentPoint(point);
// 				if (m_shape->m_bSelected == false) 
// 				{
					 m_shape->m_bSelected = true;
					 ((CShapeSelect*)m_shape)->SetRect();
					 ((CShapeSelect*)m_shape)->SetDC(pDoc->MyDC,pDoc->m_cavasW,pDoc->m_cavasH);
			//	 }
			}
			else//Step0.3 ����
			{
				m_shape->SetCurrentPoint(point);
				m_shape->m_bSelected = true;
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
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);//����DC�Ĺ������ԣ�����scrollview�й�
	pDC->DPtoLP(&point);//ת����ǰ��Ϊ�߼�λ������
	if (m_shape && m_shape->m_bSelected)
	{
		if (m_shape->IsPointIn(point))
		{
			//////////////////////////////////////////////////////////////////////////
			//�˴���ӵ���ʽ�˵�
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{	
			CPaintDoc* pDoc = GetDocument();
			CDC* dc = new CDC();
			dc->CreateCompatibleDC(pDC);
			CBitmap MemBitmap;  
			//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������   
			MemBitmap.CreateCompatibleBitmap(pDC,pDoc->m_cavasW,pDoc->m_cavasH);  
			//��λͼѡ�뵽�ڴ��豸������  
			//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
			CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
			//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
			//��Ҳ�������Լ�Ӧ���õ���ɫ  
			dc->FillSolidRect(0,0,pDoc->m_cavasW,pDoc->m_cavasH,RGB(255,255,255));  
			dc->BitBlt(0,0,pDoc->m_cavasW,pDoc->m_cavasH,pDoc->MyDC,0,0,SRCCOPY);
			pDoc->m_stack.push(dc);

			m_shape->Draw(pDoc->MyDC);
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
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	fil.Diffuse(pDoc->MyDC,0,0,pDoc->m_cavasW,pDoc->m_cavasH);
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
		
		CDC* pDC = GetDC();//���DC
		OnPrepareDC(pDC);//����DC�Ĺ������ԣ�����scrollview�й�
		pDC->DPtoLP(&point);//ת����ǰ��Ϊ�߼�λ������
		
		//////////////////////////////////////////////////////////////////////////
		// 		CRectTracker::hitNothing    �C1
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

//DEL void CPaintView::OnEditUndo() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	CPaintDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL 	if (m_shape && m_shape->m_bSelected)
//DEL 	{
//DEL 		delete m_shape;
//DEL 		m_shape = NULL;
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
void CPaintView::FillColor(CDC* m_DC/*!!!!!!����� view����� */,COLORREF v_color/*�����ɫ*/,CPoint v_point/*����ʱ�ĵ�*/ ) 
{
	//if(û���)
	//{return}

	stack<CPoint> coloStack;  //stl ����Ҫ���ĵ�
	CClientDC dc( this );
	CRect rect;
	GetClientRect(&rect);
	CPoint currentpoint = v_point; // ���ĵ���Ϊ���ӵ�
	coloStack.push(currentpoint);  //����ѹ��ջ��

	//m_DC
	if(!m_DC->m_hDC)  
	{
		m_DC->CreateCompatibleDC(&dc);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		m_DC->SelectObject(&bitmap);
		m_DC->BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
	}
	
	COLORREF seedColor = m_DC->GetPixel(currentpoint);  //��ȡ���ӵ���ɫ

	while ( ! coloStack.empty() ) //ջ���գ�����
	{
		currentpoint = coloStack.top();
		coloStack.pop();    //��ջ
		CPoint ptArr[ 4 ];
		//��������
		ptArr[ 0 ] = CPoint( currentpoint.x - 1, currentpoint.y );
		ptArr[ 1 ] = CPoint( currentpoint.x + 1, currentpoint.y );
		ptArr[ 2 ] = CPoint( currentpoint.x, currentpoint.y - 1 );
		ptArr[ 3 ] = CPoint( currentpoint.x, currentpoint.y + 1 );
		//������ӵ���Χ�ĸ����ڿͻ������ڲ�������ɫ�����ӵ����ɫ����ͬ�ģ���ô��������ջ��
		for ( int i = 0; i < 4; i ++ )
		{
			if( ptArr[ i ].x >= rect.left && ptArr[ i ].x <= rect.right && ptArr[ i ].y >= rect.top && ptArr[ i ].y <= rect.bottom )
				if( m_DC->GetPixel( ptArr[ i ] ) == seedColor )
					coloStack.push( ptArr[ i ] );
		}
		m_DC->SetPixel( currentpoint, v_color ); //����ǰ��Ҫ���ĵ����ɫ����Ϊ���ɫ
		dc.SetPixel( currentpoint, v_color ); 

	}
	Invalidate(FALSE);
}

