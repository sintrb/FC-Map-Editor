// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FCµØÍ¼±à¼­Æ÷.h"
#include "Tile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTile::CTile()
{
	this->width = 8;
	this->height = 8;
	this->max_width = 8;
	this->max_height = 8;
	this->data = new unsigned char[64];
	this->fill(0);
}

CTile::CTile(int w, int h)
{
	this->width = w;
	this->height = h;
	this->max_width = w;
	this->max_height = h;
	if(w && h)this->data = new unsigned char[w*h];
	else this->data = NULL;
	this->fill(0);
}


CTile::~CTile()
{
	Destory();
}

inline unsigned char CTile::GetChr(int x, int y)
{
	if(x<width && y<height){
		return data[y*this->max_width+x];
	}
	return 0;
}

inline void CTile::SetChr(int x, int y, unsigned char c)
{
	if(x<width && y<height){
		data[y*this->max_width+x] = c;
	}
}

void CTile::fill(unsigned char c)
{
	for(int i=0; i<this->max_width*this->max_height; ++i){
		this->data[i] = c;
	}
}

void CTile::Destory()
{
	if(data)
		delete this->data;
}

void CTile::SetSize(int x, int y)
{
	if(x <= this->max_width && y <= this->max_height){
		this->width = x;
		this->height = y;
	}
}

void CTile::TileCopy(CTile &tl, int x, int y, int tm)
{
	if(tl.width==0){
		x=x;
	}
	int w = min(tl.width, this->width - x);
	int h = min(tl.height, this->height - y);
	unsigned char c;
	for(int iy = 0; iy < h; ++iy){
		for(int ix = 0; ix < w; ++ix){
			c = tl.GetChr(ix, iy);
			if(c != tm){
				this->SetChr(x + ix, y + iy, c);
			}
		}
	}
}

void CTile::ReSize(int w, int h)
{
	if(w != this->max_width || h != this->max_height){
		CTile* tpt = new CTile(w, h);
		tpt->TileCopy(*this, 0, 0, 0);
		unsigned char* tp = new unsigned char[w*h];
		CopyMemory(tp, tpt->data, w*h);
		delete this->data;
		*this = *tpt;
		this->data = tp;
		delete tpt;
	}
}

void CTile::inf()
{
	TRACE("Size(%d, %d)\n", width, height);
	for(int y=0; y<this->max_height; ++y){
		for(int x=0; x<this->max_width; ++x){
			TRACE("%02x ", GetChr(x,y));
		}
		TRACE("\n");
	}
}

void CTile::fill(int x, int y, int w, int h, unsigned char c)
{
	for(int iy = 0; iy < h; ++iy){
		for(int ix = 0; ix < w; ++ix){
			SetChr(x+ix, y+iy, c);
		}
	}
}

void CTile::fill(int x, int y, int w, int h, CTile& t)
{
	if(t.height!=0 && t.width!=0){
		for(int iy = 0; iy <= (h-t.height); iy += t.height){
			for(int ix = 0; ix <= (w-t.width); ix += t.width){
				TileCopy(t, x+ix, y+iy, ::g_tm);
			}
		}
	}
}

void CTile::fillEx(int x, int y, int w, int h, unsigned char c)
{
	if(w>0 && h>0){
		for(int iy = 0; iy < h; iy += 2){
			for(int ix = 0; ix < w; ix += 2){
				SetChrEx(x+ix, y+iy, c);
			}
		}
	}
}

void CTile::SetChrEx(int x, int y, unsigned char c)
{
	int l = x/2*2;
	int h = y/2*2;
	SetChr(l, h, c);
	SetChr(l+1, h, c);
	SetChr(l, h+1, c);
	SetChr(l+1, h+1, c);
}