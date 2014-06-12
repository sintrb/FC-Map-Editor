#if !defined(AFX_SAVENAMEDLG_H__0F5C5F02_3DCA_444F_B107_6DBC1AAAF167__INCLUDED_)
#define AFX_SAVENAMEDLG_H__0F5C5F02_3DCA_444F_B107_6DBC1AAAF167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveNameDlg dialog

class CSaveNameDlg : public CDialog
{
// Construction
public:
	void SetName(CString atb, CString chr, CString col, CString nam);
	CSaveNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveNameDlg)
	enum { IDD = IDD_DIALOG_SAVENAME };
	CString	m_sAtb;
	CString	m_sChr;
	CString	m_sCol;
	CString	m_sNam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVENAMEDLG_H__0F5C5F02_3DCA_444F_B107_6DBC1AAAF167__INCLUDED_)
