// InputTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "InputTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputTextDlg dialog


CInputTextDlg::CInputTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputTextDlg)
	m_iOffset = 0;
	m_sText = _T("");
	//}}AFX_DATA_INIT
}


void CInputTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputTextDlg)
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_iOffset);
	DDV_MinMaxInt(pDX, m_iOffset, -255, 255);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputTextDlg, CDialog)
	//{{AFX_MSG_MAP(CInputTextDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputTextDlg message handlers
