// DefaultValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "DefaultValueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefaultValueDlg dialog


CDefaultValueDlg::CDefaultValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDefaultValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefaultValueDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->m_iValue = 0;
}


void CDefaultValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefaultValueDlg)
	DDX_Control(pDX, IDC_COMBO_DVALUE, m_cbDValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefaultValueDlg, CDialog)
	//{{AFX_MSG_MAP(CDefaultValueDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_DVALUE, OnSelchangeComboDvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefaultValueDlg message handlers


void CDefaultValueDlg::SetDValue(int dv)
{
	this->m_iValue = dv;
}

BOOL CDefaultValueDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_cbDValue.SetCurSel(this->m_iValue);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDefaultValueDlg::OnSelchangeComboDvalue() 
{
	// TODO: Add your control notification handler code here
	this->m_iValue = this->m_cbDValue.GetCurSel();
}
