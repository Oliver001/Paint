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
	bool m_bNet;

    BITMAPINFO struct_bitmapInfo;
	BITMAPINFOHEADER  bitmap_Info;
	BOOL OpenTifDocumen(void);
	DWORD m_dwBmSize;//图象的数据部分的大小
	CPalette m_palDIB;//BMP图象调色板
	HANDLE m_hDIB;//BMP图象内存块句柄
	CSize m_sizeDoc;//图象的长和宽 
	BOOL CreateBmpBuffer(void);

	bool m_bNotEmpty;
	void BackUp();
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
	CDC* tempDC;
	CRect tempRect;
	stack <CDC*> m_stack;
	CString BmpName;//保存图像文件文件名
	CString extname;//保存图像文件扩展名

	CBitmap bitmap;
	CShape* m_shape;

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
	afx_msg void OnCopy();
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnLefttranslation();
	afx_msg void OnDowntranslation();
	afx_msg void OnUptranslation();
	afx_msg void OnRighttranslation();
	afx_msg void OnUpmirroring();
	afx_msg void OnLrmirroring();
	afx_msg void OnRightspin();
	afx_msg void OnLeftspin();
	afx_msg void OnOamirroring();
	afx_msg void OnUpdateLefttranslation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLeftspin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLrmirroring(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOamirroring(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRightspin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRighttranslation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSmallzoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUpmirroring(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUptranslation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDowntranslation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBigzoom(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnPixel2();
	afx_msg void OnPixel5();
	afx_msg void OnPixel10();
	afx_msg void OnPixel15();
	afx_msg void OnPixel20();
	afx_msg void OnSolid();
	afx_msg void OnDash();
	afx_msg void OnDot();
	afx_msg void OnPixel1();
	afx_msg void OnUpdateSolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDash(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDot(CCmdUI* pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnNet();
	afx_msg void OnUpdateNet(CCmdUI* pCmdUI);
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
