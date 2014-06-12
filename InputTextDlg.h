#if !defined(AFX_INPUTTEXTDLG_H__6AB0BB0F_55EE_4778_81AA_DB6F4F8A7840__INCLUDED_)
#define AFX_INPUTTEXTDLG_H__6AB0BB0F_55EE_4778_81AA_DB6F4F8A7840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputTextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputTextDlg dialog

class CInputTextDlg : public CDialog
{
// Construction
public:
	CInputTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputTextDlg)
	enum { IDD = IDD_DIALOG_INPUTTEXT };
	int		m_iOffset;
	CString	m_sText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputTextDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTTEXTDLG_H__6AB0BB0F_55EE_4778_81AA_DB6F4F8A7840__INCLUDED_)
