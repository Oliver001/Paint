; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPaintDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "paint.h"
ODLFile=paint.odl
LastPage=0

ClassCount=7
Class1=CPaintApp
Class2=CPaintDoc
Class3=CPaintView
Class4=CMainFrame

ResourceCount=9
Resource1=IDR_FILTERBAR
Class5=CAboutDlg
Class6=CMyPaintView
Resource2=IDR_COLORBAR
Resource3=IDR_MENU1
Resource4=IDR_MENU2
Resource5=IDD_ABOUTBOX
Resource6=IDR_DRAWBAR
Resource7=IDR_GEOMTRANSBAR
Resource8=IDR_MAINFRAME
Class7=CTextDlg
Resource9=IDD_DIALOG1

[CLS:CPaintApp]
Type=0
HeaderFile=paint.h
ImplementationFile=paint.cpp
Filter=N

[CLS:CPaintDoc]
Type=0
HeaderFile=paintDoc.h
ImplementationFile=paintDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPaintDoc

[CLS:CPaintView]
Type=0
HeaderFile=paintView.h
ImplementationFile=paintView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPaintView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_NET
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=paint.cpp
ImplementationFile=paint.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILEOPEN
Command3=ID_FILE_SAVE
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_CUT
Command7=ID_COPY
Command8=ID_PASTE
Command9=ID_VIEW_TOOLBAR
Command10=IDM_GEOMTRANSBAR
Command11=IDM_FILTERBAR
Command12=IDM_DRAWBAR
Command13=IDM_COLORBAR
Command14=ID_NET
Command15=IDM_SELECTSHAPE
Command16=IDM_LINE
Command17=IDM_CIRCLE
Command18=IDM_TRIANGLE
Command19=IDM_RECTANGLE
Command20=IDM_FIVEANGLE
Command21=IDR_TEXT
Command22=ID_LEFTTRANSLATION
Command23=ID_UPTRANSLATION
Command24=ID_DOWNTRANSLATION
Command25=ID_RIGHTTRANSLATION
Command26=ID_RIGHTSPIN
Command27=ID_LEFTSPIN
Command28=ID_UPMIRRORING
Command29=ID_LRMIRRORING
Command30=ID_OAMIRRORING
Command31=IDM_BACKWARD
Command32=IDM_SLEEK
Command33=IDM_NEONRED
Command34=IDM_SHARPEN
Command35=IDM_RELIEF
Command36=IDM_INLAY
Command37=IDM_EXPOSURE
Command38=IDM_DIFFUSE
Command39=IDM_GREY
Command40=IDM_HELP
Command41=ID_APP_ABOUT
CommandCount=41

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_EXIT
Command8=IDR_SETLINE_W
Command9=IDR_SETLINE_S
CommandCount=9

[TB:IDR_DRAWBAR]
Type=1
Class=CPaintDoc
Command1=IDM_SELECTSHAPE
Command2=IDM_LINE
Command3=IDM_CIRCLE
Command4=IDM_TRIANGLE
Command5=IDM_RECTANGLE
Command6=IDM_FIVEANGLE
Command7=IDR_TEXT
CommandCount=7

[TB:IDR_GEOMTRANSBAR]
Type=1
Class=?
Command1=ID_LEFTTRANSLATION
Command2=ID_UPTRANSLATION
Command3=ID_DOWNTRANSLATION
Command4=ID_RIGHTTRANSLATION
Command5=ID_RIGHTSPIN
Command6=ID_LEFTSPIN
Command7=ID_UPMIRRORING
Command8=ID_LRMIRRORING
Command9=ID_OAMIRRORING
CommandCount=9

[TB:IDR_FILTERBAR]
Type=1
Class=?
Command1=IDM_BACKWARD
Command2=IDM_SLEEK
Command3=IDM_NEONRED
Command4=IDM_SHARPEN
Command5=IDM_RELIEF
Command6=IDM_INLAY
Command7=IDM_EXPOSURE
Command8=IDM_DIFFUSE
Command9=IDM_GREY
CommandCount=9

[CLS:CMyPaintView]
Type=0
HeaderFile=MyPaintView.h
ImplementationFile=MyPaintView.cpp
BaseClass=CScrollView
Filter=C
LastObject=ID_SELECTSHAPE
VirtualFilter=VWC

[TB:IDR_COLORBAR]
Type=1
Class=?
Command1=ID_COLORBAR
CommandCount=1

[MNU:IDR_MENU1]
Type=1
Class=CMainFrame
Command1=ID_PIXEL1
Command2=ID_PIXEL2
Command3=ID_Pixel5
Command4=ID_PIXEL10
Command5=ID_PIXEL15
Command6=ID_PIXEL20
CommandCount=6

[MNU:IDR_MENU2]
Type=1
Class=CMainFrame
Command1=ID_SOLID
Command2=ID_DASH
Command3=ID_DOT
CommandCount=3

[DLG:IDD_DIALOG1]
Type=1
Class=CTextDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CTextDlg]
Type=0
HeaderFile=TextDlg.h
ImplementationFile=TextDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TEXT

