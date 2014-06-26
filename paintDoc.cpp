// paintDoc.cpp : implementation of the CPaintDoc class
//

#include "stdafx.h"
#include "paint.h"

#include "paintDoc.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
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

CPaintDoc::CPaintDoc():
m_cavasH(300),
m_cavasW(600)
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CPaintDoc::~CPaintDoc()
{
	AfxOleUnlockApp();
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
