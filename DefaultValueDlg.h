#if !defined(AFX_DEFAULTVALUEDLG_H__F3381B8C_09BF_4DDB_B8F4_AA123C47F854__INCLUDED_)
#define AFX_DEFAULTVALUEDLG_H__F3381B8C_09BF_4DDB_B8F4_AA123C47F854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefaultValueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDefaultValueDlg dialog

class CDefaultValueDlg : public CDialog
{
// Construction
public:
	int m_iValue;
	
	CDefaultValueDlg(CWnd* pParent = NULL);   // standard constructor
	void SetDValue(int dv);
// Dialog Data
	//{{AFX_DATA(CDefaultValueDlg)
	enum { IDD = IDD_DIALOG_DEFAULTVALUE };
	CComboBox	m_cbDValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefaultValueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefaultValueDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDvalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFAULTVALUEDLG_H__F3381B8C_09BF_4DDB_B8F4_AA123C47F854__INCLUDED_)
