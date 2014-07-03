// paintDoc.cpp : implementation of the CPaintDoc class
//

#include "stdafx.h"
#include "paint.h"

#include "paintDoc.h"
#include "ShapeLine.h"
#include "ShapeRect.h"
#include "ShapeEllipse.h"
#include "ShapePentagon.h"
#include "ShapeTriangle.h"
#include "ShapeSelect.h"
#include "MainFrm.h"
#include "paintView.h"
#include "TiffStruct.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc

IMPLEMENT_DYNCREATE(CPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintDoc, CDocument)
	//{{AFX_MSG_MAP(CPaintDoc)
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_RECTANGLE, OnRectangle)
	ON_COMMAND(IDM_TRIANGLE, OnTriangle)
	ON_COMMAND(IDM_FIVEANGLE, OnFiveangle)
	ON_COMMAND(IDM_CIRCLE, OnCircle)
	ON_UPDATE_COMMAND_UI(IDM_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(IDM_TRIANGLE, OnUpdateTriangle)
	ON_UPDATE_COMMAND_UI(IDM_RECTANGLE, OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(IDM_CIRCLE, OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(IDM_FIVEANGLE, OnUpdateFiveangle)
	ON_COMMAND(IDM_SELECTSHAPE, OnSelectshape)
	ON_UPDATE_COMMAND_UI(IDM_SELECTSHAPE, OnUpdateSelectshape)
	ON_COMMAND(IDM_FILL, OnFill)
	ON_UPDATE_COMMAND_UI(IDM_FILL, OnUpdateFill)
	ON_COMMAND(ID_FILEOPEN, OnFileopen)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_COPY, OnCopy)
	ON_UPDATE_COMMAND_UI(ID_COPY, OnUpdateCopy)
	ON_COMMAND(ID_PASTE, OnPaste)
	ON_UPDATE_COMMAND_UI(ID_PASTE, OnUpdatePaste)
	ON_COMMAND(ID_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(ID_CUT, OnUpdateCut)
	ON_COMMAND(ID_LEFTTRANSLATION, OnLefttranslation)
	ON_COMMAND(ID_DOWNTRANSLATION, OnDowntranslation)
	ON_COMMAND(ID_UPTRANSLATION, OnUptranslation)
	ON_COMMAND(ID_RIGHTTRANSLATION, OnRighttranslation)
	ON_COMMAND(ID_UPMIRRORING, OnUpmirroring)
	ON_COMMAND(ID_LRMIRRORING, OnLrmirroring)
	ON_COMMAND(ID_RIGHTSPIN, OnRightspin)
	ON_COMMAND(ID_LEFTSPIN, OnLeftspin)
	ON_COMMAND(ID_OAMIRRORING, OnOamirroring)
	ON_UPDATE_COMMAND_UI(ID_LEFTTRANSLATION, OnUpdateLefttranslation)
	ON_UPDATE_COMMAND_UI(ID_LEFTSPIN, OnUpdateLeftspin)
	ON_UPDATE_COMMAND_UI(ID_LRMIRRORING, OnUpdateLrmirroring)
	ON_UPDATE_COMMAND_UI(ID_OAMIRRORING, OnUpdateOamirroring)
	ON_UPDATE_COMMAND_UI(ID_RIGHTSPIN, OnUpdateRightspin)
	ON_UPDATE_COMMAND_UI(ID_RIGHTTRANSLATION, OnUpdateRighttranslation)
	ON_UPDATE_COMMAND_UI(ID_UPMIRRORING, OnUpdateUpmirroring)
	ON_UPDATE_COMMAND_UI(ID_UPTRANSLATION, OnUpdateUptranslation)
	ON_UPDATE_COMMAND_UI(ID_DOWNTRANSLATION, OnUpdateDowntranslation)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_PIXEL2, OnPixel2)
	ON_COMMAND(ID_Pixel5, OnPixel5)
	ON_COMMAND(ID_PIXEL10, OnPixel10)
	ON_COMMAND(ID_PIXEL15, OnPixel15)
	ON_COMMAND(ID_PIXEL20, OnPixel20)
	ON_COMMAND(ID_SOLID, OnSolid)
	ON_COMMAND(ID_DASH, OnDash)
	ON_COMMAND(ID_DOT, OnDot)
	ON_COMMAND(ID_PIXEL1, OnPixel1)
	ON_UPDATE_COMMAND_UI(ID_SOLID, OnUpdateSolid)
	ON_UPDATE_COMMAND_UI(ID_DASH, OnUpdateDash)
	ON_UPDATE_COMMAND_UI(ID_DOT, OnUpdateDot)
	ON_COMMAND(IDR_TEXT, OnText)
	ON_UPDATE_COMMAND_UI(IDR_TEXT, OnUpdateText)
	ON_COMMAND(ID_NET, OnNet)
	ON_UPDATE_COMMAND_UI(ID_NET, OnUpdateNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPaintDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CPaintDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IPaint to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {372F6618-4CDA-4606-88F4-B556A63CF94B}
static const IID IID_IPaint =
{ 0x372f6618, 0x4cda, 0x4606, { 0x88, 0xf4, 0xb5, 0x56, 0xa6, 0x3c, 0xf9, 0x4b } };

BEGIN_INTERFACE_MAP(CPaintDoc, CDocument)
	INTERFACE_PART(CPaintDoc, IID_IPaint, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc construction/destruction

CPaintDoc::CPaintDoc()
: m_cavasH(500)
, m_cavasW(1000)
, m_DrawType(LINE)
, m_nLineStyle(PS_SOLID)
, m_nLineWidth(5)
, clr(RGB(0,0,0))
, tempRect(0,0,0,0)
, m_bNotEmpty(false)
, m_shape(NULL)
, m_bNet(true)
{
	// TODO: add one-time construction code here
	EnableAutomation();

	AfxOleLockApp();
}

CPaintDoc::~CPaintDoc()
{
	AfxOleUnlockApp();
	while(!m_stack.empty())
	{
		CDC* dc = (CDC*)m_stack.top();
		m_stack.pop();
		
		delete dc;
	}
	if (tempDC)
	{
		delete tempDC;
	}
	if (m_shape)
	{
		delete m_shape;
	}

}

BOOL CPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPaintDoc serialization

void CPaintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc diagnostics

#ifdef _DEBUG
void CPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc commands

void CPaintDoc::OnLine() 
{
	// TODO: Add your command handler code here
	m_DrawType = LINE;
}

void CPaintDoc::OnRectangle() 
{
	// TODO: Add your command handler code here
	m_DrawType = RECTANGLE;
}

void CPaintDoc::OnTriangle() 
{
	// TODO: Add your command handler code here
	m_DrawType = TRIANGLE;
	
}

void CPaintDoc::OnFiveangle() 
{
	// TODO: Add your command handler code here
	m_DrawType = FIVEANGLE;
}

void CPaintDoc::OnCircle() 
{
	// TODO: Add your command handler code here
	m_DrawType = CIRCLE;
}

void CPaintDoc::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(LINE == m_DrawType);
}

void CPaintDoc::OnUpdateTriangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(TRIANGLE == m_DrawType);
}

void CPaintDoc::OnUpdateRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(RECTANGLE == m_DrawType);
}

void CPaintDoc::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(CIRCLE == m_DrawType);
}

void CPaintDoc::OnUpdateFiveangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(FIVEANGLE == m_DrawType);
}

CShape* CPaintDoc::NewShape()
{
	CShape* shape;
	switch (m_DrawType)
	{
	case LINE:
		shape = new CShapeLine();
		break;
	case CIRCLE:
		shape = new CShapeEllipse();
		break;
	case TRIANGLE:
		shape = new CShapeTriangle();
		break;
	case RECTANGLE:
		shape = new CShapeRect();
		break;
	case FIVEANGLE:
		shape = new CShapePentagon();
		break;
	case SELECT:
		shape = new CShapeSelect();
	}

	shape->m_color  = clr;
	shape->m_nPenStyle = m_nLineStyle;
	shape->m_nPenWidth = m_nLineWidth;

	return shape;
}

void CPaintDoc::OnSelectshape() 
{
	// TODO: Add your command handler code here
	m_DrawType = SELECT;
}

void CPaintDoc::OnUpdateSelectshape(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrawType == SELECT);
	
}


void CPaintDoc::OnFill() 
{
	// TODO: Add your command handler code here
	m_DrawType = FILL;
}

void CPaintDoc::OnUpdateFill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrawType == FILL);
}

void CPaintDoc::OnFileopen() 
{
	// TODO: 在此添加命令处理程序代码
	//CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|jpg文件(*.jpg)|*.jpg||"));
CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|jpg文件(*.jpg)|*.jpg|tif文件(*.tif)|*.tif||"));
	int m_state=0;
	if (IDOK==dlg.DoModal())
	{
		m_state=0;
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt();//返回选定文件的扩展文件名
		extname.MakeLower();
// 		if (0==extname.Compare(_T("bmp")))
// 		{
// 			m_state  = ShowBitmap(BmpName);
// 		}
// 		else 
// 		{
// 			m_state=1;
// 		}

		if (0 == extname.Compare(_T("bmp")))
		{
			CDC dcImage;
			if (!dcImage.CreateCompatibleDC(MyDC))
			{
				return ;
			}
			ShowBitmap(BmpName);
			BITMAP bm;
			bitmap.GetBitmap(&bm);
			dcImage.SelectObject(&bitmap);
			MyDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcImage,0,0,SRCCOPY);
		}
		else if (0 == extname.Compare(_T("jpg")))
		{
			ShowJpgGif(MyDC,BmpName,1,1);
		}
		else if(0==extname.Compare(_T("tif")))
		{
			m_state=2;
			OpenTifDocumen();
		}
		
	}
// 	if(m_state == 1)
// 	{
// 		if (0 == extname.Compare(_T("bmp")))
// 		{
// 			CDC dcImage;
// 			if (!dcImage.CreateCompatibleDC(MyDC))
// 			{
// 				return ;
// 			}
// 			BITMAP bm;
// 			bitmap.GetBitmap(&bm);
// 			dcImage.SelectObject(&bitmap);
// 			MyDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcImage,0,0,SRCCOPY);
// 		}
// 		else
// 		{
// 			if (0 == extname.Compare(_T("jpg")))
// 			{
// 				ShowJpgGif(MyDC,BmpName,1,1);
// 			}
// 		}
// 	}


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CPaintView*pView = (CPaintView*)pMainFrame->GetActiveView();
	pView->Invalidate();
}


bool CPaintDoc::ShowBitmap(CString BmpName)
{
	HBITMAP hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
		LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	bitmap.Detach();
	bitmap.Attach(hBitmap);
	return true;
}

bool CPaintDoc::ShowJpgGif(CDC* pDC,CString strPath, int x, int y)
{
	IStream *pStm;
	CFileStatus fstatus;
	CFile file;
	LONG cb;
	//打开文件并检测文件的有效性
	if (file.Open(strPath,CFile::modeRead)&&
		file.GetStatus(strPath,fstatus)&&
		((cb = fstatus.m_size) != -1))
	{
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);
		LPVOID pvData = NULL;
		if (hGlobal != NULL)
		{
			pvData = GlobalLock(hGlobal);
			if (pvData != NULL)
			{
				//file.ReadHuge(pvData, cb);??//6.0中
				file.Read(pvData, cb);//
				GlobalUnlock(hGlobal);
				CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);
			}
		}
	}
	else
	{
		return false;
	}//end


	IPicture *pPic;
	if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)))
	{
		OLE_XSIZE_HIMETRIC hmWidth;
		OLE_YSIZE_HIMETRIC hmHeight;
		pPic->get_Width(&hmWidth);
		pPic->get_Height(&hmHeight);
		double fX,fY;


		fX = (double)pDC->GetDeviceCaps(VERTRES/*定值*/)*
			(double)hmHeight/((double)pDC->GetDeviceCaps(VERTSIZE)*100.0);
		fY =(double)pDC->GetDeviceCaps(VERTRES)*
			(double)hmHeight/((double)pDC->GetDeviceCaps(VERTSIZE)*100.0);
		if(FAILED(pPic->Render(*pDC,x,y,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL)))
		{
			/*  看似解释的很清楚，但是有很多地方带有迷惑性，跟实际情况，跟人们想象的不同。我就是这样，研究了半天才弄明白。
				hdc 是设备环境句柄，
				x、y是图片在设备中显示的坐标，
				cx、cy是要显示图片的矩形的长度和宽度，注意，用IPicture::get_Width和IPicture::get_Height的得到的数据并不适用于此处，而是要除以26.45
				xSrc，ySrc分别是在源图像上的水平偏移和在源图像上的垂直偏移；
				cxSrc是在源图像上水平拷贝的数量，cySrc是在源图像上垂直拷贝的数量；
				prcWBounds是指向目标图元设备环境句柄的指针，一般为NULL。
				为什么用render函数的时候都是Render(hdc,  xPos,  yPos,  width,    height, 0,  srcHeight,srcWidth,-srcHeight);
			这是一个问题..........
				原因是这样的：这个和位图的格式有关，位图文件中最开始的像素数据不是图像左上角这个像素，而是图像中最后一行最左边像素点的数据。
				所以左顶点是（0,hmHeight）
				hmWidth表示宽度
				-hmHeight是负数，表示从最后一行读取，并显示在第一行。*/

			pPic->Release();
			return false;
		}
		pPic->Release();
	}
	else
	{
		return false;
	}
	return true;
}


bool CPaintDoc::Reset(int w, int h)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CPaintView*pView = (CPaintView*)pMainFrame->GetActiveView();
 //	pView->Invalidate();

	CDC* dc = new CDC();
	dc->CreateCompatibleDC(pView->GetDC());
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
	MemBitmap.CreateCompatibleBitmap(MyDC,w,h);
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	dc->FillSolidRect(0,0,m_cavasW,m_cavasH,RGB(255,255,255));  
	dc->BitBlt(0,0,m_cavasW,m_cavasH,MyDC,0,0,SRCCOPY);
//	delete MyDC;
	MyDC = dc;

// 	CDC* pDC = new CDC;
// 	pDC->CreateCompatibleDC(MyDC);
// 	CBitmap MemBitmap;   
// 	MemBitmap.CreateCompatibleBitmap(pDC,w,h);  
// 	CBitmap *pOldBit=pDC->SelectObject(&MemBitmap);  
// 	pDC->FillSolidRect(0,0,w,h,RGB(255,255,255));  
// 	if (MyDC)
// 	{
// 		if (!pDC->BitBlt(0,0,m_cavasW,m_cavasH,MyDC,0,0,SRCCOPY))
// 			return false;
// 		delete MyDC;
// 		MyDC = pDC;
 		m_cavasW = w;
 		m_cavasH = h;
// 	}
	dc->SelectObject(pOldBit);

// 	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
// 	CPaintView*pView = (CPaintView*)pMainFrame->GetActiveView();
// 	pView->Invalidate();
	return true;
}

void CPaintDoc::OnEditUndo() 
{
	// TODO: Add your command handler code here
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CPaintView*pView = (CPaintView*)pMainFrame->GetActiveView();

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
			MyDC->BitBlt(0,0,m_cavasW,m_cavasH,dc,0,0,SRCCOPY);
			m_stack.pop();
			
			delete dc;
		}
	}
	pView->Invalidate();
	
}

void CPaintDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_stack.empty());
}

void CPaintDoc::OnCopy() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	tempDC->FillSolidRect(0,0,1400,800,RGB(255,255,255));
// 	int x1 = m_shape->m_points[0].x < m_shape->m_points[1].x?m_shape->m_points[0].x : m_shape->m_points[1].x;
// 	int x2 =  m_shape->m_points[0].x > m_shape->m_points[1].x?m_shape->m_points[0].x : m_shape->m_points[1].x;
// 	int y1 = m_shape->m_points[0].y < m_shape->m_points[1].y?m_shape->m_points[0].y : m_shape->m_points[1].y;
// 	int y2 =  m_shape->m_points[0].y > m_shape->m_points[1].y?m_shape->m_points[0].y : m_shape->m_points[1].y;

	tempRect = ((CShapeSelect*)m_shape)->selectRect;
	tempDC->BitBlt(tempRect.left,tempRect.top,tempRect.Width(),tempRect.Height(),MyDC,tempRect.left,tempRect.top,SRCCOPY);
// 	tempRect = CRect(x1,y1,x2,y2);
// 	tempDC->BitBlt(x1,y1,x2-x1,y2-y1,MyDC,x1,y1,SRCCOPY);
	m_bNotEmpty = true;
}

void CPaintDoc::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	pCmdUI->Enable((m_shape) && (m_shape->m_nDrawType == SELECT) && (m_shape->m_bSelected));
}

void CPaintDoc::OnPaste() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	BackUp();
	if (m_shape)
	{
		m_shape->Draw(MyDC);
		delete m_shape;
		m_shape = NULL;
	}
	m_shape = NewShape();
	m_shape->SetCurrentPoint(CPoint(tempRect.left,tempRect.top));
	m_shape->SetCurrentPoint(CPoint(tempRect.right,tempRect.bottom));
	((CShapeSelect*)m_shape)->type = SELECTPASTE;
	
	m_shape->m_bSelected = true;
	((CShapeSelect*)m_shape)->SetRect();
	((CShapeSelect*)m_shape)->SetDC(tempDC,tempRect.Width(),tempRect.Height());
	
//	MyDC->StretchBlt(0,0,tempRect.Width(),tempRect.Height(),tempDC/*MyDC*//*((CShapeSelect*)m_shape)->selectDC*/,tempRect.left,tempRect.top,tempRect.Width(),tempRect.Height(),SRCCOPY);

// 	m_shape->m_points[0].x = 0;
// 	m_shape->m_points[0].y = 0;
// 	m_shape->m_points[1].x = tempRect.Width();
// 	m_shape->m_points[1].y = tempRect.Height();
// 	//SetCurrentPoint(CPoint(tempRect.left,tempRect.top));
// 	//m_shape->SetCurrentPoint(CPoint(tempRect.right,tempRect.bottom));
	
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bNotEmpty);
}

void CPaintDoc::OnCut() 
{
	// TODO: Add your command handler code here
	BackUp();
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	tempDC->FillSolidRect(0,0,1400,800,RGB(255,255,255));
// 	int x1 = m_shape->m_points[0].x < m_shape->m_points[1].x?m_shape->m_points[0].x : m_shape->m_points[1].x;
// 	int x2 =  m_shape->m_points[0].x > m_shape->m_points[1].x?m_shape->m_points[0].x : m_shape->m_points[1].x;
// 	int y1 = m_shape->m_points[0].y < m_shape->m_points[1].y?m_shape->m_points[0].y : m_shape->m_points[1].y;
// 	int y2 =  m_shape->m_points[0].y > m_shape->m_points[1].y?m_shape->m_points[0].y : m_shape->m_points[1].y;
// 	tempRect = CRect(x1,y1,x2,y2);
	tempRect = ((CShapeSelect*)m_shape)->selectRect;
	tempDC->BitBlt(tempRect.left,tempRect.top,tempRect.Width(),tempRect.Height(),MyDC,tempRect.left,tempRect.top,SRCCOPY);
	
	
	
//	tempDC->BitBlt(x1,y1,x2-x1,y2-y1,((CShapeSelect*)m_shape)->selectDC,x1,y1,SRCCOPY);

	if (m_shape)
	{
	//	m_shape->Draw(MyDC);
		delete m_shape;
		m_shape = NULL;
	}
	MyDC->FillSolidRect(tempRect.left,tempRect.top,tempRect.Width(),tempRect.Height(),RGB(255,255,255));
	
	m_bNotEmpty = true;
// 
//  	delete m_shape;
//  	m_shape = NULL;

	pView->Invalidate(FALSE);
}

void CPaintDoc::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	pCmdUI->Enable((m_shape) && (m_shape->m_nDrawType == SELECT) && (m_shape->m_bSelected));
}

void CPaintDoc::BackUp()
{
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	CDC* dc = new CDC();
	dc->CreateCompatibleDC(pView->GetDC());
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）   
	MemBitmap.CreateCompatibleBitmap(pView->GetDC(),m_cavasW,m_cavasH);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=dc->SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	dc->FillSolidRect(0,0,m_cavasW,m_cavasH,RGB(255,255,255));  
	dc->BitBlt(0,0,m_cavasW,m_cavasH,MyDC,0,0,SRCCOPY);
	m_stack.push(dc);
}

void CPaintDoc::OnLefttranslation() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Move(-1,0);
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnDowntranslation() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Move(0,1);
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnUptranslation() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Move(0,-1);
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnRighttranslation() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Move(1,0);
	pView->Invalidate(FALSE);
}


void CPaintDoc::OnUpmirroring() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	if (m_DrawType  == LINE)
	{
		m_shape->Rotate();
	}
	else if (m_DrawType == CIRCLE)
	{
			/////
	}
	else if (m_DrawType == TRIANGLE)
	{
		if (m_shape->m_nRorate%2)
		{
		}
		else
		{
			m_shape->Rotate();
			m_shape->Rotate();
		}
	}
	else if (m_DrawType == RECTANGLE)
	{
		/////
	}
	else if (m_DrawType == FIVEANGLE)
	{
		if (m_shape->m_nRorate%2)
		{
		}
		else
		{
			m_shape->Rotate();
			m_shape->Rotate();
		}
	}
	else //select
	{
		m_shape->mirror = 1;
	}

	pView->Invalidate(FALSE);
}

void CPaintDoc::OnLrmirroring() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	if (m_DrawType  == LINE)
	{
		m_shape->Rotate();
	}
	else if (m_DrawType == CIRCLE)
	{
		/////
	}
	else if (m_DrawType == TRIANGLE)
	{
		if (!(m_shape->m_nRorate%2))
		{
		}
		else
		{
			m_shape->Rotate();
			m_shape->Rotate();
		}
	}
	else if (m_DrawType == RECTANGLE)
	{
		/////
	}
	else if (m_DrawType == FIVEANGLE)
	{
		if (!(m_shape->m_nRorate%2))
		{
		}
		else
		{
			m_shape->Rotate();
			m_shape->Rotate();
		}
	}
	else //select
	{
		m_shape->mirror = 2;
	}
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnRightspin() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Rotate();
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnLeftspin() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	m_shape->Rotate();
	m_shape->Rotate();
	m_shape->Rotate();
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnOamirroring() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	if (m_DrawType  == LINE)
	{
		m_shape->Rotate();
	}
	else if (m_DrawType == CIRCLE)
	{
		/////
	}
	else if (m_DrawType == TRIANGLE)
	{
		if (m_shape->m_nRorate == 0 )
		{
			m_shape->m_nRorate = 1;
		}
		else if (m_shape->m_nRorate == 1 )
		{
			m_shape->m_nRorate = 0;
		}
		if (m_shape->m_nRorate == 2 )
		{
			m_shape->m_nRorate = 3;
		}
		else if (m_shape->m_nRorate == 3 )
		{
			m_shape->m_nRorate = 2;
		}
	}
	else if (m_DrawType == RECTANGLE)
	{
		/////
	}
	else if (m_DrawType == FIVEANGLE)
	{
		if (m_shape->m_nRorate == 0 )
		{
			m_shape->m_nRorate = 1;
		}
		else if (m_shape->m_nRorate == 1 )
		{
			m_shape->m_nRorate = 0;
		}
		if (m_shape->m_nRorate == 2 )
		{
			m_shape->m_nRorate = 3;
		}
		else if (m_shape->m_nRorate == 3 )
		{
			m_shape->m_nRorate = 2;
		}
	}
	else //select
	{
		m_shape->mirror = 3;
	}
	pView->Invalidate(FALSE);
}

void CPaintDoc::OnUpdateLefttranslation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
	
}

void CPaintDoc::OnUpdateLeftspin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateLrmirroring(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateOamirroring(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateRightspin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateRighttranslation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateSmallzoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateUpmirroring(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateUptranslation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateDowntranslation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnUpdateBigzoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_shape && m_shape->m_bSelected);
}

void CPaintDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	BITMAPINFO bi;
	void* pBits = NULL;
	CRect rect(0,0,m_cavasW,m_cavasH);
//	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;
	//填信息
	ZeroMemory(&bi,sizeof(bi));
	bi.bmiHeader.biSize=sizeof(bi.bmiHeader);
	bi.bmiHeader.biHeight=nHeight;
	bi.bmiHeader.biWidth=nWidth;
	bi.bmiHeader.biPlanes=1;
	bi.bmiHeader.biBitCount=24;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biSizeImage=3*nWidth*nHeight;
	
	//拷贝客户区到内存
	HDC hActiveDC=MyDC->GetSafeHdc(); // 窗口句柄原来就有啊
	HDC hActiveWndCompatibleDC=CreateCompatibleDC(hActiveDC);  //兼容DC 已经出现了好多次了
	HBITMAP hActiveWndCompactibleBitmap=CreateCompatibleBitmap(hActiveDC,rect.right,rect.bottom);//HBITMAP 句柄 已经出现了好多次了 
	SelectObject(hActiveWndCompatibleDC,hActiveWndCompactibleBitmap);  //SELECTOBJECT()
	BitBlt(hActiveWndCompatibleDC,0,0,rect.right,rect.bottom,hActiveDC,0,0,SRCCOPY); //BitBlt  hActiveWndCompatibleDC
	//保存内存DC
	HDC hBmpFileDC=CreateCompatibleDC(hActiveWndCompatibleDC);
	HBITMAP hBmpFileBitmap=CreateDIBSection(hActiveWndCompatibleDC,&bi,DIB_RGB_COLORS,&pBits,NULL,0);
	SelectObject(hBmpFileDC,hBmpFileBitmap);
	BitBlt(hBmpFileDC,0,0,nWidth,nHeight,hActiveWndCompatibleDC,0,0,SRCCOPY);
	
	///CFileDialog 
	CString tempFileName=_T("test.bmp");
	CFileDialog dlg(FALSE, _T("bmp"), _T("Temp.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), pView);
	
	if(dlg.DoModal() == IDOK)
	{
		tempFileName=dlg.GetPathName();
	}
	HANDLE hFile=CreateFile(tempFileName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		DWORD dwRet=0;
		//填充文件头
		BITMAPFILEHEADER bmfHeader;
		ZeroMemory(&bmfHeader,sizeof(bmfHeader));
		bmfHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		bmfHeader.bfSize=bi.bmiHeader.biSizeImage+bmfHeader.bfOffBits;
		bmfHeader.bfType='MB';
		WriteFile(hFile,&bmfHeader,sizeof(bmfHeader),&dwRet,NULL);
		WriteFile(hFile,&bi.bmiHeader,sizeof(bi.bmiHeader),&dwRet,NULL);
		WriteFile(hFile,pBits,bi.bmiHeader.biSizeImage,&dwRet,NULL);
		CloseHandle(hFile);
	}
}

void CPaintDoc::OnPixel2() 
{
	// TODO: Add your command handler code here
		m_nLineWidth = 2;
		CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnPixel5() 
{
	// TODO: Add your command handler code here
	m_nLineWidth = 5;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnPixel10() 
{
	// TODO: Add your command handler code here
	m_nLineWidth = 10;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnPixel15() 
{
	// TODO: Add your command handler code here
	m_nLineWidth = 15;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnPixel20() 
{
	// TODO: Add your command handler code here
	m_nLineWidth = 20;
		CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnSolid() 
{
	// TODO: Add your command handler code here
	m_nLineStyle = PS_SOLID;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnDash() 
{
	// TODO: Add your command handler code here
	m_nLineStyle = PS_DASH;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnDot() 
{
	// TODO: Add your command handler code here
	m_nLineStyle = PS_DOT;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnPixel1() 
{
	// TODO: Add your command handler code here
	m_nLineWidth = 1;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnUpdateSolid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nLineWidth == 1);
}

void CPaintDoc::OnUpdateDash(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nLineWidth == 1);
}

void CPaintDoc::OnUpdateDot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nLineWidth == 1);
}

void CPaintDoc::OnText() 
{
	// TODO: Add your command handler code here
	m_DrawType = MYTEXT;
}

void CPaintDoc::OnUpdateText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrawType == MYTEXT);
}

void CPaintDoc::OnNet() 
{
	// TODO: Add your command handler code here
	m_bNet = !m_bNet;
	CPaintView* pView = (CPaintView* )((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Invalidate(FALSE);
}

void CPaintDoc::OnUpdateNet(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bNet);
}
BOOL CPaintDoc::OpenTifDocumen(void)
{
	DWORD dwFileLength = 0;
	CString strTemp = _T("");
	WORD wDECount = 0;
	BYTE* pDIB = NULL;       //内存块的指针  一个 HANDLE 的指针
	int i = 0;
	IFH ifh;
	ZeroMemory(&ifh, sizeof(IFH));
	CFile file;
	CFileException fe;
	//打开文件
	if(0 == file.Open(BmpName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		AfxMessageBox("打开文件失败");
		return FALSE;
	}
	dwFileLength = file.GetLength();

	//读文件头 IFH
	if(sizeof(IFH) != file.Read(&ifh, sizeof(IFH)))
	{
		AfxMessageBox("读取TIF文件头(IFH)失败");
		return FALSE;
	}
	//Version成员总是包含十进制42(0x2a)  42这个数大概永远不会变化
	if(0x2a != ifh.version)
	{
		AfxMessageBox("该文件不是TIF格式，读文件失败");
		return FALSE;
	}

	if(0x4949 != ifh.byteOrder)
	{
		AfxMessageBox("该TIF文件字节序错误，读文件失败");
		return FALSE;
	}
	//文件指针 定位在IFH
	file.Seek(ifh.offsetToIFD, CFile::begin);
	//DECount
	if(2 != file.Read(&wDECount, 2))
	{
		AfxMessageBox("无法获得TIF文件目录入口数量");
		return FALSE;
	}
	//strTemp.Format("该TIF文件有%d个目录入口", wDECount);
	//AfxMessageBox(strTemp); //显示有多少个目录入口
	//创建wDECount个DE数组
	DE* pde = new DE[wDECount];
	DE* pTemp = pde;
	memset(pde, 0, sizeof(DE)*wDECount);

	if(sizeof(DE)*wDECount != file.Read(pde, sizeof(DE)*wDECount))
	{
		AfxMessageBox("读图象文件目录失败");
		delete []pde;
		return FALSE;
	}
	//for(i=0; i<wDECount; i++)
	//{
	//	pTemp = pde + i;
	//	strTemp.Format
	//		("DE[%d].tag = %d\r\nDE[%d].type = %d\r\nDE[%d].length = %d\r\nDE[%d].valueOffset=%d",
	//		i,pTemp->tag,i,pTemp->type,i,pTemp->length,i,
	//		pTemp->valueOffset);
	//	AfxMessageBox(strTemp);//显示目录文件信息
	//}

	for(i=0; i<wDECount; i++)
	{
		pTemp = pde + i;
		if(256 == pTemp->tag)//tag为256的目录入口中的变量标识了    图象宽度
		{
			m_sizeDoc.cx = pTemp->valueOffset;
		}
		if(257 == pTemp->tag)// tag为257的目录入口中的变量标识了    图象长度
		{
			m_sizeDoc.cy = pTemp->valueOffset;
		}
		if(273 == pTemp->tag)//计算图象数据                         占用字节数
		{
			m_dwBmSize = m_sizeDoc.cx * m_sizeDoc.cy;
		}
	}

	//构造BMP图象内存块  
	if(!CreateBmpBuffer())
	{
		AfxMessageBox("构造BMP图象内存块失败");
		delete []pde;
		return FALSE;
	}

//BMP内存块指针
	pDIB = (BYTE*)GlobalLock(m_hDIB);

	if(NULL == pDIB)
	{
		AfxMessageBox("获得BMP内存块指针失败");
		GlobalUnlock(m_hDIB);
		delete []pde;
		return FALSE;
	}
//////////////////////////////////////////////////
////////构造BITMAPFILEHEADER并复制到BMP内存块
	BITMAPFILEHEADER bmfHdr;
	/*Sets buffers to a specified character*/
	memset(&bmfHdr, 0, sizeof(BITMAPFILEHEADER));
	/*bfOffBits 从文件头开始到颜色数据的偏移量*/
	bmfHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		/*RGBQUAD颜色结构体*/
		256*sizeof(RGBQUAD);
	 /*bfReserved1和bfReserved1必须为0*/
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	 /*bfSize  图片的大小*/
	bmfHdr.bfSize = bmfHdr.bfOffBits + m_dwBmSize;
	/* bfType  图片的类型 必须是BM 填0x4d42即十进制的19778*/
	bmfHdr.bfType = 0x4d42;
	/*Moves one buffer to another.*/
	memmove(pDIB, &bmfHdr, sizeof(BITMAPFILEHEADER));

///////////////////////////////////////////////////////////////////
	//构造BITMAPINFOHEADER并复制到BMP内存块

	//biSize：本结构的长度，为40个字节。
	//	biWidth：位图的宽度，以像素为单位。
	//	biHeight：位图的高度，以像素为单位。
	//	biPlanes：目标设备的级别，必须是1。
	//	biBitCount：每个像素所占的位数（bit），其值必须为1（黑白图像）、4（16色图）、8（256色）、24（真彩色图），新的BMP格式支持32位色。
	//	biCompresssion：位图压缩类型，有效的值为BI_RGB（未经压缩）、BI_RLE8、BI_RLE4、BI_BITFILEDS（均为Windows定义常量）。这里只讨论未经压缩的情况，即biCompression=BI_RGB。
	//	biSizeImage：实际的位图数据占用的字节数，该值的大小在第4部分位图数据中有具体解释。
	//	biXPelsPerMeter：指定目标设备的水平分辨率，单位是像素/米。
	//	biYPelsPerMeter：指定目标设备的垂直分辨率，单位是像素/米。
	//	biClrUsed：位图实际用到的颜色数，如果该值为零，则用到的颜色数为2的biBitCount次幂。
	//	biClrImportant：位图显示过程中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。
	BITMAPINFOHEADER bmiHdr;
	//myself after
	BITMAPINFO *bitmapinfo;
	bitmapinfo=(BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	//myself after
	memset(&bmiHdr, 0, sizeof(BITMAPINFOHEADER));
	/*biBitCount：每个像素所占的位数（bit），其值必须为1
		（黑白图像）、4（16色图）、8（256色）、24（真彩色图），新的BMP格式支持32位色。*/
	bmiHdr.biBitCount = 8;
	bmiHdr.biClrImportant = 0;
	bmiHdr.biClrUsed = 0;
	bmiHdr.biCompression = 0;

	bmiHdr.biHeight = m_sizeDoc.cy;
	bmiHdr.biPlanes = 1;
	bmiHdr.biSize = sizeof(BITMAPINFOHEADER);
	bmiHdr.biSizeImage = 0;

	bmiHdr.biWidth = m_sizeDoc.cx;
	bmiHdr.biXPelsPerMeter = 2834;
	bmiHdr.biYPelsPerMeter = 2834;
	memmove((BITMAPFILEHEADER*)pDIB + 1, &bmiHdr, sizeof(BITMAPINFOHEADER));
	memcpy(bitmapinfo,&bmiHdr,sizeof(BITMAPINFOHEADER));
	//myself after
	bitmap_Info = bmiHdr;
	//myself after
	this->struct_bitmapInfo = *bitmapinfo;
	//myself after

	//构造256个RGBQUAD并复制到BMP内存块
	RGBQUAD* pRgbQuad = (RGBQUAD*)(pDIB + sizeof(BITMAPFILEHEADER) +      
		sizeof(BITMAPINFOHEADER));
	RGBQUAD* pOldQuad = pRgbQuad;
	RGBQUAD rgbQuad;
	memset(&rgbQuad, 0, sizeof(RGBQUAD));
	for(i=0; i<256; i++)
	{
		rgbQuad.rgbBlue = i;
		rgbQuad.rgbGreen = i;
		rgbQuad.rgbRed = i;
		rgbQuad.rgbReserved = 0;
		pRgbQuad = pOldQuad + i;
		memmove(pRgbQuad, &rgbQuad, sizeof(RGBQUAD));
	}
	//填充所有像素数据, 颠倒图象数据从最后一行开始读起
	int j = 0;
	for(i=m_sizeDoc.cy-1; i>=0; i--)
	{
		file.Seek(sizeof(IFH) + i*m_sizeDoc.cx, CFile::begin);
		file.Read((BYTE*)(pRgbQuad + 1) + j*m_sizeDoc.cx, m_sizeDoc.cx);
		j++;
	}


	//初始化专用调色板
	BYTE buf[2+2+4*256];
	LOGPALETTE* pPal = (LOGPALETTE*)buf;
	pPal->palVersion = 0x300;
	pPal->palNumEntries = 256;
	for(i=0; i<255; i++)
	{
		pPal->palPalEntry[i].peBlue = i;
		pPal->palPalEntry[i].peFlags = 0;
		pPal->palPalEntry[i].peGreen = i;
		pPal->palPalEntry[i].peRed = i;
	}
	m_palDIB.CreatePalette(pPal);

	//（附加功能）生成bmp文件
	CFile fileWrite("C:\\mytiff.bmp", CFile::modeCreate | CFile::modeWrite);
	fileWrite.Write(pDIB, sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) + 256*sizeof(RGBQUAD) + m_dwBmSize);

	if(NULL == m_hDIB)
	{
		return FALSE;
	}
	HDC hdc = MyDC->m_hDC;
	BYTE* pBuf = (BYTE*)GlobalLock(m_hDIB);
	pBuf += sizeof(BITMAPFILEHEADER);
	BYTE* pData = pBuf + sizeof(BITMAPINFOHEADER) + 256*sizeof(RGBQUAD);
	CPalette* pOldPal = MyDC->SelectPalette(&m_palDIB, TRUE);
	MyDC->RealizePalette();
	::SetStretchBltMode(hdc, COLORONCOLOR);
	::StretchDIBits(hdc, 10, 10, m_sizeDoc.cx, m_sizeDoc.cy,
		0, 0, m_sizeDoc.cx, m_sizeDoc.cy, pData,
		(BITMAPINFO*)pBuf, DIB_RGB_COLORS, SRCCOPY);
	MyDC->SelectPalette(pOldPal, FALSE);
//		GlobalUnlock(m_hDIB);

//	OnOpenDocument成员函数返回前的清理工作
	GlobalUnlock(m_hDIB);
	delete []pde;
	return TRUE;

}

//分配指定大小的 堆内存
BOOL CPaintDoc::CreateBmpBuffer(void)
{
	//申请BMP内存块
	m_hDIB = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
		sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		256*sizeof(RGBQUAD) +
		m_dwBmSize);
	if(NULL == m_hDIB)
	{
		AfxMessageBox("申请BMP内存块失败");
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
