// MapAttributeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FC地图编辑器.h"
#include "MapAttributeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapAttributeDlg dialog


CMapAttributeDlg::CMapAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapAttributeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapAttributeDlg)
	m_iHeight = 0;
	m_iWidth = 0;
	m_iCellHeight = 0;
	m_iCellWidth = 0;
	//}}AFX_DATA_INIT
	this->m_iHeight = 30;
	this->m_iWidth = 64;
	this->m_iCellHeight = 30;
	this->m_iCellWidth = 32;
}


void CMapAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapAttributeDlg)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_iHeight);
	DDV_MinMaxInt(pDX, m_iHeight, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_iWidth);
	DDV_MinMaxInt(pDX, m_iWidth, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_CELLHEIGHT, m_iCellHeight);
	DDX_Text(pDX, IDC_EDIT_CELLWIDTH, m_iCellWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapAttributeDlg, CDialog)
	//{{AFX_MSG_MAP(CMapAttributeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapAttributeDlg message handlers

BOOL CMapAttributeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapAttributeDlg::Set(int w, int h)
{
	this->m_iHeight = h;
	this->m_iWidth = w;
}

void CMapAttributeDlg::SetCell(int w, int h)
{
	this->m_iCellHeight = h;
	this->m_iCellWidth = w;
}

void CMapAttributeDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData();
	if(this->m_iCellHeight > this->m_iHeight || this->m_iCellWidth > this->m_iWidth || this->m_iCellHeight <= 0 || this->m_iCellWidth <= 0){
		AfxMessageBox("单元大小设置有误!!!", 0, NULL);
	}
	else if(this->m_iHeight % this->m_iCellHeight !=0 || this->m_iWidth % this->m_iCellWidth != 0){
		AfxMessageBox("整体不能被完整分割!!!\n整体的大小必须是单元的整数倍!!!", 0, NULL);
	}
	else if(this->m_iCellHeight %2 !=0 || this->m_iCellWidth %2 != 0){
		AfxMessageBox("属性表不能被完整的保存!!!\n单元的大小必须是偶数!!!", MB_OK, NULL);
	}
	else{
		CDialog::OnOK();
	}
}
