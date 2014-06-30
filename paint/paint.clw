; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPaintView
LastTemplate=CScrollView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "paint.h"
ODLFile=paint.odl
LastPage=0

ClassCount=6
Class1=CPaintApp
Class2=CPaintDoc
Class3=CPaintView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_COLORBAR
Class5=CAboutDlg
Class6=CMyPaintView
Resource2=IDR_FILTERBAR
Resource3=IDR_DRAWBAR
Resource4=IDR_GEOMTRANSBAR
Resource5=IDD_ABOUTBOX
Resource6=IDR_MAINFRAME

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
LastObject=IDM_DIFFUSE
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
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_VIEW_TOOLBAR
Command10=IDM_FONTBAR
Command11=IDM_GEOMTRANSBAR
Command12=IDM_FILTERBAR
Command13=IDM_DRAWBAR
Command14=IDM_COLORBAR
Command15=IDM_SELECTSHAPE
Command16=IDM_LINE
Command17=IDM_CIRCLE
Command18=IDM_TRIANGLE
Command19=IDM_RECTANGLE
Command20=IDM_FIVEANGLE
Command21=ID_LEFTTRANSLATION
Command22=ID_UPTRANSLATION
Command23=ID_DOWNTRANSLATION
Command24=ID_RIGHTTRANSLATION
Command25=ID_RIGHTSPIN
Command26=ID_LEFTSPIN
Command27=ID_BIGZOOM
Command28=ID_SMALLZOOM
Command29=ID_UPMIRRORING
Command30=ID_LRMIRRORING
Command31=ID_OAMIRRORING
Command32=IDM_BACKWARD
Command33=IDM_SLEEK
Command34=IDM_NEONRED
Command35=IDM_SHARPEN
Command36=IDM_RELIEF
Command37=IDM_INLAY
Command38=IDM_EXPOSURE
Command39=IDM_DIFFUSE
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
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_EXIT
CommandCount=7

[TB:IDR_DRAWBAR]
Type=1
Class=CPaintDoc
Command1=IDM_SELECTSHAPE
Command2=IDM_LINE
Command3=IDM_CIRCLE
Command4=IDM_TRIANGLE
Command5=IDM_RECTANGLE
Command6=IDM_FIVEANGLE
CommandCount=6

[TB:IDR_GEOMTRANSBAR]
Type=1
Class=?
Command1=ID_LEFTTRANSLATION
Command2=ID_UPTRANSLATION
Command3=ID_DOWNTRANSLATION
Command4=ID_RIGHTTRANSLATION
Command5=ID_RIGHTSPIN
Command6=ID_LEFTSPIN
Command7=ID_BIGZOOM
Command8=ID_SMALLZOOM
Command9=ID_UPMIRRORING
Command10=ID_LRMIRRORING
Command11=ID_OAMIRRORING
CommandCount=11

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
CommandCount=8

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

