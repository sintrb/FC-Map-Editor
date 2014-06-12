// ViewColDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "ViewColDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewColDlg dialog


CViewColDlg::CViewColDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewColDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewColDlg)
	m_iSeltPal = -1;
	//}}AFX_DATA_INIT
	this->buf = NULL;
}


void CViewColDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewColDlg)
	DDX_Control(pDX, IDC_COMBO_INDEX, m_cbIndex);
	DDX_Control(pDX, IDC_STATIC_COL, m_bmpCol);
	DDX_CBIndex(pDX, IDC_COMBO_INDEX, m_iSeltPal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewColDlg, CDialog)
	//{{AFX_MSG_MAP(CViewColDlg)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewColDlg message handlers

void CViewColDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect(0,0,0,0);
	CClientDC* pDC = (CClientDC*)this->m_bmpCol.GetDC();
	int w = 16;
	int h = 100;
	rect.bottom = h;
	rect.right = w *16;
	pDC->FillRect(&rect, NULL);
	col[12]=col[8]=col[4]=col[0];
	for(int x=0; x<16; ++x){
		this->col[x] &= 0x3f;
		CRect rc(x*w,0,(x+1)*w,h);
		CBrush bs(g_stdcol[this->col[x]]);
		pDC->FillRect(&rc, &bs);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CViewColDlg::SetFilename(CString fn)
{
	this->filename = fn;
}

void CViewColDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(this->buf){
		delete this->buf;
		this->buf = NULL;
	}
	CDialog::OnOK();
}

void CViewColDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(this->buf){
		delete this->buf;
		this->buf = NULL;
	}
	CDialog::OnCancel();
}

BOOL CViewColDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFile cf(this->filename, CFile::modeRead | CFile::typeBinary);
	for(int i=0; i<cf.GetLength()/16; ++i){
		CString str;
		str.Format("µÚ%02x¿é", i);
		this->m_cbIndex.AddString(str);
	}
	this->buf = new unsigned char[((cf.GetLength())/16+1)*16];
	cf.Read(this->buf, cf.GetLength());
	cf.Close();
	if(i>0){
		CopyMemory(this->col, this->buf , 16);
		this->m_cbIndex.SetCurSel(0);
		//this->UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewColDlg::OnSelchangeComboIndex() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	CopyMemory(this->col, this->buf+this->m_cbIndex.GetCurSel()*16 , 16);
	this->RedrawWindow();	
}
