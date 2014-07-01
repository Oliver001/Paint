// paintDoc.h : interface of the CPaintDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTDOC_H__941F44C9_2BF0_44DF_B917_EC7A2BB77D28__INCLUDED_)
#define AFX_PAINTDOC_H__941F44C9_2BF0_44DF_B917_EC7A2BB77D28__INCLUDED_

#include "Shape.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Filter.h"
#include <stack>
using namespace std;
class CPaintDoc : public CDocument
{
protected: // create from serialization only
	CPaintDoc();
	DECLARE_DYNCREATE(CPaintDoc)

public:
	bool Reset(int w,int h);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	CShape* NewShape();
	DrawType m_DrawType;
	COLORREF clr;
	int m_nLineStyle;
	int m_nLineWidth;
	UINT m_cavasH;
	UINT m_cavasW;
	virtual ~CPaintDoc();
	CDC* MyDC;
	stack <CDC*> m_stack;
	CBitmap bitmap;
	
	CString BmpName;//保存图像文件文件名
	CString extname;//保存图像文件扩展名
	//CBitmap m_bitmap;//创建位图对象
	bool ShowBitmap(CString BmpName);//用来显示指定位图的函数
	bool ShowJpgGif(CDC* pDC,CString strPath, int x, int y);
	bool ShowJpgGif(void);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// Generated message map functions
protected:
	//{{AFX_MSG(CPaintDoc)
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnTriangle();
	afx_msg void OnFiveangle();
	afx_msg void OnCircle();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTriangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFiveangle(CCmdUI* pCmdUI);
	afx_msg void OnSelectshape();
	afx_msg void OnUpdateSelectshape(CCmdUI* pCmdUI);
	afx_msg void OnFill();
	afx_msg void OnUpdateFill(CCmdUI* pCmdUI);
	afx_msg void OnFileopen();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPaintDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTDOC_H__941F44C9_2BF0_44DF_B917_EC7A2BB77D28__INCLUDED_)
