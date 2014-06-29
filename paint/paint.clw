; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPaintDoc
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

ResourceCount=5
Resource1=IDR_GEOMTRANSBAR
Class5=CAboutDlg
Class6=CMyPaintView
Resource2=IDR_DRAWBAR
Resource3=IDR_FILTERBAR
Resource4=IDR_MAINFRAME
Resource5=IDD_ABOUTBOX

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


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_LINE
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
Command9=IDM_MAINBAR
Command10=IDM_FONTBAR
Command11=IDM_GEOMTRANSBAR
Command12=IDM_FILTERBAR
Command13=IDM_DRAWBAR
Command14=IDM_COLORBAR
Command15=IDM_LINE
Command16=IDM_CIRCLE
Command17=IDM_TRIANGLE
Command18=IDM_RECTANGLE
Command19=IDM_FIVEANGLE
Command20=IDM_TRANSLATION
Command21=IDM_SPIN
Command22=IDM_ZOOM
Command23=IDM_MIRRORING
Command24=IDM_BACKWARD
Command25=IDM_SLEEK
Command26=IDM_NEONRED
Command27=IDM_SHARPEN
Command28=IDM_RELIEF
Command29=IDM_INLAY
Command30=IDM_EXPOSURE
Command31=IDM_DIFFUSE
Command32=IDM_HELP
Command33=ID_APP_ABOUT
CommandCount=33

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
Command1=ID_SELECTSHAPE
Command2=ID_DRAWLINE
Command3=ID_DRAWCIRCLE
Command4=ID_DRAWTRIANGLE
Command5=ID_DRAWRECTANGLE
Command6=ID_DRAWFIVEANGLE
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
Command11=ID_BUTTON32824
CommandCount=11

[TB:IDR_FILTERBAR]
Type=1
Class=?
Command1=ID_BACKWARD
Command2=ID_BUTTON32816
Command3=ID_BUTTON32818
Command4=ID_BUTTON32819
Command5=ID_BUTTON32820
Command6=ID_BUTTON32821
Command7=ID_BUTTON32822
Command8=ID_BUTTON32823
CommandCount=8

[CLS:CMyPaintView]
Type=0
HeaderFile=MyPaintView.h
ImplementationFile=MyPaintView.cpp
BaseClass=CScrollView
Filter=C
LastObject=ID_SELECTSHAPE
VirtualFilter=VWC

