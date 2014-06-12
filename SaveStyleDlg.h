#if !defined(AFX_SAVESTYLEDLG_H__A259D049_3078_48AF_861D_9646D6BA8C8D__INCLUDED_)
#define AFX_SAVESTYLEDLG_H__A259D049_3078_48AF_861D_9646D6BA8C8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveStyleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveStyleDlg dialog

class CSaveStyleDlg : public CDialog
{
// Construction
public:
	CBitmap bmpAV;
	CBitmap bmpAH;
	CBitmap bmpCV;
	CBitmap bmpCH;
	void RefreshUI();
	int m_iStyle;
	int GetStyle();
	void SetStyle(int st);
	CSaveStyleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveStyleDlg)
	enum { IDD = IDD_DIALOG_SAVESTYLE };
	CStatic	m_stPic;
	int		m_nStyle;
	int		m_nDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSaveStyleDlg)
	afx_msg void OnRadioCell();
	afx_msg void OnRadioAll();
	afx_msg void OnRadioV();
	afx_msg void OnRadioH();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVESTYLEDLG_H__A259D049_3078_48AF_861D_9646D6BA8C8D__INCLUDED_)
