// ChrViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "ChrViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChrViewerDlg dialog


CChrViewerDlg::CChrViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChrViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChrViewerDlg)
	//}}AFX_DATA_INIT
	this->m_datbuf = NULL;
	this->m_chr.SetMul(2);
}


void CChrViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChrViewerDlg)
	DDX_Control(pDX, IDC_STATIC_BMP, m_sBmp);
	DDX_Control(pDX, IDC_COMBO_CHRSEL, m_cbChrSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChrViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CChrViewerDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_CHRSEL, OnSelchangeComboChrsel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChrViewerDlg message handlers

void CChrViewerDlg::SetChrFile(CString fn)
{
	this->m_chrfilename = fn;
	if(this->m_datbuf)delete this->m_datbuf;
	CFile cf(fn, CFile::modeRead | CFile::typeBinary);
	if(cf.GetLength()>0){
		this->m_datbuf = new unsigned char[(cf.GetLength()/0x1000+1)*0x1000];
		cf.Read(this->m_datbuf, cf.GetLength());
		this->m_chrCount = cf.GetLength()/0x1000;
	}
	cf.Close();
}

BOOL CChrViewerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_cbChrSel.Clear();
	for(int i=0; i<this->m_chrCount; ++i){
		CString str;
		str.Format("µÚ%d¿é", i);
		this->m_cbChrSel.AddString(str);
	}
	SelectChr(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChrViewerDlg::SelectChr(int n)
{
	this->m_chr.RefreshPicture(this->m_datbuf + 0x1000*n, ::g_pal + 4*::g_iNowSelPal);
	this->m_sBmp.SetBitmap((HBITMAP)this->m_chr.m_bmp);
	this->m_cbChrSel.SetCurSel(n);
	this->m_SelChr = n;
	this->UpdateData(FALSE);
}

void CChrViewerDlg::OnSelchangeComboChrsel() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	SelectChr(this->m_cbChrSel.GetCurSel());
}

BOOL CChrViewerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this->m_datbuf;
	return CDialog::DestroyWindow();
}
