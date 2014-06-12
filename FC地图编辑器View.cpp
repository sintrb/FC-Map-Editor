// FC地图编辑器View.cpp : implementation of the CFCView class
//

#include "stdafx.h"
#include "FC地图编辑器.h"

#include "FC地图编辑器Doc.h"
#include "FC地图编辑器View.h"

#include "DefaultValueDlg.h"
#include "MapAttributeDlg.h"
#include "SaveStyleDlg.h"
#include "InputTextDlg.h"
#include "ChrViewerDlg.h"
#include "ViewColDlg.h"

#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFCView

IMPLEMENT_DYNCREATE(CFCView, CScrollView)

BEGIN_MESSAGE_MAP(CFCView, CScrollView)
	//{{AFX_MSG_MAP(CFCView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_COMMAND(ID_SET_DEFAULTVALUE, OnSetDefaultvalue)
	ON_UPDATE_COMMAND_UI(ID_SET_DEFAULTVALUE, OnUpdateAllEnable)
	ON_COMMAND(ID_SET_MAPATTRIBUTE, OnSetMapattribute)
	ON_COMMAND(ID_SET_SAVESTYLE, OnSetSavestyle)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_ALL, OnEditAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateIsSelected)
	ON_COMMAND(ID_EDIT_TEXT, OnEditText)
	ON_COMMAND(ID_IMPORT_CHR, OnImportChr)
	ON_COMMAND(ID_IMPORT_MAP, OnImportMap)
	ON_COMMAND(ID_IMPORT_COL, OnImportCol)
	ON_COMMAND(ID_IMPORT_ATTRIBUTE, OnImportAttribute)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_FILL, OnEditFill)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TM, OnUpdateEditTm)
	ON_COMMAND(ID_EDIT_TM, OnEditTm)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_DRAWCLIPBOARD()
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOCK, OnUpdateEditLock)
	ON_COMMAND(ID_EDIT_LOCK, OnEditLock)
	ON_UPDATE_COMMAND_UI(ID_SET_MAPATTRIBUTE, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_SET_SAVESTYLE, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_CHR, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_COL, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_MAP, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_ATTRIBUTE, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ALL, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateIsSelected)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TEXT, OnUpdateIsSelected)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FILL, OnUpdateIsSelected)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESH, OnUpdateAllEnable)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFCView construction/destruction

CFCView::CFCView()
{
	// TODO: add construction code here
	this->m_iDefaultValue = 0;
	this->m_bGrid = TRUE;
	this->m_bMouseDown = FALSE;
	this->m_bSelect = FALSE;
	this->m_bHaveClipData = FALSE;
	this->m_conDraw = FALSE;
	this->m_bMapLock = FALSE;
}

CFCView::~CFCView()
{
}

BOOL CFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFCView drawing

void CFCView::OnDraw(CDC* pDC)
{
	CFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	this->LoadMapAttribute();
	TRACE("ReDraw\n");
	//Draw map
	CTile* pal = pDoc->m_Map.m_pal;	//属性表
	CTile* tile = pDoc->m_Map.m_tiles;	//名字表

	CRect rt;
	CPoint pt = this->GetScrollPosition();
	this->GetWindowRect(&rt);
	rt.bottom += this->m_iTileH;
	rt.right += this->m_iTileW;
	int lx = max(pt.x/this->m_iTileW - 1 , 0);
	int ly = max(pt.y/this->m_iTileH - 1, 0);
	int hy = min(this->m_iMapH, ly + rt.Height()/this->m_iTileH+1);
	int hx = min(this->m_iMapW, lx + rt.Width()/this->m_iTileW+1);


	for(int i=0; i<4; ++i){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		memDC.SelectObject(&::g_chrBmps[i].m_bmp);

		for(int y = ly; y < hy; ++y){
			for(int x = lx; x < hx; ++x){
				int tl = tile->GetChr(x,y);
				int lx = tl%16;
				int ly = tl/16;
				ly = ly * 16;
				lx = lx * 16;
				if(pal->GetChr(x,y)==i)pDC->BitBlt(x*16,y*16,16,16,&memDC,lx,ly,SRCCOPY);
			}
		}
	}

	//Draw Grid
	if(this->m_bGrid && !this->m_bMouseDown && !this->m_conDraw){
		CPen pen(PS_DOT, 1, RGB(0xff, 0, 0));
		CPen *pOldPen = pDC->SelectObject(&pen);
		for(int y = ly; y <= hy; ++y){
			pDC->MoveTo(0, y*this->m_iTileH);
			pDC->LineTo(hx*this->m_iTileW, y*this->m_iTileH);
		}
		for(int x = lx; x <= hx; ++x){
			pDC->MoveTo(x*this->m_iTileW, 0);
			pDC->LineTo(x*this->m_iTileW, hy*this->m_iTileH);
		}
		pDC->SelectObject(pOldPen);
		//Draw
		for(y = ly/this->m_iCellH*this->m_iCellH; y <= hy; y += this->m_iCellH){
			pDC->MoveTo(0, y*this->m_iTileH);
			pDC->LineTo(hx*this->m_iTileW, y*this->m_iTileH);
		}
		for(x = lx/this->m_iCellW*this->m_iCellW; x <= hx; x += this->m_iCellW){
			pDC->MoveTo(x*this->m_iTileW, 0);
			pDC->LineTo(x*this->m_iTileW, hy*this->m_iTileH);
		}
	}

	//Draw FoucsRect
	if(this->m_bSelect){
		CRect rc(	max(this->m_rcSelect.left, lx)*this->m_iTileW+m_iTileW/2-4,
					max(this->m_rcSelect.top, ly)*this->m_iTileH+m_iTileH/2-4,
					min(this->m_rcSelect.right, hx)*this->m_iTileW+m_iTileW/2+4,
					min(this->m_rcSelect.bottom, hy)*this->m_iTileH+m_iTileH/2+4);
		pDC->DrawFocusRect(&rc);
	}
}

void CFCView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	SetClipboardViewer();
	this->LoadMapAttribute();
	this->ReSetScroll();
}

/////////////////////////////////////////////////////////////////////////////
// CFCView printing

BOOL CFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFCView diagnostics

#ifdef _DEBUG
void CFCView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFCView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFCDoc* CFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFCDoc)));
	return (CFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFCView message handlers

void CFCView::ReSetScroll()
{
	SIZE size={this->m_iMapW * this->m_iTileW, this->m_iMapH * this->m_iTileH};
	SetScrollSizes(MM_TEXT,size);
}

void CFCView::LoadMapAttribute()
{
	CFCDoc* pDoc = GetDocument();
	CMap &map = pDoc->m_Map;
	if(map.bIsChange){// Load the data of map
		this->m_iCellH = map.iCellHeight;
		this->m_iCellW = map.iCellWidth;
		this->m_iMapH = map.iMapHeight;
		this->m_iMapW = map.iMapWidth;
		this->m_iTileH = map.iTileHeight;
		this->m_iTileW = map.iTileWidth;
		this->m_iSaveStyle = map.iSaveStyle;
		map.bIsChange = FALSE;
	}
}

void CFCView::SaveMapAttribute()
{
	CFCDoc* pDoc = GetDocument();
	CMap &map = pDoc->m_Map;
	map.iTileHeight = this->m_iTileH;
	map.iTileWidth = this->m_iTileW;
	map.iSaveStyle = this->m_iSaveStyle;
	map.SetSize(this->m_iMapW, this->m_iMapH, this->m_iCellW, this->m_iCellH);
}

void CFCView::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(this->m_bGrid);
}

void CFCView::OnViewGrid() 
{
	// TODO: Add your command handler code here
	 this->m_bGrid = !this->m_bGrid;
	 this->RedrawWindow();
}

void CFCView::OnUpdateAllEnable(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CFCView::OnSetDefaultvalue() 
{
	// TODO: Add your command handler code here
	CDefaultValueDlg dlg;
	dlg.SetDValue(this->m_iDefaultValue);
	if(dlg.DoModal() == IDOK){
		this->m_iDefaultValue = dlg.m_iValue;
	}
}



void CFCView::OnSetMapattribute() 
{
	// TODO: Add your command handler code here
	CMapAttributeDlg dlg;
	dlg.Set(this->m_iMapW, this->m_iMapH);
	dlg.SetCell(this->m_iCellW, this->m_iCellH);
	if(dlg.DoModal() == IDOK){
		this->m_iMapH = dlg.m_iHeight;
		this->m_iMapW = dlg.m_iWidth;
		this->m_iCellH = dlg.m_iCellHeight;
		this->m_iCellW = dlg.m_iCellWidth;
		this->SaveMapAttribute();
		this->ReSetScroll();
		this->RedrawWindow();
	}
}

void CFCView::OnSetSavestyle() 
{
	// TODO: Add your command handler code here
	CSaveStyleDlg dlg;
	dlg.SetStyle(this->m_iSaveStyle);
	if(dlg.DoModal() == IDOK){
		this->m_iSaveStyle = dlg.GetStyle();
		this->SaveMapAttribute();
	}
	
}

void CFCView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	this->OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	int iX = point.x / this->m_iTileW;
	int iY = point.y / this->m_iTileH;
	if((this->m_ptOldMousPoint.x / this->m_iTileW) != iX || (this->m_ptOldMousPoint.y / this->m_iTileH) != iY){
		if(iX < this->m_iMapW && iY < this->m_iMapH){
			this->m_ptOldMousPoint = point;
			if(this->m_bMouseDown){
				this->m_rcSelect.left = min(this->m_ptMouseDown.x, iX);
				this->m_rcSelect.right = max(this->m_ptMouseDown.x, iX);
				this->m_rcSelect.top = min(this->m_ptMouseDown.y, iY);
				this->m_rcSelect.bottom = max(this->m_ptMouseDown.y, iY);
				this->RedrawWindow();
			}
		}
		this->RefreshStatusBar(iX, iY);
	}
	int w = max(1, ::g_selTl.width);
	int h = max(1, ::g_selTl.height);
	if((abs(this->m_rcSelect.left - iX)>=w || abs(this->m_rcSelect.top - iY)>=h) && this->m_conDraw){
		this->m_ptMouseDown.x = iX;
		this->m_ptMouseDown.y = iY;
		this->m_rcSelect.left = iX;
		this->m_rcSelect.right = iX + w;
		this->m_rcSelect.top = iY;
		this->m_rcSelect.bottom = iY + h;
		this->RefreshStatusBar(iX, iY);
		this->SetChr(iX, iY);
		this->RefreshStatusBar(iX, iY);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CFCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags & MK_LBUTTON){
		CClientDC dc(this);
		this->OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		int iX = point.x / this->m_iTileW;
		int iY = point.y / this->m_iTileH;
		if(nFlags & MK_SHIFT){	//按下shift
			this->m_rcSelect.left = min(this->m_rcSelect.left, iX);
			this->m_rcSelect.top = min(this->m_rcSelect.top, iY);
			this->m_rcSelect.right = max(this->m_rcSelect.right, iX);
			this->m_rcSelect.bottom = max(this->m_rcSelect.bottom, iY);
			this->m_bSelect = TRUE;
			this->RedrawWindow();
		}
		else if(nFlags & MK_CONTROL && iX < this->m_iMapW && iY < this->m_iMapH){	//设置拖动
			this->m_ptMouseDown.x = iX;
			this->m_ptMouseDown.y = iY;
			this->m_rcSelect.left = this->m_rcSelect.right = iX;
			this->m_rcSelect.top = this->m_rcSelect.bottom = iY;
			this->m_bMouseDown = TRUE;
			this->m_bSelect = TRUE;
			this->RedrawWindow();
			SetCapture();
		}
		else if(!m_bMapLock && iX < this->m_iMapW && iY < this->m_iMapH){	//绘制
			//g_selTl.inf();
			this->m_ptMouseDown.x = iX;
			this->m_ptMouseDown.y = iY;
			this->m_rcSelect.left = this->m_rcSelect.right = iX;
			this->m_rcSelect.top = this->m_rcSelect.bottom = iY;
			this->m_bSelect = TRUE;
			this->m_conDraw = TRUE;
			this->RefreshStatusBar(iX, iY);
			this->SetChr(iX, iY);
			this->RefreshStatusBar(iX, iY);
			//this->RedrawWindow();
			SetCapture();
		}
		else{
			this->RedrawWindow();
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CFCView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->m_bMouseDown){
		ReleaseCapture();
		this->m_bMouseDown = FALSE;
		ReleaseCapture();
		this->RedrawWindow();
	}
	else if(this->m_conDraw){
		this->m_conDraw = FALSE;
		ReleaseCapture();
		this->RedrawWindow();
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CFCView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->m_bSelect){
		this->m_bMouseDown = FALSE;
		this->m_bSelect = FALSE;
		CClientDC dc(this);
		this->OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		int iX = point.x / this->m_iTileW;
		int iY = point.y / this->m_iTileH;
		this->RefreshStatusBar(iX, iY);
	}
	this->RedrawWindow();
	CScrollView::OnRButtonDown(nFlags, point);
}

void CFCView::RefreshStatusBar(int iX, int iY)
{
	CString str;
	str.Format("绝对坐标(%02x,%02x) Tile:%02x", iX, iY, GetDocument()->m_Map.m_tiles->GetChr(iX, iY));
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_wndStatusBar.SetPaneText(1, str);

	str.Format("单元:(%02x,%02x) 坐标(%02x,%02x)", iX/this->m_iCellW, iY/this->m_iCellH, iX%this->m_iCellW, iY%this->m_iCellH);
	pFrame->m_wndStatusBar.SetPaneText(2, str);
	if(this->m_bSelect){
		str.Format("选区(%02x,%02x) to (%02x,%02x)",
					this->m_rcSelect.left, this->m_rcSelect.top,
					this->m_rcSelect.right, this->m_rcSelect.bottom);
		pFrame->m_wndStatusBar.SetPaneText(3, str);

		str.Format("大小(%02xx%02x)", this->m_rcSelect.right-this->m_rcSelect.left+1, this->m_rcSelect.bottom-this->m_rcSelect.top+1);
		pFrame->m_wndStatusBar.SetPaneText(4, str);
	}
	else{
		pFrame->m_wndStatusBar.SetPaneText(3, _T("选区(00,00) to (00,00)"));
		pFrame->m_wndStatusBar.SetPaneText(4, _T("大小(00x00)"));
	}
}

void CFCView::OnEditAll() 
{
	// TODO: Add your command handler code here
	this->m_rcSelect.left = 0;
	this->m_rcSelect.right = this->m_iMapW - 1;
	this->m_rcSelect.top = 0;
	this->m_rcSelect.bottom = this->m_iMapH - 1;
	this->m_bSelect = TRUE;
	RefreshStatusBar();
	this->RedrawWindow();
}

void CFCView::OnUpdateIsSelected(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bMapLock && this->m_bSelect);
}

void CFCView::OnEditText() 
{
	// TODO: Add your command handler code here
	CInputTextDlg dlg;
	if(!m_bMapLock && dlg.DoModal()==IDOK){
		CFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CTile* pal = pDoc->m_Map.m_pal;	//属性表
		CTile* tile = pDoc->m_Map.m_tiles;	//名字表
		CString str = dlg.m_sText;
		for(int y = 0, int x = 0, int i = 0; i < str.GetLength(); ++i){
			unsigned char c = str.GetAt(i);
			if(c=='\n'){
				++y;
				x = 0;
			}
			else if(c!='\r'){
				c += dlg.m_iOffset;
				tile->SetChr(this->m_rcSelect.left+x, this->m_rcSelect.top+y, c);
				pal->SetChr(this->m_rcSelect.left+x, this->m_rcSelect.top+y,g_iNowSelPal);
				++x;
			}
		}
		this->RedrawWindow();
	}
}

void CFCView::OnImportChr() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(	TRUE,
						"*.chr",
						NULL,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"字模文件(*.chr)|*.chr|所有文件(*.*)|*.*||");
	if(dlg.DoModal() == IDOK){
		CString fn = dlg.GetPathName();
		CChrViewerDlg vdlg;
		vdlg.SetChrFile(fn);
		if(vdlg.DoModal()==IDOK){
			GetDocument()->SetChr(fn, vdlg.m_SelChr);
		}
	}
}

void CFCView::OnImportMap()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(	TRUE,
						"*.chr",
						NULL,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"名字表文件(*.nam)|*.nam|所有文件(*.*)|*.*||");
	if(dlg.DoModal() == IDOK){
		CString fn = dlg.GetPathName();
		GetDocument()->SetNam(fn);
	}
}

void CFCView::OnImportCol() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(	TRUE,
						"*.chr",
						NULL,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"调色文件(*.col)|*.col|所有文件(*.*)|*.*||");
	if(dlg.DoModal() == IDOK){
		CString fn = dlg.GetPathName();
		//AfxMessageBox(fn);
		CViewColDlg dlg;
		dlg.SetFilename(fn);
		//dlg.DoModal();
		if(dlg.DoModal()==IDOK && dlg.m_iSeltPal>=0){
			GetDocument()->SetPal(fn, dlg.m_iSeltPal);
		}
	}
}

void CFCView::OnImportAttribute() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(	TRUE,
						"*.chr",
						NULL,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"属性表文件(*.atb)|*.atb|所有文件(*.*)|*.*||");
	if(dlg.DoModal() == IDOK){
		CString fn = dlg.GetPathName();
		GetDocument()->SetAtb(fn);
	}
}

void CFCView::SetChr(int x, int y)
{
	this->m_rcSelect.right = this->m_rcSelect.left + g_selTl.width - 1;
	this->m_rcSelect.bottom = this->m_rcSelect.top + g_selTl.height - 1;
	PasteTo();
	//tile->SetChr(x, y, 'A');
	this->RedrawWindow();
}

void CFCView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	if(!m_bMapLock){
		CFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CTile* tile = pDoc->m_Map.m_tiles;	//名字表
		tile->fill(this->m_rcSelect.left, this->m_rcSelect.top, this->m_rcSelect.Width()+1, this->m_rcSelect.Height()+1, (unsigned char)this->m_iDefaultValue);
		this->RedrawWindow();
		SetModifiedFlag();
	}
}

void CFCView::OnEditFill() 
{
	// TODO: Add your command handler code here
	if(!m_bMapLock){
		PasteTo();
		this->RedrawWindow();
		SetModifiedFlag();
	}
}

void CFCView::OnUpdateEditTm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(g_tm<=255);
	pCmdUI->Enable();
}

void CFCView::OnEditTm() 
{
	// TODO: Add your command handler code here
	if(g_tm>255){
		g_tm = this->m_iDefaultValue;
	}
	else{
		g_tm = 256;
	}
}

void CFCView::PasteTo()
{
	if(!m_bMapLock){
		CFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CTile* tile = pDoc->m_Map.m_tiles;	//名字表
		CTile* pal = pDoc->m_Map.m_pal;	//调色
		tile->fill(this->m_rcSelect.left, this->m_rcSelect.top, this->m_rcSelect.Width()+1, this->m_rcSelect.Height()+1, g_selTl);
		
		int x = this->m_rcSelect.left;
		int y = this->m_rcSelect.top;
		int w = max(max(this->m_rcSelect.Width()+1, g_selTl.width), 1);
		int h = max(max(this->m_rcSelect.Height()+1, g_selTl.height), 1);
		pal->fillEx(x, y, w, h, g_iNowSelPal);
		SetModifiedFlag();
	}
}

void CFCView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	this->RedrawWindow();
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFCView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	this->RedrawWindow();
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CFCView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rt;
	CPoint pt = this->GetScrollPosition();
	this->GetWindowRect(&rt);
	int lx = pt.x/this->m_iTileW;
	int ly = pt.y/this->m_iTileH;
	int hy = min(this->m_iMapH, ly + rt.Height()/this->m_iTileH+1);
	int hx = min(this->m_iMapW, lx + rt.Width()/this->m_iTileW+1);
	CRect rect;
	rect.bottom = pt.y + rt.Height();
	rect.right = pt.x + rt.Width();

	rect.left = 0;
	rect.top = hy * this->m_iTileH + 1;
	pDC->FillRect(rect, NULL);

	rect.top = 0;
	rect.left = hx * this->m_iTileW + 1;
	pDC->FillRect(rect, NULL);
	TRACE("%d, %d -> %d, %d", rt.left, rt.top, rt.right, rt.bottom);
	TRACE("ERASE\n");
	return TRUE;
	//return CScrollView::OnEraseBkgnd(pDC);
}

void CFCView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	TRACE("Copy (%d,%d)->(%d,%d)\n", this->m_rcSelect.left, this->m_rcSelect.top, this->m_rcSelect.right, this->m_rcSelect.bottom);
	UINT format = RegisterClipboardFormat("FC_MAP_EDITOR");
	if(OpenClipboard())
	{
		BeginWaitCursor();
		int w = this->m_rcSelect.Width()+1;
		int h = this->m_rcSelect.Height()+1;
		CClipboardData ds;
		ds.width = w;
		ds.height = h;
		CFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CTile* tile = pDoc->m_Map.m_tiles;	//名字表
		HGLOBAL clipbuffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, sizeof(CClipboardData) + sizeof(unsigned char)*w*h);
		CClipboardData * buffer = (CClipboardData*)GlobalLock(clipbuffer);
		*buffer = ds;
		unsigned char* buf = (unsigned char*)(buffer + 1);
		for(int y=0, int i=0; y<h; ++y){
			for(int x=0; x<w; ++x, ++i){
				buf[i] = tile->GetChr(this->m_rcSelect.left + x, this->m_rcSelect.top + y);
			}
		}
		GlobalUnlock(clipbuffer);
		SetClipboardData(format,clipbuffer);

		CloseClipboard();
		EndWaitCursor();
	}

}

void CFCView::OnEditCut() 
{
	// TODO: Add your command handler code here
	this->OnEditCopy();
	if(!m_bMapLock)this->OnEditDelete();
}

void CFCView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	UINT format = RegisterClipboardFormat("FC_MAP_EDITOR");
	if(!m_bMapLock && OpenClipboard())
	{
		BeginWaitCursor();
		HANDLE hdata =GetClipboardData(format);
		if(hdata){
			CClipboardData* buffer = (CClipboardData*)GlobalLock(hdata);
			CClipboardData ds = *buffer;
			CTile ct(0,0);
			ct.width = ct.max_width = ds.width;
			ct.height = ct.max_height = ds.height;
			ct.data = (unsigned char*)(buffer + 1);
			CFCDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			CTile* tile = pDoc->m_Map.m_tiles;	//名字表
			tile->TileCopy(ct, this->m_rcSelect.left, this->m_rcSelect.top, ::g_tm);
			GlobalUnlock(hdata);
			CloseClipboard();
			TRACE("Paste %d,%d\n", ds.width, ds.height);
			ct.data = NULL;
		}
		CloseClipboard();
		EndWaitCursor();
		this->RedrawWindow();
	}
}

void CFCView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_bHaveClipData && this->m_bSelect && !m_bMapLock);
}

void CFCView::OnDrawClipboard() 
{
	CScrollView::OnDrawClipboard();
	
	// TODO: Add your message handler code here
	UINT format = RegisterClipboardFormat("FC_MAP_EDITOR");
	if(OpenClipboard())
	{
		HANDLE hdata =GetClipboardData(format);
		if(hdata){
			this->m_bHaveClipData = TRUE;
		}
		else{
			this->m_bHaveClipData = FALSE;
		}
		CloseClipboard();
	}
}

void CFCView::OnViewRefresh() 
{
	// TODO: Add your command handler code here
	this->RedrawWindow();
}

void CFCView::SetModifiedFlag(BOOL flag)
{
	GetDocument()->SetModifiedFlag(flag);
}

void CFCView::OnUpdateEditLock(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bMapLock);
}

void CFCView::OnEditLock() 
{
	// TODO: Add your command handler code here
	m_bMapLock = !m_bMapLock;
}

void CFCView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_bSelect);
}
