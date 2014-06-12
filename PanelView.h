#if !defined(AFX_PANELVIEW_H__9A493CEF_F5B7_42C4_B48B_103993F89D50__INCLUDED_)
#define AFX_PANELVIEW_H__9A493CEF_F5B7_42C4_B48B_103993F89D50__INCLUDED_

#include "PanelDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PanelView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanelView view

class CPanelView : public CView
{
protected:
	CPanelView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPanelView)

// Attributes
public:

// Operations
public:
	CPanelDlg *m_panel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPanelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPanelView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANELVIEW_H__9A493CEF_F5B7_42C4_B48B_103993F89D50__INCLUDED_)
