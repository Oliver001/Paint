// paintView.h : interface of the CPaintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTVIEW_H__9FD8D918_C7C2_452C_BACD_E94D340DF978__INCLUDED_)
#define AFX_PAINTVIEW_H__9FD8D918_C7C2_452C_BACD_E94D340DF978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
using namespace std;
#include "paintDoc.h"
#include "Shape.h"	// Added by ClassView
#include "Filter.h"

class CPaintView : public CView
{
public: // create from serialization only
	CPaintView();
	DECLARE_DYNCREATE(CPaintView)

// Attributes
public:
	CPaintDoc* GetDocument();
	void SetDocument(CPaintDoc *pDoc);
	CDocument *pOldDoc;
	CBitmap bitmap;
	CFilter fil;
	BITMAP bmp;
    int x,y;
	stack <CDC*> m_stack;
// Operations
public:
	CDC* MyDC;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CShape* m_shape;
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaintView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBackward();
	afx_msg void OnExposure();
	afx_msg void OnNeonred();
	afx_msg void OnRelief();
	afx_msg void OnSharpen();
	afx_msg void OnSleek();
	afx_msg void OnInlay();
	afx_msg void OnDiffuse();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in paintView.cpp
inline CPaintDoc* CPaintView::GetDocument()
   { return (CPaintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTVIEW_H__9FD8D918_C7C2_452C_BACD_E94D340DF978__INCLUDED_)
