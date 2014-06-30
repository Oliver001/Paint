// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__9325FC1F_E8A5_4973_85C8_B75775562D84__INCLUDED_)
#define AFX_MAINFRM_H__9325FC1F_E8A5_4973_85C8_B75775562D84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_paintToolBar;	
	CToolBar	m_FilterToolBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFontbar();
	afx_msg void OnUpdateFontbar(CCmdUI* pCmdUI);
	afx_msg void OnFilterbar();
	afx_msg void OnUpdateFilterbar(CCmdUI* pCmdUI);
	afx_msg void OnDrawbar();
	afx_msg void OnUpdateDrawbar(CCmdUI* pCmdUI);
	afx_msg void OnColorbar();
	afx_msg void OnUpdateColorbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9325FC1F_E8A5_4973_85C8_B75775562D84__INCLUDED_)
