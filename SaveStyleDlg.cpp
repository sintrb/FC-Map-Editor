// SaveStyleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FC地图编辑器.h"
#include "SaveStyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveStyleDlg dialog


CSaveStyleDlg::CSaveStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveStyleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveStyleDlg)
	m_nStyle = -1;
	m_nDir = -1;
	//}}AFX_DATA_INIT
}


void CSaveStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveStyleDlg)
	DDX_Control(pDX, IDC_STATIC_PIC, m_stPic);
	DDX_Radio(pDX, IDC_RADIO_CELL, m_nStyle);
	DDX_Radio(pDX, IDC_RADIO_V, m_nDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveStyleDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveStyleDlg)
	ON_BN_CLICKED(IDC_RADIO_CELL, OnRadioCell)
	ON_BN_CLICKED(IDC_RADIO_ALL, OnRadioAll)
	ON_BN_CLICKED(IDC_RADIO_V, OnRadioV)
	ON_BN_CLICKED(IDC_RADIO_H, OnRadioH)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveStyleDlg message handlers

void CSaveStyleDlg::OnRadioCell() 
{
	// TODO: Add your control notification handler code here
	//this->m_stPic.SetBitmap(NULL);
	this->RefreshUI();
}

void CSaveStyleDlg::OnRadioAll() 
{
	// TODO: Add your control notification handler code here
	this->RefreshUI();
}

void CSaveStyleDlg::OnRadioV() 
{
	// TODO: Add your control notification handler code here
	this->RefreshUI();
}

void CSaveStyleDlg::OnRadioH() 
{
	// TODO: Add your control notification handler code here
	this->RefreshUI();
}

void CSaveStyleDlg::SetStyle(int st)
{
	this->m_iStyle = st;
	this->m_nStyle = st/2;
	this->m_nDir = st%2;
}

int CSaveStyleDlg::GetStyle()
{
	return this->m_iStyle;
}

BOOL CSaveStyleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	bmpAV.LoadBitmap(IDB_BITMAP_ALLV);
	bmpAH.LoadBitmap(IDB_BITMAP_ALLH);
	bmpCV.LoadBitmap(IDB_BITMAP_CELLV);
	bmpCH.LoadBitmap(IDB_BITMAP_CELLH);
	this->RefreshUI();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveStyleDlg::RefreshUI()
{
	this->UpdateData(TRUE);
	if(this->m_nDir != 0 && this->m_nDir != 1)this->m_nDir = 1;
	if(this->m_nStyle != 0 && this->m_nStyle != 1)this->m_nStyle = 1;
	this->m_iStyle = this->m_nDir + this->m_nStyle * 2;
	switch(this->m_iStyle)
	{
	case 0:{//单元格横向
		this->m_stPic.SetBitmap((HBITMAP)bmpCH.m_hObject);
		break;
		   }
	case 1:{//单元格纵向
		this->m_stPic.SetBitmap((HBITMAP)bmpCV.m_hObject);
		break;
		   }
	case 2:{//整体横向
		this->m_stPic.SetBitmap((HBITMAP)bmpAH.m_hObject);
		break;
		   }
	case 3:{//整体纵向
		this->m_stPic.SetBitmap((HBITMAP)bmpAV.m_hObject);
		break;
		   }
	default:{
		AfxMessageBox("错误的保存方式!!!", MB_OK, NULL);
		this->m_iStyle = 0;
			}
	}
	
	this->UpdateData(FALSE);
}

