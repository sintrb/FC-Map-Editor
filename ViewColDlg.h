#if !defined(AFX_VIEWCOLDLG_H__B6D96248_F4B0_4990_BFCE_2DBCA247F41F__INCLUDED_)
#define AFX_VIEWCOLDLG_H__B6D96248_F4B0_4990_BFCE_2DBCA247F41F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewColDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewColDlg dialog

class CViewColDlg : public CDialog
{
// Construction
public:
	unsigned char* buf;
	CString filename;
	void SetFilename(CString fn);
	unsigned char col[16];
	CViewColDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewColDlg)
	enum { IDD = IDD_DIALOG_COLOR };
	CComboBox	m_cbIndex;
	CStatic	m_bmpCol;
	int		m_iSeltPal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewColDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewColDlg)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCOLDLG_H__B6D96248_F4B0_4990_BFCE_2DBCA247F41F__INCLUDED_)
