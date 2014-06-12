// FCµØÍ¼±à¼­Æ÷View.h : interface of the CFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FCVIEW_H__22941ED0_7A12_4F2A_A1B2_D12DED9AA88B__INCLUDED_)
#define AFX_FCVIEW_H__22941ED0_7A12_4F2A_A1B2_D12DED9AA88B__INCLUDED_

#include "ClipboardData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFCView : public CScrollView
{
protected: // create from serialization only
	CFCView();
	DECLARE_DYNCREATE(CFCView)

// Attributes
public:
	CFCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bMapLock;
	void SetModifiedFlag(BOOL flag = TRUE);
	BOOL m_conDraw;
	BOOL m_bHaveClipData;
	void PasteTo();
	void SetChr(int x, int y);
//	CBitmap m_bmpChr;	//Tile¼¯16*16µÄ
	void RefreshStatusBar(int iX=0, int iY=0);
	CPoint m_ptMouseDown;
	CPoint m_ptOldMousPoint;
	void SaveMapAttribute();
	int m_iDefaultValue;
	void LoadMapAttribute();

	void ReSetScroll();
	int m_iMapH;
	int m_iMapW;
	int m_iCellH;
	int m_iCellW;

	int m_iTileH;
	int m_iTileW;

	BOOL m_bSelect;
	BOOL m_bMouseDown;
	BOOL m_bGrid;

	int m_iSaveStyle;
	CRect m_rcSelect;
	virtual ~CFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFCView)
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnSetDefaultvalue();
	afx_msg void OnUpdateAllEnable(CCmdUI* pCmdUI);
	afx_msg void OnSetMapattribute();
	afx_msg void OnSetSavestyle();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditAll();
	afx_msg void OnUpdateIsSelected(CCmdUI* pCmdUI);
	afx_msg void OnEditText();
	afx_msg void OnImportChr();
	afx_msg void OnImportMap();
	afx_msg void OnImportCol();
	afx_msg void OnImportAttribute();
	afx_msg void OnEditDelete();
	afx_msg void OnEditFill();
	afx_msg void OnUpdateEditTm(CCmdUI* pCmdUI);
	afx_msg void OnEditTm();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnDrawClipboard();
	afx_msg void OnViewRefresh();
	afx_msg void OnUpdateEditLock(CCmdUI* pCmdUI);
	afx_msg void OnEditLock();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FCµØÍ¼±à¼­Æ÷View.cpp
inline CFCDoc* CFCView::GetDocument()
   { return (CFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FCVIEW_H__22941ED0_7A12_4F2A_A1B2_D12DED9AA88B__INCLUDED_)
