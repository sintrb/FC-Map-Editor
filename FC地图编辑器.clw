; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFCView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FCµØÍ¼±à¼­Æ÷.h"
LastPage=0

ClassCount=14
Class1=CFCApp
Class2=CFCDoc
Class3=CFCView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_DIALOG_MAPATTRIBUTE
Class5=CAboutDlg
Resource2=IDD_DIALOG_SAVESTYLE
Class6=CDefaultValueDlg
Resource3=IDR_MAINFRAME
Class7=CMapAttributeDlg
Resource4=IDD_DIALOG_DEFAULTVALUE
Class8=CInputTextDlg
Resource5=IDD_DIALOG_VIERCHR
Class9=CSaveStyleDlg
Resource6=IDD_DIALOG_SAVENAME
Class10=CSaveNameDlg
Resource7=IDD_DIALOG_PANEL
Class11=CChrViewerDlg
Class12=CPanelView
Resource8=IDD_ABOUTBOX
Class13=CPanelDlg
Resource9=IDD_DIALOG_INPUTTEXT
Class14=CViewColDlg
Resource10=IDD_DIALOG_COLOR

[CLS:CFCApp]
Type=0
HeaderFile=FCµØÍ¼±à¼­Æ÷.h
ImplementationFile=FCµØÍ¼±à¼­Æ÷.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CFCApp

[CLS:CFCDoc]
Type=0
HeaderFile=FCµØÍ¼±à¼­Æ÷Doc.h
ImplementationFile=FCµØÍ¼±à¼­Æ÷Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CFCDoc

[CLS:CFCView]
Type=0
HeaderFile=FCµØÍ¼±à¼­Æ÷View.h
ImplementationFile=FCµØÍ¼±à¼­Æ÷View.cpp
Filter=W
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_FILE_OPEN


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_IMPORT_CHR




[CLS:CAboutDlg]
Type=0
HeaderFile=FCµØÍ¼±à¼­Æ÷.cpp
ImplementationFile=FCµØÍ¼±à¼­Æ÷.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_ALL
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_FILL
Command16=ID_EDIT_DELETE
Command17=ID_EDIT_TEXT
Command18=ID_EDIT_TM
Command19=ID_EDIT_LOCK
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_VIEW_GRID
Command23=ID_VIEW_REFRESH
Command24=ID_VIEW_RELOAD
Command25=ID_SET_DEFAULTVALUE
Command26=ID_SET_MAPATTRIBUTE
Command27=ID_SET_SAVESTYLE
Command28=ID_SET_LISTEN
Command29=ID_IMPORT_CHR
Command30=ID_IMPORT_COL
Command31=ID_IMPORT_MAP
Command32=ID_IMPORT_ATTRIBUTE
Command33=ID_APP_ABOUT
CommandCount=33

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_ALL
Command2=ID_EDIT_COPY
Command3=ID_EDIT_DELETE
Command4=ID_EDIT_FILL
Command5=ID_EDIT_LOCK
Command6=ID_FILE_NEW
Command7=ID_FILE_OPEN
Command8=ID_FILE_PRINT
Command9=ID_FILE_SAVE
Command10=ID_EDIT_TEXT
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_DELETE
Command14=ID_EDIT_CUT
Command15=ID_VIEW_RELOAD
Command16=ID_VIEW_REFRESH
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
Command19=ID_EDIT_COPY
Command20=ID_EDIT_PASTE
Command21=ID_EDIT_CUT
Command22=ID_EDIT_UNDO
CommandCount=22

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_TEXT
Command5=ID_EDIT_DELETE
Command6=ID_EDIT_FILL
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_VIEW_GRID
Command11=ID_EDIT_LOCK
Command12=ID_VIEW_REFRESH
Command13=ID_VIEW_RELOAD
Command14=ID_FILE_PRINT
Command15=ID_APP_ABOUT
CommandCount=15

[DLG:IDD_DIALOG_DEFAULTVALUE]
Type=1
Class=CDefaultValueDlg
ControlCount=3
Control1=IDC_COMBO_DVALUE,combobox,1344340227
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308352

[CLS:CDefaultValueDlg]
Type=0
HeaderFile=DefaultValueDlg.h
ImplementationFile=DefaultValueDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDefaultValueDlg
VirtualFilter=dWC

[CLS:CMapAttributeDlg]
Type=0
HeaderFile=MapAttributeDlg.h
ImplementationFile=MapAttributeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMapAttributeDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_MAPATTRIBUTE]
Type=1
Class=CMapAttributeDlg
ControlCount=12
Control1=IDC_EDIT_CELLWIDTH,edit,1350639744
Control2=IDC_EDIT_CELLHEIGHT,edit,1350639744
Control3=IDC_EDIT_WIDTH,edit,1350639744
Control4=IDC_EDIT_HEIGHT,edit,1350639744
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287

[CLS:CInputTextDlg]
Type=0
HeaderFile=InputTextDlg.h
ImplementationFile=InputTextDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_OFFSET
VirtualFilter=dWC

[DLG:IDD_DIALOG_INPUTTEXT]
Type=1
Class=CInputTextDlg
ControlCount=6
Control1=IDC_EDIT_TEXT,edit,1352732676
Control2=IDC_EDIT_OFFSET,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_SAVESTYLE]
Type=1
Class=CSaveStyleDlg
ControlCount=9
Control1=IDC_RADIO_CELL,button,1342308361
Control2=IDC_RADIO_ALL,button,1342177289
Control3=IDC_RADIO_V,button,1342308361
Control4=IDC_RADIO_H,button,1342177289
Control5=IDOK,button,1342373889
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC_PIC,static,1342177294

[CLS:CSaveStyleDlg]
Type=0
HeaderFile=SaveStyleDlg.h
ImplementationFile=SaveStyleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSaveStyleDlg
VirtualFilter=dWC

[CLS:CSaveNameDlg]
Type=0
HeaderFile=SaveNameDlg.h
ImplementationFile=SaveNameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSaveNameDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_SAVENAME]
Type=1
Class=CSaveNameDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_CHR,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_COL,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_NAM,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_ATB,edit,1350631552

[DLG:IDD_DIALOG_VIERCHR]
Type=1
Class=CChrViewerDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO_CHRSEL,combobox,1344339971
Control4=IDC_STATIC_BMP,static,1342177294
Control5=IDC_STATIC,static,1342308352

[CLS:CChrViewerDlg]
Type=0
HeaderFile=ChrViewerDlg.h
ImplementationFile=ChrViewerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CChrViewerDlg
VirtualFilter=dWC

[CLS:CPanelView]
Type=0
HeaderFile=PanelView.h
ImplementationFile=PanelView.cpp
BaseClass=CView
Filter=C
LastObject=CPanelView
VirtualFilter=VWC

[DLG:IDD_DIALOG_PANEL]
Type=1
Class=CPanelDlg
ControlCount=23
Control1=IDC_RADIO_SIN,button,1342308361
Control2=IDC_RADIO_REC,button,1342177289
Control3=IDC_RADIO_REC_V,button,1342177289
Control4=IDC_RADIO_REC_H,button,1342177289
Control5=IDC_RADIO_COLOR,button,1342177289
Control6=IDC_RADIO_SEL,button,1342177289
Control7=IDC_COMBO_DIY,combobox,1344405507
Control8=IDC_BUTTON_DIY_NEW,button,1073807360
Control9=IDC_BUTTON_DIY_DEL,button,1073807360
Control10=IDC_STATIC_SEL_FRAME,button,1342177287
Control11=IDC_STATIC_BMP,static,1342177294
Control12=IDC_STATIC_GROUP_FRAME,button,1342177287
Control13=IDC_STATIC_DIY_BMP,static,1342177294
Control14=IDC_STATIC_FRAM_COL,button,1342177287
Control15=IDC_STATIC_BMPCOL,static,1342177294
Control16=IDC_STATIC_STDCOL_BMP,static,1342177294
Control17=IDC_CHECK_CLOCKPAL,button,1342242819
Control18=IDC_CHECK_LOCKDIY,button,1342242819
Control19=IDC_BUTTON_FILL,button,1342242816
Control20=IDC_EDIT_DIY_W,edit,1350639744
Control21=IDC_EDIT_DIY_H,edit,1350639744
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC_INF,static,1342181376

[CLS:CPanelDlg]
Type=0
HeaderFile=PanelDlg.h
ImplementationFile=PanelDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_STATIC_INF
VirtualFilter=dWC

[DLG:IDD_DIALOG_COLOR]
Type=1
Class=CViewColDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_COL,static,1342177294
Control4=IDC_COMBO_INDEX,combobox,1344339971

[CLS:CViewColDlg]
Type=0
HeaderFile=ViewColDlg.h
ImplementationFile=ViewColDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_INDEX
VirtualFilter=dWC

