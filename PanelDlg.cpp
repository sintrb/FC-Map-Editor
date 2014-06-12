// PanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FC地图编辑器.h"
#include "PanelDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelDlg dialog


CPanelDlg::CPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPanelDlg)
	m_rdStyle = -1;
	m_iDiySel = -1;
	m_ckClockPal = FALSE;
	m_ckLockDiy = FALSE;
	m_stDiyw = 0;
	m_stDiyh = 0;
	//}}AFX_DATA_INIT
}


void CPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelDlg)
	DDX_Control(pDX, IDC_STATIC_STDCOL_BMP, m_bmpStdCol);
	DDX_Control(pDX, IDC_STATIC_BMPCOL, m_bmpCol);
	DDX_Control(pDX, IDC_STATIC_BMP, m_bmpChr);
	DDX_Control(pDX, IDC_STATIC_DIY_BMP, m_bmpDiy);
	DDX_Control(pDX, IDC_COMBO_DIY, m_cbDiyList);
	DDX_Radio(pDX, IDC_RADIO_SIN, m_rdStyle);
	DDX_CBIndex(pDX, IDC_COMBO_DIY, m_iDiySel);
	DDX_Check(pDX, IDC_CHECK_CLOCKPAL, m_ckClockPal);
	DDX_Check(pDX, IDC_CHECK_LOCKDIY, m_ckLockDiy);
	DDX_Text(pDX, IDC_EDIT_DIY_W, m_stDiyw);
	DDV_MinMaxInt(pDX, m_stDiyw, 0, 8);
	DDX_Text(pDX, IDC_EDIT_DIY_H, m_stDiyh);
	DDV_MinMaxInt(pDX, m_stDiyh, 0, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanelDlg, CDialog)
	//{{AFX_MSG_MAP(CPanelDlg)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RADIO_SIN, OnRadioStyle)
	ON_BN_CLICKED(IDC_BUTTON_DIY_NEW, OnButtonDiyNew)
	ON_BN_CLICKED(IDC_BUTTON_DIY_DEL, OnButtonDiyDel)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_DIY, OnSelchangeComboDiy)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_FILL, OnButtonFill)
	ON_BN_CLICKED(IDC_RADIO_REC, OnRadioStyle)
	ON_BN_CLICKED(IDC_RADIO_REC_V, OnRadioStyle)
	ON_BN_CLICKED(IDC_RADIO_REC_H, OnRadioStyle)
	ON_BN_CLICKED(IDC_RADIO_COLOR, OnRadioStyle)
	ON_BN_CLICKED(IDC_RADIO_SEL, OnRadioStyle)
	ON_EN_CHANGE(IDC_EDIT_DIY_W, OnChangeEditDiyW)
	ON_EN_CHANGE(IDC_EDIT_DIY_H, OnChangeEditDiyH)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelDlg message handlers

void CPanelDlg::OnDestroy() 
{
	// TODO: Add your message handler code here
	for(int i=0; i<10; ++i){
		this->m_tileDiy[i].Destory();
	}
	CDialog::OnDestroy();
}

void CPanelDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("Clicked Dlg!\n");
	CRect rect;
	CPoint pt = point;
	this->ClientToScreen(&point);

	this->m_bmpChr.GetWindowRect(&rect);
	if(rect.PtInRect(point)){
		point.x -= rect.left;
		point.y -= rect.top;
		ClickedChr(point);
	}

	this->m_bmpDiy.GetWindowRect(&rect);	//自定义
	rect.right = rect.left + 8*16;
	rect.bottom = rect.top + 8*16;
	if(rect.PtInRect(point)){
		point.x -= rect.left;
		point.y -= rect.top;
		OnLButtonDiyBmp(point);
	}

	this->m_bmpCol.GetWindowRect(&rect);	//颜色左键检测
	rect.right = rect.left + COL_W * 4;
	rect.bottom = rect.top + COL_W * 4;
	if(rect.PtInRect(point)){
		point.x -= rect.left;
		point.y -= rect.top;
		OnLButtonColBmp(point);	//颜色左键
	}

	this->m_bmpStdCol.GetWindowRect(&rect);	//颜色左键检测
	rect.right = rect.left + this->m_stdColW * 16;
	rect.bottom = rect.top + this->m_stdColW * 4;
	if(rect.PtInRect(point)){
		point.x -= rect.left;
		point.y -= rect.top;
		OnLButtonStdColBmp(point);	//颜色左键
	}

	CDialog::OnLButtonDown(nFlags, pt);
}

void CPanelDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("Clicked Dlg!\n");
	CRect rect;
	CPoint pt = point;
	this->ClientToScreen(&point);

	this->m_bmpCol.GetWindowRect(&rect);	//颜色右键检测
	rect.right = rect.left + COL_W * 4;
	rect.bottom = rect.top + COL_W * 4;
	if(rect.PtInRect(point)){
		point.x -= rect.left;
		point.y -= rect.top;
		OnRButtonColBmp(point);	//颜色右键
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CPanelDlg::ClickedChr(CPoint point)
{
	this->m_iSelChr = point.x / ::g_chrBmps[0].m_SingleW + point.y / ::g_chrBmps[0].m_SingleH * 16;
	TRACE("CHR PT:%d\n", this->m_iSelChr);
	COLORREF bmpbuf[256];
	if(::g_chrBmps[this->m_iSelChr].GetTileBmp(this->m_iSelChr, bmpbuf)){
		this->m_bmpdiy.DeleteObject();
		this->m_bmpdiy.CreateBitmap(16, 16,1,0x20,bmpbuf);
		CString str;
		str.Format("Tile:%02x", this->m_iSelChr);
		this->SetInf(str);
	}
	RefreshGTile();
	this->DrawChr();
}

void CPanelDlg::OnRadioStyle() 
{
	// TODO: Add your control notification handler code here
	RefreshGTile();
	DrawChr();
}

void CPanelDlg::OnButtonDiyNew() 
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Format("编号:%d", this->m_cbDiyList.GetCount());
	this->m_cbDiyList.AddString(str);
	this->m_cbDiyList.SetCurSel(this->m_cbDiyList.GetCount()-1);
}

void CPanelDlg::OnButtonDiyDel() 
{
	// TODO: Add your control notification handler code here
	UINT sel = this->m_cbDiyList.GetCurSel()-1;
	this->m_cbDiyList.DeleteString(this->m_cbDiyList.GetCurSel());
	if(sel>=0)this->m_cbDiyList.SetCurSel(sel);
}

void CPanelDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CPanelDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CPanelDlg::OnLButtonDiyBmp(CPoint point)//设定自定义
{
	//TRACE("Diy LBT PT:%d, %d\n", point.x, point.y);
	this->UpdateData();
	int i = this->m_cbDiyList.GetCurSel();	
	if(i>=0 && !this->m_ckLockDiy){
		int x = point.x / 16;
		int y = point.y / 16;
		this->m_tileDiy[i].SetChr(x, y, this->m_iSelChr);
		this->RefreshGTile();
		this->DrawDiyBmp();
	}

}

void CPanelDlg::OnRButtonDiyBmp(CPoint point)
{
	//TRACE("Diy RBT PT:%d, %d\n", point.x, point.y);
}

void CPanelDlg::OnLButtonColBmp(CPoint point)//颜色左键
{
	//TRACE("Col LBT PT:%d, %d\n", point.x, point.y);
	m_iNowCol = point.x/COL_W + (point.y/COL_W)*4;
	g_iNowSelPal = point.y/COL_W;
	CString str;
	str.Format("Pal:%02x", ::g_stdpal[m_iNowCol]);
	this->SetInf(str);
	this->DrawChr();
	this->DrawDiyBmp();
	this->DrawPal();
	this->DrawStdPal();
}

void CPanelDlg::OnRButtonColBmp(CPoint point)//颜色右键
{
}

void CPanelDlg::OnLButtonStdColBmp(CPoint point)	//标准调色板左键
{
	UpdateData();
	if(!this->m_ckClockPal){
		int i = point.x/this->m_stdColW + point.y/this->m_stdColW*16;
		if(this->m_iNowCol%4==0){
			::g_stdpal[12]=g_stdpal[8]=g_stdpal[4]=g_stdpal[0] = i;
		}
		else{
			::g_stdpal[this->m_iNowCol] = i;
		}
		RefreshCol();
		CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
		p->GetActiveDocument()->UpdateAllViews(NULL);
		CString str;
		str.Format("Pal:%02x", i);
		this->SetInf(str);
	}
}

void CPanelDlg::OnRButtonStdColBmp(CPoint point)	//标准调色板右键
{
	this->m_bmpStdCol.ShowWindow(SW_HIDE);
}

void CPanelDlg::OnPaint() 
{
	CPaintDC dc(this);
	DrawChr();
	DrawPal();
	DrawStdPal();
	DrawDiyBmp();
}


void CPanelDlg::OnSelchangeComboDiy() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	RefreshwToA();
	RefreshGTile();
	this->DrawDiyBmp();
	
}

BOOL CPanelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_stdColW = 11;
	this->m_rdStyle = 0;
	this->m_iNowCol = 0;
	this->m_iSelChr = 0;
	g_selTl.SetSize(0,0);
	//this->m_tileDiy[0].TileCopy(this->m_tileDiy[1], 4, 4, FALSE);
	RefreshCol();
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPanelDlg::RefresBmp()
{
	 //m_diyChrs[::g_iNowSelPal]

}


void CPanelDlg::RefresgBmp()
{
	g_chrBmps[0].SetPal(::g_pal);
	g_chrBmps[1].SetPal(::g_pal+4);
	g_chrBmps[2].SetPal(::g_pal+8);
	g_chrBmps[3].SetPal(::g_pal+12);
}

void CPanelDlg::RefreshCol()
{
	g_stdpal[12]=g_stdpal[8]=g_stdpal[4]=g_stdpal[0];
	for(int i=0; i<16; ++i){
		::g_pal[i] = ::g_stdcol[::g_stdpal[i]] & 0x00ffffff;
	}
	RefresgBmp();
}

void CPanelDlg::OnButtonFill() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	int i = this->m_cbDiyList.GetCurSel();	
	if(i>=0 && !this->m_ckLockDiy){
		for(int y=0; y<8; ++y)
			for(int x=0; x<8; ++x)
				this->m_tileDiy[i].SetChr(x, y, this->m_iSelChr);
		RefreshGTile();
		this->RedrawWindow();
	}
}

void CPanelDlg::DrawChr()//绘制Chr选框
{
	this->m_bmpChr.SetBitmap(::g_chrBmps[::g_iNowSelPal].m_bmp);
	CClientDC* pDC = (CClientDC*)this->m_bmpChr.GetDC();
	UpdateData();
	CRect rect;
	switch(this->m_rdStyle)
	{
	case 0:{
		this->DrawChrTileBox(pDC, this->m_iSelChr);
		break;
		 }
	case 1:{
		this->DrawChrTileBox(pDC, this->m_iSelChr);
		this->DrawChrTileBox(pDC, this->m_iSelChr+1);
		this->DrawChrTileBox(pDC, this->m_iSelChr+16);
		this->DrawChrTileBox(pDC, this->m_iSelChr+17);
		break;
		 }
	case 2:
	case 3:{
		this->DrawChrTileBox(pDC, this->m_iSelChr);
		this->DrawChrTileBox(pDC, this->m_iSelChr+1);
		this->DrawChrTileBox(pDC, this->m_iSelChr+2);
		this->DrawChrTileBox(pDC, this->m_iSelChr+3);
		break;
		 }
	case 4:{

		break;
		 }
	case 5:{

		break;
		 }
	default:{

		}
	}
}

void CPanelDlg::DrawPal()//绘制调色板
{
	CClientDC* pDC = (CClientDC*)this->m_bmpCol.GetDC();
	int w = COL_W;
	int lw = 4;
	int jg = 3;
	pDC->Rectangle(0,0,4*w+2,4*w+2);
	for(int i=0, int y=0; y<4; ++y){
		for(int x=0; x<4; ++x, ++i){
			CRect rect(x*w+lw, y*w+lw, (x+1)*w-lw, (y+1)*w-lw);
			CBrush brush(g_pal[i]);
			pDC->FillRect(&rect, &brush);
		}
	}
	CRect rect(jg, ::g_iNowSelPal * w + jg, 4*w - jg, (::g_iNowSelPal+1)*w - jg);
	pDC->Draw3dRect(&rect, RGB(0xff,0,0), RGB(0xff,0,0));
	jg = 2;
	rect.left = (this->m_iNowCol%4)*w+jg;
	rect.top = (this->m_iNowCol/4)*w+jg;
	rect.right = (this->m_iNowCol%4 + 1)*w-jg;
	rect.bottom = (this->m_iNowCol/4 + 1)*w-jg;
	pDC->Draw3dRect(&rect, RGB(0xff,0,0), RGB(0xff,0,0));
}

void CPanelDlg::DrawStdPal()//绘制标准调色板
{
	int w = this->m_stdColW;
	int lw = 1;
	int jg = 1;
	if(this->m_bmpStdCol.IsWindowVisible()){
		//TRACE("Visual!!!\n");
		CClientDC* pDC = (CClientDC*)this->m_bmpStdCol.GetDC();
		CRect rc(0, 0, 16*w, 4*w);
		pDC->FillRect(&rc, NULL);
		CString str;
		int i = 0;
		for(int y=0; y<4; ++y){
			for(int x=0; x<16; ++x, ++i){
				str.Format("%x", i);
				CRect rect(x*w+lw,y*w+lw,(x+1)*w-lw,(y+1)*w-lw);
				CBrush brush(g_stdcol[i]);
				pDC->FillRect(&rect, &brush);
			}
		}
		int n = g_stdpal[this->m_iNowCol];
		CRect rect((n%16)*w,(n/16)*w,(n%16 + 1)*w-lw,(n/16 +1)*w-lw);
		pDC->Draw3dRect(&rect, RGB(0xff,0,0), RGB(0xff,0,0));
	}
}

void CPanelDlg::DrawDiyBmp()//自定义图片
{
	this->m_bmpDiy.SetBitmap(this->m_bmpdiy);
	if(this->m_cbDiyList.GetCurSel()>=0){
		int i = this->m_cbDiyList.GetCurSel();
		CClientDC* pDC = (CClientDC*)this->m_bmpDiy.GetDC();
		CRect rc(0, 0, 128, 128);
		pDC->FillRect(&rc, NULL);
		CRect rect(0, 0, this->m_tileDiy[i].max_width*16, this->m_tileDiy[i].max_height*16);
		CBrush brush(RGB(0xff,0,0));
		pDC->Draw3dRect(&rect, RGB(0xff,0,0), RGB(0xff,0,0));
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		memDC.SelectObject(&::g_chrBmps[::g_iNowSelPal].m_bmp);
		for(int y=0; y<this->m_tileDiy[i].height; ++y){
			for(int x=0; x<this->m_tileDiy[i].width; ++x){
				int tl = this->m_tileDiy[i].GetChr(x,y);
				int lx = tl%16;
				int ly = tl/16;
				ly = ly * 16;
				lx = lx * 16;
				pDC->BitBlt(x*16,y*16,16,16,&memDC,lx,ly,SRCCOPY);
			}
		}
	}
}

void CPanelDlg::RefreshGTile()
{
	int tm = g_tm;
	g_tm = 0xffff;
	UpdateData();
	TRACE("Refresh Gloab Tile:%d\n",this->m_rdStyle);
	switch(this->m_rdStyle)
	{
	case 0:{	//单选
		::g_selTl.SetSize(1,1);
		::g_selTl.SetChr(0,0,this->m_iSelChr);
		break;
		 }
	case 1:{	//连读方块
		::g_selTl.SetSize(2,2);
		::g_selTl.SetChr(0,0,this->GetTile(this->m_iSelChr));
		::g_selTl.SetChr(1,0,this->GetTile(this->m_iSelChr+1));
		::g_selTl.SetChr(0,1,this->GetTile(this->m_iSelChr+16));
		::g_selTl.SetChr(1,1,this->GetTile(this->m_iSelChr+17));
		break;
		 }
	case 2:{	//竖向方块
		::g_selTl.SetSize(2,2);
		::g_selTl.SetChr(0,0,this->GetTile(this->m_iSelChr));
		::g_selTl.SetChr(1,0,this->GetTile(this->m_iSelChr+2));
		::g_selTl.SetChr(0,1,this->GetTile(this->m_iSelChr+1));
		::g_selTl.SetChr(1,1,this->GetTile(this->m_iSelChr+3));
		break;
		 }
	case 3:{	//横向方块
		::g_selTl.SetSize(2,2);
		::g_selTl.SetChr(0,0,this->GetTile(this->m_iSelChr));
		::g_selTl.SetChr(1,0,this->GetTile(this->m_iSelChr+1));
		::g_selTl.SetChr(0,1,this->GetTile(this->m_iSelChr+2));
		::g_selTl.SetChr(1,1,this->GetTile(this->m_iSelChr+3));
		break;
		 }
	case 4:{	//描色
		::g_selTl.SetSize(0,0);
		break;
		 }
	case 5:{	//自定义
		if(this->m_cbDiyList.GetCurSel()>=0){
			int i = this->m_cbDiyList.GetCurSel();
			::g_selTl.SetSize(this->m_tileDiy[i].width , this->m_tileDiy[i].height);

			::g_selTl.TileCopy(this->m_tileDiy[i] ,0, 0, ::g_tm);
		}
		else{
			::g_selTl.SetSize(0,0);
		}
		break;
		}
	default:{
		::g_selTl.SetSize(0,0);
		}
	}
	g_tm = tm;
	//::g_selTl.inf();
}



void CPanelDlg::OnChangeEditDiyW() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int i = this->m_stDiyw;
	UpdateData();
	if((this->m_stDiyw<0 || this->m_stDiyw>8) || this->m_ckLockDiy){
		this->m_stDiyw = i;
		UpdateData(FALSE);
	}
	else{
		RefreshDiySize();
	}
	// TODO: Add your control notification handler code here
	
}

void CPanelDlg::OnChangeEditDiyH() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int i = this->m_stDiyh;
	UpdateData();
	if((this->m_stDiyh<0 || this->m_stDiyh>8) || this->m_ckLockDiy){
		this->m_stDiyh = i;
		UpdateData(FALSE);
	}
	else{
		RefreshDiySize();
	}
	// TODO: Add your control notification handler code here
	
}

void CPanelDlg::RefreshDiySize()
{
	if(this->m_cbDiyList.GetCurSel()>=0){
		int i = this->m_cbDiyList.GetCurSel();
		this->m_tileDiy[i].SetSize(this->m_stDiyw, this->m_stDiyh);
		RefreshGTile();
		this->DrawDiyBmp();
	}
}

void CPanelDlg::RefreshwToA()
{
	if(this->m_cbDiyList.GetCurSel()>=0){
		int i = this->m_cbDiyList.GetCurSel();
		this->m_stDiyw = this->m_tileDiy[i].width;
		this->m_stDiyh = this->m_tileDiy[i].height;
		UpdateData(FALSE);
	}
}

void CPanelDlg::DrawChrTileBox(CClientDC *pDC, int index)
{
	if(index<256){
		CRect rect;
		rect.left = (index%16) * ::g_chrBmps[0].m_SingleW;
		rect.right = rect.left + ::g_chrBmps[0].m_SingleW;
		rect.top = (index/16) * ::g_chrBmps[0].m_SingleH;
		rect.bottom = rect.top + ::g_chrBmps[0].m_SingleH;
		pDC->Draw3dRect(&rect, RGB(0xff,0,0), RGB(0xff,0,0));
	}
}

inline unsigned char CPanelDlg::GetTile(int index)
{
	if(index<0x256)return index;
	else return 0;
}

void CPanelDlg::SetInf(CString inf)
{
	this->SetDlgItemText(IDC_STATIC_INF, inf);
	TRACE(inf);
}
