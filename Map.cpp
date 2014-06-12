// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FC地图编辑器.h"
#include "Map.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap::CMap()
{
	this->iCellHeight = 30;
	this->iCellWidth = 32;
	this->iMapHeight = 30;
	this->iMapWidth = 32;
	this->iTileHeight = 16;
	this->iTileWidth = 16;
	this->iSaveStyle = 2;
	this->bIsChange = TRUE;
	this->m_tiles = new CTile(this->iMapWidth, this->iMapHeight);
	this->m_pal = new CTile(this->iMapWidth, this->iMapHeight);
	this->m_tiles->fill(0);
	this->m_pal->fill(0);
}

CMap::~CMap()
{
	delete this->m_tiles;
	delete this->m_pal;
}

int CMap::GetNamSize()
{
	return this->m_tiles->width * this->m_tiles->height;
}

int CMap::GetAtbSize()
{
	int l=0;
	if(this->iSaveStyle==0 || this->iSaveStyle==1){	//单元格
		int lone = 0;
		lone = ((this->iCellHeight+3)/4)*((this->iCellWidth+3)/4);
		l = (this->iMapHeight/this->iCellHeight)*(this->iMapWidth/this->iCellWidth)*lone;
	}
	else if(this->iSaveStyle==2 || this->iSaveStyle==3){//整体
		l = ((this->iMapHeight+3)/4) * ((this->iMapWidth+3)/4);
	}
	return l;
}

void CMap::SetSize(int mw, int mh, int cw, int ch)
{
	if(mw<1 || mh<1 || cw<1 || ch<1){
		AfxMessageBox("错误的地图尺寸!!!");
	}
	else{
		this->iMapWidth = mw;
		this->iMapHeight = mh;
		this->iCellWidth = cw;
		this->iCellHeight = ch;
		this->m_pal->ReSize(mw, mh);
		this->m_tiles->ReSize(mw, mh);
	}
}

void CMap::OnNew()
{
	SetSize(32, 30, 32, 30);
	this->m_pal->fill(0);
	this->m_tiles->fill(0);
	this->bIsChange = TRUE;
}
