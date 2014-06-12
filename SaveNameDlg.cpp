// SaveNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "SaveNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveNameDlg dialog


CSaveNameDlg::CSaveNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveNameDlg)
	m_sAtb = _T("");
	m_sChr = _T("");
	m_sCol = _T("");
	m_sNam = _T("");
	//}}AFX_DATA_INIT
}


void CSaveNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveNameDlg)
	DDX_Text(pDX, IDC_EDIT_ATB, m_sAtb);
	DDX_Text(pDX, IDC_EDIT_CHR, m_sChr);
	DDX_Text(pDX, IDC_EDIT_COL, m_sCol);
	DDX_Text(pDX, IDC_EDIT_NAM, m_sNam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveNameDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveNameDlg message handlers

void CSaveNameDlg::SetName(CString atb, CString chr, CString col, CString nam)
{
	if(atb.Find('.') == -1)atb += ".atb";
	if(chr.Find('.') == -1)chr += ".chr";
	if(col.Find('.') == -1)col += ".col";
	if(nam.Find('.') == -1)nam += ".nam";

	this->m_sAtb = atb;
	this->m_sChr = chr;
	this->m_sCol = col;
	this->m_sNam = nam;
}
