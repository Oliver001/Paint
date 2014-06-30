// MyTracker.h: interface for the CMyTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTRACKER_H__8D172DF3_64D3_4559_A737_84A02371B1A3__INCLUDED_)
#define AFX_MYTRACKER_H__8D172DF3_64D3_4559_A737_84A02371B1A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTracker : public CRectTracker  
{
public:
	void GetHandleRect(int nHandle, CRect* pHandleRect) const;
	CMyTracker();
	virtual ~CMyTracker();
	void Draw(CDC *pDC,UINT type=1,COLORREF clr=RGB(0,0,0),UINT m=0xff);
};

#endif // !defined(AFX_MYTRACKER_H__8D172DF3_64D3_4559_A737_84A02371B1A3__INCLUDED_)
