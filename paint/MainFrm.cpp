// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "paint.h"

#include "MainFrm.h"
#include "HColorBar.h"
#include "paintDoc.h"

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
	ON_NOTIFY(TBN_DROPDOWN,AFX_IDW_TOOLBAR,OnToolbarDropDown)//此行即为新增的ON_NOTIFY消息映射
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_COMMAND(IDM_GEOMTRANSBAR, OnGeomtransbar)
	ON_UPDATE_COMMAND_UI(IDM_GEOMTRANSBAR, OnUpdateGeomtransbar)
	ON_UPDATE_COMMAND_UI(IDR_SETLINE_W, OnUpdateSetlineW)
	ON_UPDATE_COMMAND_UI(IDR_SETLINE_S, OnUpdateSetlineS)
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
	wndBar=true;
	paintbar=true;
	filterbar=true;
	colorbar=true;
	transbar=true;
}

CMainFrame::~CMainFrame()
{
	delete m_colorBar;
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

	m_colorBar = new HColorBar();
	if (!m_colorBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_colorBar->LoadToolBar(IDR_COLORBAR))
	{
		TRACE0("Failed to create colorbar\n");
		return -1;      // fail to create
	}

	if (!m_transBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_FLOAT_MULTI) ||
		!m_transBar.LoadToolBar(IDR_GEOMTRANSBAR))
	{
		TRACE0("Failed to create transToolBar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//docking the first toolbar
// 		m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 		EnableDocking(CBRS_ALIGN_ANY);
// 	
// // 	CRect rectone;
// // 	m_wndToolBar.GetWindowRect( &rectone);
// //     rectone.OffsetRect(0, 1);
// //     TRACE("rectone left%d, right%d top%d ,bott%d\n",rectone.left,rectone.right,rectone.top,rectone.bottom);
// //     RecalcLayout(TRUE);//重排
// //     DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_TOP, &rectone);
// 
//     //docking the second toolbar
// 	m_FilterToolBar.EnableDocking(CBRS_ALIGN_ANY);
// //  CRect rectone;
// //  m_FilterToolBar.GetWindowRect( &rectone);
// //   rectone.OffsetRect(0, 1);
// //   TRACE("rectone left%d, right%d top%d ,bott%d\n",rectone.left,rectone.right,rectone.top,rectone.bottom);
// //   RecalcLayout(TRUE);//重排
// //  DockControlBar(&m_FilterToolBar, AFX_IDW_DOCKBAR_TOP, &rectone);
// 	DockControlBarLeftOf(&m_FilterToolBar,&m_wndToolBar);
    //docking the third toolbar
//    m_transBar.EnableDocking(CBRS_ALIGN_ANY);
//     CRect recttwo;
//     m_transBar.GetWindowRect( &recttwo);
//     recttwo.OffsetRect(0,1);
//     TRACE("recttwo left%d, right%d top%d ,bott%d\n",recttwo.left,recttwo.right,recttwo.top,recttwo.bottom);
//     RecalcLayout(TRUE);
//    DockControlBar(&m_transBar, AFX_IDW_DOCKBAR_TOP, &recttwo);

    //docking the fourth toolbar
//     m_colorBar->EnableDocking(CBRS_ALIGN_BOTTOM);
// //     CRect rectthree;
// //     EnableDocking(CBRS_ALIGN_ANY);
// //     m_wndToolBarThree.GetWindowRect( &rectthree );
// //     RecalcLayout(TRUE); 
// //     rectthree.OffsetRect(2000, 0);
// //     TRACE("rectthree left%d, right%d top%d ,bott%d\n",rectthree.left,rectthree.right,rectthree.top,rectthree.bottom);
//     DockControlBar(m_colorBar);
// 
// 	m_paintToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 	DockControlBar(&m_paintToolBar);
// 	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_paintToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_paintToolBar);

	m_FilterToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&m_FilterToolBar,&m_wndToolBar);

	m_colorBar->EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(m_colorBar);


	m_transBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&m_transBar,&m_FilterToolBar);

	//为画图工具栏的按钮添加下拉菜单
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
		//取值TBSTYLE_EX_DRAWDDARROWS，可以为某一个按钮添加下拉按钮。
	DWORD dwStyle=m_wndToolBar.GetButtonStyle(m_wndToolBar.CommandToIndex(IDR_SETLINE_W));
		dwStyle|=TBSTYLE_DROPDOWN;//其中ID_DRAW_LINE是你要添加下拉菜单的按钮的ID
	m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDR_SETLINE_W),dwStyle);

	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	//取值TBSTYLE_EX_DRAWDDARROWS，可以为某一个按钮添加下拉按钮。
	dwStyle=m_wndToolBar.GetButtonStyle(m_wndToolBar.CommandToIndex(IDR_SETLINE_S));
	dwStyle|=TBSTYLE_DROPDOWN;//其中ID_DRAW_LINE是你要添加下拉菜单的按钮的ID
	m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDR_SETLINE_S),dwStyle);


	return 0;
}
void CMainFrame::DockControlBarLeftOf(CToolBar* Bar, CToolBar* LeftOf) 
{ 
	CRect rect; 
    DWORD dw; 
    UINT n; 
	
    // 让 MFC 调整所有浮动工具条的尺寸，以便GetWindowRect的到准确结果 
    RecalcLayout(TRUE); 
	
    LeftOf->GetWindowRect(&rect); 
    rect.OffsetRect(1,0); 
    dw=LeftOf->GetBarStyle(); 
    n = 0; 
    n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n; 
    n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n; 
    n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n; 
    n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n; 
	
    // 当矩形使用默认参数时，DockControlBar 将在单独的一行里浮动工具条， 
    // 通过计算矩形的大小来模拟工具条拖动到指定位置实现浮动。 
    DockControlBar(Bar,n,&rect);
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
	if (!filterbar)
	{
		m_FilterToolBar.ShowWindow(SW_SHOW);
	
	} 
	else
	{	
		m_FilterToolBar.ShowWindow(SW_HIDE);
	}
	filterbar= !filterbar;
	DockControlBar(&m_FilterToolBar);
}

void CMainFrame::OnUpdateFilterbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(filterbar);
}

void CMainFrame::OnDrawbar() 
{
	// TODO: Add your command handler code here
	if (!paintbar)
	{
		m_paintToolBar.ShowWindow(SW_SHOW);
		
	} 
	else
	{	
		m_paintToolBar.ShowWindow(SW_HIDE);
	}
	paintbar= !paintbar;
	DockControlBar(&m_paintToolBar);
}

void CMainFrame::OnUpdateDrawbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(paintbar);
}

void CMainFrame::OnColorbar() 
{
	// TODO: Add your command handler code here
	if (!colorbar)
	{
		m_colorBar->ShowWindow(SW_SHOW);
		
	} 
	else
	{	
		m_colorBar->ShowWindow(SW_HIDE);
	}
	colorbar= !colorbar;
	DockControlBar(m_colorBar);
}

void CMainFrame::OnUpdateColorbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(colorbar);
}

void CMainFrame::OnToolbarDropDown(NMTOOLBAR *pnmtb, LRESULT *plr)
{
	CWnd *pWnd; 
	UINT nID;       
    switch(pnmtb->iItem)   
	{           
	case IDR_SETLINE_W: 
		//ID_DRAW_LINE即是你要添加下拉菜单的ToolBar按钮的ID  
		pWnd = &m_wndToolBar;  
		nID = IDR_MENU1;//IDR_POPUP_LINE就是上面新制作的菜单ID，当然，如果你要添加多个下拉菜单，只要多加几个case就好了   
		break;   
	case IDR_SETLINE_S: 
		//ID_DRAW_LINE即是你要添加下拉菜单的ToolBar按钮的ID  
		pWnd = &m_wndToolBar;  
		nID = IDR_MENU2;//IDR_POPUP_LINE就是上面新制作的菜单ID，当然，如果你要添加多个下拉菜单，只要多加几个case就好了   
		break; 
// 	case ID_LINE_H: 
// 		//ID_DRAW_LINE即是你要添加下拉菜单的ToolBar按钮的ID  
// 		pWnd = &m_lineBar;  
// 		nID = IDR_MENU1;//IDR_POPUP_LINE就是上面新制作的菜单ID，当然，如果你要添加多个下拉菜单，只要多加几个case就好了   
// 		break; 
	default:          
		return; 
		}
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu*pPopup=menu.GetSubMenu(0);
	ASSERT(pPopup);
	CRect rc;
	pWnd->SendMessage(TB_GETRECT,pnmtb->iItem,(LPARAM)&rc);
	pWnd->ClientToScreen(&rc);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,rc.left,rc.bottom,this,&rc);
	
}

void CMainFrame::OnViewToolbar() 
{
	// TODO: Add your command handler code here
	if (!wndBar)
	{
		m_wndToolBar.ShowWindow(SW_SHOW);
		
	} 
	else
	{	
		m_wndToolBar.ShowWindow(SW_HIDE);
	}
	wndBar= !wndBar;
	DockControlBar(&m_transBar);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(wndBar);
}

void CMainFrame::OnGeomtransbar() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if (!transbar)
	{
		m_transBar.ShowWindow(SW_SHOW);
		
	} 
	else
	{	
		m_transBar.ShowWindow(SW_HIDE);
	}
	transbar= !transbar;
	DockControlBar(&m_transBar);
}

void CMainFrame::OnUpdateGeomtransbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(transbar);
}

void CMainFrame::OnUpdateSetlineW(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateSetlineS(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
