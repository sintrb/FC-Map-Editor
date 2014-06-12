#if !defined(AFX_PANELDLG_H__919BE67B_D67B_4562_AFEF_96492135EEAC__INCLUDED_)
#define AFX_PANELDLG_H__919BE67B_D67B_4562_AFEF_96492135EEAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PanelDlg.h : header file
//
#include "DiyChr.h"
#include "Tile.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CPanelDlg dialog
#define COL_W 25
class CPanelDlg : public CDialog
{
// Construction
public:
	void SetInf(CString inf);
	inline unsigned char GetTile(int index);
	void DrawChrTileBox(CClientDC* pDC, int index);
	void RefreshwToA();
	void RefreshDiySize();
	void RefreshGTile();
	void DrawDiyBmp();
	void DrawStdPal();
	void DrawPal();
	void DrawChr();
	CTile m_tileDiy[10];
	int m_iSelChr;
	void RefreshCol();
	void RefresgBmp();
	void OnRButtonStdColBmp(CPoint point);
	void OnLButtonStdColBmp(CPoint point);
	int m_stdColW;
	int m_iNowCol;
	void OnRButtonColBmp(CPoint point);
	void RefresBmp();
	void OnLButtonColBmp(CPoint point);
	CBitmap m_bmpdiy;
	void OnRButtonDiyBmp(CPoint point);
	void OnLButtonDiyBmp(CPoint point);
	void ClickedChr(CPoint point);
	CPanelDlg(CWnd* pParent = NULL);   // standard constructor
	CDiyChr m_diyChrs[10];
// Dialog Data
	//{{AFX_DATA(CPanelDlg)
	enum { IDD = IDD_DIALOG_PANEL };
	CStatic	m_bmpStdCol;
	CStatic	m_bmpCol;
	CStatic	m_bmpChr;
	CStatic	m_bmpDiy;
	CComboBox	m_cbDiyList;
	int		m_rdStyle;
	int		m_iDiySel;
	BOOL	m_ckClockPal;
	BOOL	m_ckLockDiy;
	int		m_stDiyw;
	int		m_stDiyh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPanelDlg)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRadioStyle();
	afx_msg void OnButtonDiyNew();
	afx_msg void OnButtonDiyDel();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboDiy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonFill();
	afx_msg void OnChangeEditDiyW();
	afx_msg void OnChangeEditDiyH();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANELDLG_H__919BE67B_D67B_4562_AFEF_96492135EEAC__INCLUDED_)
