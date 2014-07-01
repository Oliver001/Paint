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
: m_cavasH(600)
, m_cavasW(1000)
, m_DrawType(LINE)
, m_nLineStyle(PS_SOLID)
, m_nLineWidth(2)
, clr(RGB(0,0,0))
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
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|jpg文件(*.jpg)|*.jpg||"));

	int m_state=0;
	if (IDOK==dlg.DoModal())
	{
		m_state=0;
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt();//返回选定文件的扩展文件名
		extname.MakeLower();
		if (0==extname.Compare(_T("bmp")))
		{
			m_state  = ShowBitmap(BmpName);
		}
		else
		{
			m_state=1;
		}
	}
	if(m_state == 1)
	{
		if (0 == extname.Compare(_T("bmp")))
		{
			CDC dcImage;
			if (!dcImage.CreateCompatibleDC(MyDC))
			{
				return ;
			}
			BITMAP bm;
			bitmap.GetBitmap(&bm);
			dcImage.SelectObject(&bitmap);
			MyDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcImage,0,0,SRCCOPY);
		}
		else
		{
			if (0 == extname.Compare(_T("jpg")))
			{
				ShowJpgGif(MyDC,BmpName,1,1);
			}
		}
	}
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
	if (pView->m_shape && pView->m_shape->m_bSelected)
	{
		delete pView->m_shape;
		pView->m_shape = NULL;
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
