#if !defined(AFX_MYPAINTVIEW_H__BA3C902C_BADD_4B3C_83C2_F5DB6664F651__INCLUDED_)
#define AFX_MYPAINTVIEW_H__BA3C902C_BADD_4B3C_83C2_F5DB6664F651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPaintView.h : header file
//
#include "paintView.h"
#include <afxext.h>
/////////////////////////////////////////////////////////////////////////////
// CMyPaintView view

class CMyPaintView : public CScrollView
{
protected:
	CMyPaintView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyPaintView)

	
// Attributes
public:

protected:
	CPaintView* m_paintView;
	CRectTracker m_rectTracker;
// Operations
public:
	CPaintDoc* GetDocument();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaintView)
	public:
//	virtual void OnFinalRelease();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyPaintView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMyPaintView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAINTVIEW_H__BA3C902C_BADD_4B3C_83C2_F5DB6664F651__INCLUDED_)
