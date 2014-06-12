#if !defined(AFX_MAPATTRIBUTEDLG_H__161E0D32_CDC2_427B_B5BC_05AC35C79E7B__INCLUDED_)
#define AFX_MAPATTRIBUTEDLG_H__161E0D32_CDC2_427B_B5BC_05AC35C79E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapAttributeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapAttributeDlg dialog

class CMapAttributeDlg : public CDialog
{
// Construction
public:
	void SetCell(int w = 32, int h = 30);
	void Set(int w = 0, int h = 0);
	CMapAttributeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapAttributeDlg)
	enum { IDD = IDD_DIALOG_MAPATTRIBUTE };
	int		m_iHeight;
	int		m_iWidth;
	int		m_iCellHeight;
	int		m_iCellWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapAttributeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapAttributeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPATTRIBUTEDLG_H__161E0D32_CDC2_427B_B5BC_05AC35C79E7B__INCLUDED_)
