// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "paint.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_FONTBAR, OnFontbar)
	ON_UPDATE_COMMAND_UI(IDM_FONTBAR, OnUpdateFontbar)
	ON_COMMAND(IDM_FILTERBAR, OnFilterbar)
	ON_UPDATE_COMMAND_UI(IDM_FILTERBAR, OnUpdateFilterbar)
	ON_COMMAND(IDM_DRAWBAR, OnDrawbar)
	ON_UPDATE_COMMAND_UI(IDM_DRAWBAR, OnUpdateDrawbar)
	ON_COMMAND(IDM_COLORBAR, OnColorbar)
	ON_UPDATE_COMMAND_UI(IDM_COLORBAR, OnUpdateColorbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CUR_POSITION_X,
	ID_INDICATOR_CUR_POSITION_Y,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
		if (!m_FilterToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_FLOAT_MULTI) ||
		!m_FilterToolBar.LoadToolBar(IDR_FILTERBAR))
	{
		TRACE0("Failed to create Filtertoolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC| CBRS_FLOAT_MULTI) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create mainfrmtoolbar\n");
		return -1;      // fail to create
	}

	
	if (!m_paintToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_FLOAT_MULTI) ||
		!m_paintToolBar.LoadToolBar(IDR_DRAWBAR))
	{
		TRACE0("Failed to create painttoolbar\n");
		return -1;      // fail to create
	}



	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_paintToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_paintToolBar);


// 	UINT UID = {};
//	m_FilterToolBar.SetButtons();
	if (!(m_FilterToolBar.SetButtonText(2,"Äæ·´")))
		AfxMessageBox("failed");
	m_FilterToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_FilterToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


//	cs.style|=SHOW_FULLSCREEN;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFontbar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateFontbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnFilterbar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateFilterbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnDrawbar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateDrawbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnColorbar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateColorbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
