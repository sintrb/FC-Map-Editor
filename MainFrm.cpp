// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "MainFrm.h"
#include "FCµØÍ¼±à¼­Æ÷Doc.h"
#include "FCµØÍ¼±à¼­Æ÷View.h"
#include "PanelView.h"
//#include "PanelDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESH, OnUpdateViewRefresh)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
	ID_INDICATOR_ABS,
	ID_INDICATOR_CELL,
	ID_INDICATOR_SEL,
	ID_INDICATOR_SIZE,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	/*
	CPanelDlg* dlg = new CPanelDlg();
	dlg->Create(IDD_DIALOG_PANEL, this);
	dlg->ShowWindow(SW_NORMAL);
*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	if(m_splitter.CreateStatic(this,1,2,WS_CHILD|WS_VISIBLE)==NULL)return FALSE;
	m_splitter.CreateView(0,1,RUNTIME_CLASS(CPanelView),CSize(300,600), pContext);
	m_splitter.CreateView(0,0,RUNTIME_CLASS(CFCView),CSize(600,600), pContext);
	return TRUE;
}


void CMainFrame::OnUpdateViewRefresh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnViewRefresh() 
{
	// TODO: Add your command handler code here
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p->GetActiveDocument()->UpdateAllViews(NULL);
}

void CMainFrame::SetListen()
{
	this->SetTimer(1, 500, NULL);
}

void CMainFrame::KillListen()
{
	this->KillTimer(1);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1){
		((CFCDoc*)this->GetActiveDocument())->CheckFileTime();
	}
	CFrameWnd::OnTimer(nIDEvent);
}
