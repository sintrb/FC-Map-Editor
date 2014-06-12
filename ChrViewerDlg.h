#if !defined(AFX_CHRVIEWERDLG_H__1F8E3EA9_EF96_4F41_A0CA_7617C129B118__INCLUDED_)
#define AFX_CHRVIEWERDLG_H__1F8E3EA9_EF96_4F41_A0CA_7617C129B118__INCLUDED_

#include "NESViewChr.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChrViewerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChrViewerDlg dialog

class CChrViewerDlg : public CDialog
{
// Construction
public:
	void SelectChr(int n);
	int m_chrCount;
	unsigned char* m_datbuf;
//	CBitmap m_bmp;
	int m_SelChr;
	void SetChrFile(CString fn);
	CNESViewChr m_chr;
	CString m_chrfilename;
	CChrViewerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChrViewerDlg)
	enum { IDD = IDD_DIALOG_VIERCHR };
	CStatic	m_sBmp;
	CComboBox	m_cbChrSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChrViewerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChrViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChrsel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHRVIEWERDLG_H__1F8E3EA9_EF96_4F41_A0CA_7617C129B118__INCLUDED_)
