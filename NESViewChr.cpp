// NESViewChr.cpp: implementation of the CNESViewChr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NESViewChr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNESViewChr::CNESViewChr()
{
	this->m_bmpbuf = NULL;
	this->m_datbuf = NULL;
//	this->m_bmpbufbk = NULL;
	this->m_col[0] = 0x00000000;
	this->m_col[1] = 0x000000ff;
	this->m_col[2] = 0x0000ff00;
	this->m_col[3] = 0x00ff0000;
	SetMul(2);
}

CNESViewChr::CNESViewChr(int mul)
{
	this->m_bmpbuf = NULL;
	this->m_datbuf = NULL;
//	this->m_bmpbufbk = NULL;
	this->m_col[0] = 0x00000000;
	this->m_col[1] = 0x000000ff;
	this->m_col[2] = 0x0000ff00;
	this->m_col[3] = 0xff000000;
	SetMul(mul);
}

void CNESViewChr::SetMul(int n)
{
	if(this->m_bmpbuf)delete this->m_bmpbuf;
	if(this->m_datbuf)delete this->m_datbuf;
//	if(this->m_bmpbufbk)delete this->m_bmpbufbk;
	this->m_mul = n;
	this->m_bmpbuf = new COLORREF[16*16*8*8*2*this->m_mul*this->m_mul];
//	this->m_bmpbufbk = new COLORREF[16*16*8*8*2*this->m_mul*this->m_mul];
	this->m_datbuf = new unsigned char[0x1000];
	ZeroMemory(this->m_datbuf, 0x1000);
	this->m_SingleH = 8*this->m_mul;
	this->m_SingleW = 8*this->m_mul;
	this->m_TotalH = this->m_SingleH*16;
	this->m_TotalW = this->m_SingleW*16;
}

CNESViewChr::~CNESViewChr()
{
	if(this->m_bmpbuf)delete this->m_bmpbuf;
	if(this->m_datbuf)delete this->m_datbuf;
	//if(this->m_bmpbufbk)delete this->m_bmpbufbk;
}

void CNESViewChr::RefreshPicture(unsigned char *dat, COLORREF *pal)
{
	::memcpy(this->m_datbuf, dat, sizeof(unsigned char)*0x1000);
	SetPal(pal);
}

inline void CNESViewChr::GetChr(int x, int y, int n, unsigned char &h, unsigned char &l)
{
	int i = y*16*16+x*16+n;
	h = m_datbuf[i];
	l = m_datbuf[i+8];
}

inline void CNESViewChr::SetMap(int X, int Y, int x, int y, COLORREF col)
{
	SetMap(X*8+x, this->m_mul*(Y*8+y), col);
}

inline void CNESViewChr::SetMap(int x, int y, COLORREF col)
{
	for(int iy=0; iy<this->m_mul; ++iy){
		for(int ix=0; ix<this->m_mul; ++ix){
			SetAbs(x*this->m_mul+ix, this->m_mul*(y+iy), col);
		}
	}
}

inline void CNESViewChr::SetAbs(int x, int y, COLORREF col)
{
	m_bmpbuf[y*8*16+x] = col;
}


void CNESViewChr::RefreshPicture()
{
	unsigned char h;
	unsigned char l;
	
	for(int Y=0; Y<16; ++Y){
		for(int X=0; X<16; ++X){
			for(int y=0; y<8; ++y){
				GetChr(X,Y,y,h,l);
				for(int x=0; x<8; ++x){
					if(h&0x80 && l&0x80)
						SetMap(X,Y,x,y,m_col[3]);
					else if(l&0x80)
						SetMap(X,Y,x,y,m_col[2]);
					else if(h&0x80)
						SetMap(X,Y,x,y,m_col[1]);
					else
						SetMap(X,Y,x,y,m_col[0]);
					h <<= 1;
					l <<= 1;
				}
			}
		}
	}
	m_bmp.DeleteObject();
	//CopyMemory(this->m_bmpbufbk, this->m_bmpbuf, 16*16*8*8*2*this->m_mul*this->m_mul);
	this->m_bmp.CreateBitmap(this->m_TotalW, this->m_TotalH,1,0x20,this->m_bmpbuf);
}


void CNESViewChr::SetPal(COLORREF *pal)
{
	this->m_col[0] = SwitchCol(pal[0]);
	this->m_col[1] = SwitchCol(pal[1]);
	this->m_col[2] = SwitchCol(pal[2]);
	this->m_col[3] = SwitchCol(pal[3]);
	this->RefreshPicture();
}

void CNESViewChr::SetBuf(unsigned char *buf)
{
	::memcpy(this->m_datbuf, buf, sizeof(unsigned char)*0x1000);
	this->RefreshPicture();
}

COLORREF CNESViewChr::SwitchCol(COLORREF col)
{
	COLORREF color = 0x00;
	color = RGB((col>>16)&0xff, (col>>8)&0xff, col&0xff);
	return color;
}

COLORREF* CNESViewChr::GetTileBmp(int x, int y, COLORREF* bmpbuf)
{
	return bmpbuf;
}

COLORREF* CNESViewChr::GetTileBmp(int index, COLORREF* tpbmpbuf)
{
	return this->GetTileBmp(index%16, index/16, tpbmpbuf);
}
