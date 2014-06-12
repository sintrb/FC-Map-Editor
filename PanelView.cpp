// PanelView.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "PanelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelView

IMPLEMENT_DYNCREATE(CPanelView, CView)

CPanelView::CPanelView()
{
	this->m_panel = NULL;
}

CPanelView::~CPanelView()
{
}


BEGIN_MESSAGE_MAP(CPanelView, CView)
	//{{AFX_MSG_MAP(CPanelView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelView drawing

void CPanelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPanelView diagnostics

#ifdef _DEBUG
void CPanelView::AssertValid() const
{
	CView::AssertValid();
}

void CPanelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanelView message handlers

void CPanelView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	this->m_panel = new CPanelDlg();
	this->m_panel->Create(IDD_DIALOG_PANEL, this);
	this->m_panel->ShowWindow(SW_SHOW);
}

void CPanelView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(this->m_panel)this->m_panel->MoveWindow(0, 0, cx, cy);
}

void CPanelView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	if(this->m_panel)delete this->m_panel;
}

BOOL CPanelView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//return TRUE;
	return CView::OnEraseBkgnd(pDC);
}
