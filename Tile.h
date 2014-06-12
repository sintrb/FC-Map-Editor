// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__7568AFDB_775C_45FF_9224_8D1F9DD5C931__INCLUDED_)
#define AFX_TILE_H__7568AFDB_775C_45FF_9224_8D1F9DD5C931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTile  
{
public:
	void SetChrEx(int x, int y, unsigned char c);
	void fillEx(int x, int y, int w, int h, unsigned char c);
	void fill(int x, int y, int w, int h, CTile& t);
	void fill(int x, int y, int w, int h, unsigned char c);
	void inf();
	void ReSize(int w, int h);
	void TileCopy(CTile& tl, int x, int y, int tm);
	void SetSize(int x, int y);
	void Destory();
	void fill(unsigned char c);
	virtual void SetChr(int x, int y, unsigned char c);
	inline unsigned char GetChr(int x, int y);
	CTile(int w, int h);
	CTile();
	virtual ~CTile();
	int width;
	int height;
	int max_width;
	int max_height;
	unsigned char* data;
};

#endif // !defined(AFX_TILE_H__7568AFDB_775C_45FF_9224_8D1F9DD5C931__INCLUDED_)
