// FC地图编辑器Doc.cpp : implementation of the CFCDoc class
//

#include "stdafx.h"
#include "FC地图编辑器.h"
#include "MainFrm.h"

#include "FC地图编辑器Doc.h"
#include "Map.h"
#include "SaveNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFCDoc

IMPLEMENT_DYNCREATE(CFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CFCDoc, CDocument)
	//{{AFX_MSG_MAP(CFCDoc)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RELOAD, OnUpdateViewReload)
	ON_COMMAND(ID_VIEW_RELOAD, OnViewReload)
	ON_UPDATE_COMMAND_UI(ID_SET_LISTEN, OnUpdateSetListen)
	ON_COMMAND(ID_SET_LISTEN, OnSetListen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFCDoc construction/destruction

CFCDoc::CFCDoc()
{
	// TODO: add one-time construction code here
	m_iChrBank = 0;
	m_iColBank = 0;
	m_bListenFile = FALSE;
	m_bListened = FALSE;
}

CFCDoc::~CFCDoc()
{
}

BOOL CFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_bHaveName = FALSE;
	this->m_Map.OnNew();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFCDoc serialization

void CFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CString s;
		CString nl = "\r\n";
		ar.WriteString(CString("[INFO]") + nl);
		ar.WriteString(CString("CHRFILE=") + this->m_sChrName + nl);
		ar.WriteString(CString("NAMFILE=") + this->m_sNamName + nl);
		ar.WriteString(CString("ATBFILE=") + this->m_sAtbName + nl);
		ar.WriteString(CString("COLFILE=") + this->m_sColName + nl);
		s.Format("%d", this->m_iChrBank);
		ar.WriteString(CString("CHRBANK=") + s + nl);
		s.Format("%d", this->m_iColBank);
		ar.WriteString(CString("COLBANK=") + s + nl);

		s.Format("%d", this->m_Map.iCellWidth);
		ar.WriteString(CString("CELLWIDTH=") + s + nl);
		s.Format("%d", this->m_Map.iCellHeight);
		ar.WriteString(CString("CELLHEIGHT=") + s + nl);

		s.Format("%d", this->m_Map.iMapWidth);
		ar.WriteString(CString("MAPWIDTH=") + s + nl);
		s.Format("%d", this->m_Map.iMapHeight);
		ar.WriteString(CString("MAPHEIGHT=") + s + nl);

		s.Format("%d", this->m_Map.iSaveStyle);
		ar.WriteString(CString("SAVESTYLE=") + s + nl);

		//保存其他文件
		this->SaveChr();
		this->SaveAtb();
		this->SavePal();
		this->SaveNam();
		IgnoreFileTime();
	}
	else
	{
		// TODO: add loading code here
		CString kv;
		CString k;
		CString v;
		int mw = 0;
		int mh = 0;
		int cw = 0;
		int ch = 0;
		while(ar.ReadString(kv)){
			if(GetKeyValue(kv, k, v)){
				//AfxMessageBox(k + "===" + v);
				if(k==""){
				}
				else if(k=="CHRFILE"){
					this->m_sChrName = v;
				}
				else if(k=="NAMFILE"){
					this->m_sNamName = v;
				}
				else if(k=="ATBFILE"){
					this->m_sAtbName = v;
				}
				else if(k=="COLFILE"){
					this->m_sColName = v;
				}
				else if(k=="CHRBANK"){
					this->m_iChrBank = atoi(v);
				}
				else if(k=="COLBANK"){
					this->m_iColBank = atoi(v);
				}
				else if(k=="CELLWIDTH"){
					cw = atoi(v);
				}
				else if(k=="CELLHEIGHT"){
					ch = atoi(v);
				}
				else if(k=="MAPWIDTH"){
					mw = atoi(v);
				}
				else if(k=="MAPHEIGHT"){
					mh = atoi(v);
				}
				else if(k=="SAVESTYLE"){
					this->m_Map.iSaveStyle = atoi(v);
				}
				else{
					AfxMessageBox("未知的工程属性:" + kv);
				}
			}
		}
		this->m_Map.SetSize(mw, mh, cw, ch);
		this->m_Map.bIsChange = TRUE;
		this->SetChr(this->m_sChrName, this->m_iChrBank);
		this->SetAtb(this->m_sAtbName);
		this->SetNam(this->m_sNamName);
		this->SetPal(this->m_sColName, this->m_iColBank);
		if(this->m_sChrName.GetLength()>0 && this->m_sColName.GetLength()>0 && this->m_sAtbName.GetLength()>0 && this->m_sNamName.GetLength()>0){
			this->m_bHaveName = TRUE;
		}
		IgnoreFileTime();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFCDoc diagnostics

#ifdef _DEBUG
void CFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFCDoc commands

void CFCDoc::SetChr(CString fn, int index)
{
	TRY{
		CFile cf(fn, CFile::modeRead | CFile::typeBinary);
		if((index*0x1000 + 0x1000) <= cf.GetLength()){
			cf.Seek(index * 0x1000, CFile::begin);
			unsigned char buf[0x1000];
			cf.Read(buf, 0x1000);
			g_chrBmps[0].SetBuf(buf);
			g_chrBmps[0].SetPal(::g_pal);
			g_chrBmps[1].SetBuf(buf);
			g_chrBmps[1].SetPal(::g_pal+4);
			g_chrBmps[2].SetBuf(buf);
			g_chrBmps[2].SetPal(::g_pal+8);
			g_chrBmps[3].SetBuf(buf);
			g_chrBmps[3].SetPal(::g_pal+12);
			this->m_iChrBank = index;
			this->UpdateAllViews(NULL);
		}
		else{
			AfxMessageBox("抱歉:CHR文件的大小已经被其他软件所改变,没法准确的导入数据!!!");
		}
		this->m_sChrName = cf.GetFileName();
		CString str = cf.GetFilePath();
		this->m_sChrPath = str.Left(str.ReverseFind('\\'));
		this->m_iChrBank = index;
		cf.Close();
	}
	CATCH(CFileException, e){
		AfxMessageBox(CString("打开文件") + fn + CString("时出错!!!"));
	}
	END_CATCH
}

BOOL CFCDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString s = lpszPathName;
	CString s1, s2;
	
	s1 = s.Mid(0, s.ReverseFind('\\'));
	s2 = s.Mid(s.ReverseFind('\\')+1, s.GetLength());
	if(s1 != this->m_sProjectPath || s2 != this->m_sProjectName){
		this->m_sProjectName = s2;
		this->m_sProjectPath = s1;
		SetCurrentDirectory(this->m_sProjectPath);
		this->m_bHaveName = FALSE;
	}
	int i = this->m_sProjectName.ReverseFind('.');
	if(i>=0){
		s = this->m_sProjectName.Mid(0, i);
	}
	else{
		s = this->m_sProjectName;
	}
	if(m_bHaveName){
		return CDocument::OnSaveDocument(lpszPathName);
	}
	else{
		CSaveNameDlg dlg;
		if(this->m_sAtbName.GetLength()==0)this->m_sAtbName = s;
		if(this->m_sChrName.GetLength()==0)this->m_sChrName = s;
		if(this->m_sColName.GetLength()==0)this->m_sColName = s;
		if(this->m_sNamName.GetLength()==0)this->m_sNamName = s;
		dlg.SetName(this->m_sAtbName, this->m_sChrName, this->m_sColName, this->m_sNamName);
		if(dlg.DoModal() == IDOK){
			this->m_sAtbName = dlg.m_sAtb;
			if(this->m_sChrName != dlg.m_sChr || this->m_sChrPath != this->m_sProjectPath){
				CopyFile(this->m_sChrPath + "\\" + this->m_sChrName, dlg.m_sChr, NULL);
				this->m_sChrName = dlg.m_sChr;
			}
			if(this->m_sColName != dlg.m_sCol){
				this->m_sColName = dlg.m_sCol;
				CFile cf(this->m_sColName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate);
				cf.Close();
				this->m_iColBank = 0;
			}
			else{
				CopyFile(this->m_sColPath + "\\" + this->m_sColName, dlg.m_sCol, NULL);
			}
			this->m_sColName = dlg.m_sCol;
			this->m_sNamName = dlg.m_sNam;
			this->m_bHaveName = TRUE;
			return CDocument::OnSaveDocument(lpszPathName);
		}
	}
	return FALSE;
}

BOOL CFCDoc::GetKeyValue(CString &kv, CString &k, CString &v)
{
	int i = kv.Find('=');
	if(i>0 && i < kv.GetLength()){
		k = kv.Left(i);
		v = kv.Right(kv.GetLength() - i - 1);
		return TRUE;
	}
	return FALSE;
}

void CFCDoc::SetPal(CString fn, int index)
{
	TRY{
		CFile cf(fn, CFile::modeRead | CFile::typeBinary);
		if((index*16 + 16) <= cf.GetLength()){
			cf.Seek(16*index, CFile::begin);
			cf.Read(::g_stdpal, sizeof(unsigned char)*16);
			RefreshCol();
			this->UpdateAllViews(NULL);
		}
		else{
			AfxMessageBox("抱歉:COL文件的大小已经被其他软件所改变,没法准确的导入数据!!!");
		}
		this->m_sColName = cf.GetFileName();
		CString str = cf.GetFilePath();
		this->m_sColPath = str.Left(str.ReverseFind('\\'));
		this->m_iColBank = index;
		cf.Close();
	}
	CATCH(CFileException, e){
		AfxMessageBox(CString("打开文件") + fn + CString("时出错!!!"));
	}
	END_CATCH
}

void CFCDoc::RefreshCol()
{
	g_stdpal[12]=g_stdpal[8]=g_stdpal[4]=g_stdpal[0];
	for(int i=0; i<16; ++i){
		::g_stdpal[i] &= 0x3f;
		::g_pal[i] = ::g_stdcol[::g_stdpal[i]] & 0x00ffffff;
	}
	RefresgBmp();
}

void CFCDoc::RefresgBmp()
{
	g_chrBmps[0].SetPal(::g_pal);
	g_chrBmps[1].SetPal(::g_pal+4);
	g_chrBmps[2].SetPal(::g_pal+8);
	g_chrBmps[3].SetPal(::g_pal+12);
}

void CFCDoc::SetNam(CString fn)
{
	unsigned char* buf = NULL;
	TRY{
		CFile cf(fn, CFile::modeRead | CFile::typeBinary);
		if(this->m_Map.GetNamSize()>0 && this->m_Map.GetNamSize()<=cf.GetLength()){
			UINT l = this->m_Map.GetNamSize();
			buf = new unsigned char[l];
			cf.Read(buf, l);
			UINT i = 0;
			switch(this->m_Map.iSaveStyle)
			{
			case 0:{//0:单元格横向
				for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
					for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
						for(int y = 0; y < this->m_Map.iCellHeight; ++y){
							for(int x = 0; x < this->m_Map.iCellWidth; ++x){
								this->m_Map.m_tiles->SetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y, buf[i]);
								++i;
							}
						}
					}
				}
				break;
				   }
			case 1:{//1:单元格纵向
				for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
					for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
						for(int x = 0; x < this->m_Map.iCellWidth; ++x){
							for(int y = 0; y < this->m_Map.iCellHeight; ++y){
								this->m_Map.m_tiles->SetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y, buf[i]);
								++i;
							}
						}
					}
				}
				break;
				   }
			case 2:{//2:整体横向
				for(int y = 0; y < this->m_Map.iMapHeight; ++y){
					for(int x = 0; x < this->m_Map.iMapWidth; ++x){
						this->m_Map.m_tiles->SetChr(x, y, buf[i]);
						++i;
					}
				}
				break;
				   }
			case 3:{//3:整体纵向
				for(int x = 0; x < this->m_Map.iMapWidth; ++x){
					for(int y = 0; y < this->m_Map.iMapHeight; ++y){
						this->m_Map.m_tiles->SetChr(x, y, buf[i]);
						++i;
					}
				}
				break;
				   }
			default:{
				AfxMessageBox("找不到正确的导入方式!!!");
					}
			}
			delete buf;
		}
		else{
			AfxMessageBox("抱歉:NAM文件的大小已经被其他软件所改变或者是地图太大了,没法准确的导入数据!!!");
		}		
		this->m_sNamName = cf.GetFileName();
		cf.Close();
		this->UpdateAllViews(NULL);
	}
	CATCH(CFileException, e){
		if(buf)delete buf;
		AfxMessageBox(CString("打开文件") + fn + CString("时出错!!!"));
	}
	END_CATCH
}

void CFCDoc::SetAtb(CString fn)
{
	unsigned char* buf = NULL;
	TRY{
		CFile cf(fn, CFile::modeRead | CFile::typeBinary);
		TRACE("%d\n", this->m_Map.GetAtbSize());
		if(this->m_Map.GetAtbSize()>0 && this->m_Map.GetAtbSize()<=cf.GetLength()){
			UINT l = this->m_Map.GetNamSize();
			buf = new unsigned char[l];
			cf.Read(buf, l);
			UINT i = 0;
			unsigned char pal[4];
			switch(this->m_Map.iSaveStyle)
			{
			case 0:{//0:单元格横向
				for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
					for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
						for(int y = 0; y < this->m_Map.iCellHeight; y+=4){
							for(int x = 0; x < this->m_Map.iCellWidth; x+=4){
								this->GetPal(buf[i], pal);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y, pal[0]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y, pal[1]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y+2, pal[2]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y+2, pal[3]);
								++i;
							}
						}
					}
				}
				break;
				   }
			case 1:{//1:单元格纵向
				for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
					for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
						for(int x = 0; x < this->m_Map.iCellWidth; x+=4){
							for(int y = 0; y < this->m_Map.iCellHeight; y+=4){
								this->GetPal(buf[i], pal);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y, pal[0]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y, pal[1]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y+2, pal[2]);
								this->m_Map.m_pal->SetChrEx(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y+2, pal[3]);
								++i;
							}
						}
					}
				}
				break;
				   }
			case 2:{//2:整体横向
				for(int y = 0; y < this->m_Map.iMapHeight; y+=4){
					for(int x = 0; x < this->m_Map.iMapWidth; x+=4){
						this->GetPal(buf[i], pal);
						this->m_Map.m_pal->SetChrEx(x, y, pal[0]);
						this->m_Map.m_pal->SetChrEx(x+2, y, pal[1]);
						this->m_Map.m_pal->SetChrEx(x, y+2, pal[2]);
						this->m_Map.m_pal->SetChrEx(x+2, y+2, pal[3]);
						++i;
					}
				}
				break;
				   }
			case 3:{//3:整体纵向
				for(int x = 0; x < this->m_Map.iMapWidth; x+=4){
					for(int y = 0; y < this->m_Map.iMapHeight; y+=4){
						this->GetPal(buf[i], pal);
						this->m_Map.m_pal->SetChrEx(x, y, pal[0]);
						this->m_Map.m_pal->SetChrEx(x+2, y, pal[1]);
						this->m_Map.m_pal->SetChrEx(x, y+2, pal[2]);
						this->m_Map.m_pal->SetChrEx(x+2, y+2, pal[3]);
						++i;
					}
				}
				break;
				   }
			default:{
				AfxMessageBox("找不到正确的导入方式!!!");
					}
			}
			delete buf;
		}
		else{
			AfxMessageBox("抱歉:ATB文件的大小已经被其他软件所改变或者是地图太大了,没法准确的导入数据!!!");
		}
		this->m_sAtbName = cf.GetFileName();
		cf.Close();
		this->UpdateAllViews(NULL);
	}
	CATCH(CFileException, e){
		if(buf)delete buf;
		AfxMessageBox(CString("打开文件") + fn + CString("时出错!!!"));
	}
	END_CATCH
}

inline void CFCDoc::GetPal(unsigned char atb, unsigned char *pal)
{
	pal[0] = atb & 0x03;
	pal[1] = (atb>>2) & 0x03;
	pal[2] = (atb>>4) & 0x03;
	pal[3] = (atb>>6) & 0x03;
}

unsigned char CFCDoc::GetAtb(unsigned char *pal)
{
	unsigned char atb = 0;
	atb = pal[0] & 0x03 | ((pal[1]&0x03)<<2) | ((pal[2]&0x03)<<4) | ((pal[3]&0x03)<<6);
	return atb;
}

void CFCDoc::SaveAtb()
{
	unsigned char* buf = NULL;
	TRY{
		CFile cf(this->m_sAtbName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate);
		UINT l = this->m_Map.GetAtbSize();
		buf = new unsigned char[l];
		UINT i = 0;
		unsigned char pal[4];
		switch(this->m_Map.iSaveStyle)
		{
		case 0:{//0:单元格横向
			for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
				for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
					for(int y = 0; y < this->m_Map.iCellHeight; y+=4){
						for(int x = 0; x < this->m_Map.iCellWidth; x+=4){
							pal[0] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y);
							pal[1] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y);
							pal[2] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y+2);
							pal[3] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y+2);
							buf[i] = this->GetAtb(pal);
							++i;
						}
					}
				}
			}
			break;
			   }
		case 1:{//1:单元格纵向
			for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
				for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
					for(int x = 0; x < this->m_Map.iCellWidth; x+=4){
						for(int y = 0; y < this->m_Map.iCellHeight; y+=4){
							pal[0] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y);
							pal[1] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y);
							pal[2] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y+2);
							pal[3] = this->m_Map.m_pal->GetChr(X*this->m_Map.iCellWidth+x+2, Y*this->m_Map.iCellHeight+y+2);
							buf[i] = this->GetAtb(pal);
							++i;
						}
					}
				}
			}
			break;
			   }
		case 2:{//2:整体横向
			for(int y = 0; y < this->m_Map.iMapHeight; y+=4){
				for(int x = 0; x < this->m_Map.iMapWidth; x+=4){
					pal[0] = this->m_Map.m_pal->GetChr(x, y);
					pal[1] = this->m_Map.m_pal->GetChr(x+2, y);
					pal[2] = this->m_Map.m_pal->GetChr(x, y+2);
					pal[3] = this->m_Map.m_pal->GetChr(x+2, y+2);
					buf[i] = this->GetAtb(pal);
					++i;
				}
			}
			break;
			   }
		case 3:{//3:整体纵向
			for(int x = 0; x < this->m_Map.iMapWidth; x+=4){
				for(int y = 0; y < this->m_Map.iMapHeight; y+=4){
					pal[0] = this->m_Map.m_pal->GetChr(x, y);
					pal[1] = this->m_Map.m_pal->GetChr(x+2, y);
					pal[2] = this->m_Map.m_pal->GetChr(x, y+2);
					pal[3] = this->m_Map.m_pal->GetChr(x+2, y+2);
					buf[i] = this->GetAtb(pal);
					++i;
				}
			}
			break;
			   }
		default:{
			AfxMessageBox("找不到正确的输出方式!!!");
				}
		}
		cf.Write(buf, l);
		delete buf;
		cf.Close();
	}
	CATCH(CFileException, e){
		if(buf)delete buf;
		AfxMessageBox(CString("打开文件") + this->m_sAtbName + CString("时出错!!!"));
	}
	END_CATCH
}

void CFCDoc::SaveChr()
{

}

void CFCDoc::SaveNam()
{
	unsigned char* buf = NULL;
	TRY{
		CFile cf(this->m_sNamName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate);
		UINT l = this->m_Map.GetNamSize();
		buf = new unsigned char[l];
		UINT i = 0;
		switch(this->m_Map.iSaveStyle)
		{
		case 0:{//0:单元格横向
			for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
				for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
					for(int y = 0; y < this->m_Map.iCellHeight; ++y){
						for(int x = 0; x < this->m_Map.iCellWidth; ++x){
							buf[i] = this->m_Map.m_tiles->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y);
							++i;
						}
					}
				}
			}
			break;
			   }
		case 1:{//1:单元格纵向
			for(int X = 0; X < this->m_Map.iMapWidth/this->m_Map.iCellWidth; ++X){
				for(int Y = 0; Y < this->m_Map.iMapHeight/this->m_Map.iCellHeight; ++Y){
					for(int x = 0; x < this->m_Map.iCellWidth; ++x){
						for(int y = 0; y < this->m_Map.iCellHeight; ++y){
							buf[i] = this->m_Map.m_tiles->GetChr(X*this->m_Map.iCellWidth+x, Y*this->m_Map.iCellHeight+y);
							++i;
						}
					}
				}
			}
			break;
			   }
		case 2:{//2:整体横向
			for(int y = 0; y < this->m_Map.iMapHeight; ++y){
				for(int x = 0; x < this->m_Map.iMapWidth; ++x){
					buf[i] = this->m_Map.m_tiles->GetChr(x, y);
					++i;
				}
			}
			break;
			   }
		case 3:{//3:整体纵向
			for(int x = 0; x < this->m_Map.iMapWidth; ++x){
				for(int y = 0; y < this->m_Map.iMapHeight; ++y){
					buf[i] = this->m_Map.m_tiles->GetChr(x, y);
					++i;
				}
			}
			break;
			   }
		default:{
			AfxMessageBox("找不到正确的导入方式!!!");
				}
		}
		cf.Write(buf, l);
		delete buf;		
		cf.Close();
	}
	CATCH(CFileException, e){
		if(buf)delete buf;
		AfxMessageBox(CString("打开文件") + this->m_sNamName + CString("时出错!!!"));
	}
	END_CATCH
}

void CFCDoc::SavePal()
{
	TRY{
		CFile cf(this->m_sColName, CFile::modeWrite | CFile::typeBinary);
		cf.Seek(16*this->m_iColBank, CFile::begin);
		cf.Write(::g_stdpal, 16);
		cf.Close();
	}
	CATCH(CFileException, e){
		AfxMessageBox(CString("打开文件") + this->m_sColName + CString("时出错!!!"));
	}
	END_CATCH
}

BOOL CFCDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{	
	// TODO: Add your specialized creation code here
	CString s = lpszPathName;
	CString s1, s2;
	
	s1 = s.Mid(0, s.ReverseFind('\\'));
	s2 = s.Mid(s.ReverseFind('\\')+1, s.GetLength());
	if(s1 != this->m_sProjectPath || s2 != this->m_sProjectName){
		this->m_sProjectName = s2;
		this->m_sProjectPath = s1;
		SetCurrentDirectory(this->m_sProjectPath);
		this->m_bHaveName = FALSE;
	}
	int i = this->m_sProjectName.ReverseFind('.');
	if(i>=0){
		s = this->m_sProjectName.Mid(0, i);
	}
	else{
		s = this->m_sProjectName;
	}
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return TRUE;
}

void CFCDoc::OnUpdateViewReload(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_bHaveName);
}

void CFCDoc::OnViewReload() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor();
	this->SetChr(this->m_sChrName, this->m_iChrBank);
	this->SetAtb(this->m_sAtbName);
	this->SetNam(this->m_sNamName);
	this->SetPal(this->m_sColName, this->m_iColBank);
	EndWaitCursor();
}

void CFCDoc::OnUpdateSetListen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!this->m_bHaveName)this->m_bListenFile = FALSE;
	pCmdUI->Enable(this->m_bHaveName);
	pCmdUI->SetCheck(this->m_bListenFile);
}

void CFCDoc::OnSetListen() 
{
	// TODO: Add your command handler code here
	if(!this->m_bHaveName)this->m_bListenFile = FALSE;
	else this->m_bListenFile = !this->m_bListenFile;
	if(this->m_bListenFile){
		IgnoreFileTime();
	//	::SetTimer(theApp->, 0x01, 1000, NULL);
		((CMainFrame*)AfxGetMainWnd())->SetListen();
	}
	else{
	//	::KillTimer(NULL, 0x01);
		((CMainFrame*)AfxGetMainWnd())->KillListen();
	}
}

void CFCDoc::IgnoreFileTime()
{
	CFileStatus status;
	CFile::GetStatus(this->m_sChrName, status);
	this->m_tChr = status.m_mtime;
	CFile::GetStatus(this->m_sColName, status);
	this->m_tCol = status.m_mtime;
	CFile::GetStatus(this->m_sAtbName, status);
	this->m_tAtb = status.m_mtime;
	CFile::GetStatus(this->m_sNamName, status);
	this->m_tNam = status.m_mtime;
}

void CFCDoc::CheckFileTime()
{
	TRACE("Check File Time\n");
	CFileStatus status;
	CFile::GetStatus(this->m_sChrName, status);
	BOOL mf = FALSE;
	if(this->m_tChr != status.m_mtime){	//Chr更新
		TRACE("CHR MODIFIED\n");
		this->m_tChr = status.m_mtime;
		this->SetChr(this->m_sChrName, this->m_iChrBank);
		mf = TRUE;
	}
	CFile::GetStatus(this->m_sColName, status);
	if(this->m_tCol != status.m_mtime){	//Col更新
		TRACE("COL MODIFIED\n");
		this->m_tCol = status.m_mtime;
		this->SetPal(this->m_sColName, this->m_iColBank);
		mf = TRUE;
	}
	CFile::GetStatus(this->m_sAtbName, status);
	if(this->m_tAtb != status.m_mtime){	//Atb更新
		TRACE("ATB MODIFIED\n");
		this->m_tAtb = status.m_mtime;
		this->SetAtb(this->m_sAtbName);
		mf = TRUE;
	}
	CFile::GetStatus(this->m_sNamName, status);
	if(this->m_tNam != status.m_mtime){	//Nam更新
		TRACE("NAM MODIFIED\n");
		this->m_tNam = status.m_mtime;
		this->SetNam(this->m_sNamName);
		mf = TRUE;
	}
	SetModifiedFlag(mf);
}
