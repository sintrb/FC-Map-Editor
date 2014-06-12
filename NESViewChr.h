// NESViewChr.h: interface for the CNESViewChr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NESVIEWCHR_H__AB7E5518_B217_444B_9E4A_FEF062C159E6__INCLUDED_)
#define AFX_NESVIEWCHR_H__AB7E5518_B217_444B_9E4A_FEF062C159E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNESViewChr
{
public:
	COLORREF* GetTileBmp(int index, COLORREF* tpbmpbuf);
	COLORREF* GetTileBmp(int x, int y, COLORREF* tpbmpbuf);
	COLORREF SwitchCol(COLORREF col);
	void SetBuf(unsigned char *buf);
	void SetPal(COLORREF *pal);
	void SetMul(int n);
	CNESViewChr(int mul);
	inline void SetAbs(int x, int y, COLORREF col);
	int m_mul;
	int m_SingleH;
	int m_SingleW;
	int m_TotalH;
	int m_TotalW;
	void RefreshPicture();
	inline void SetMap(int x, int y, COLORREF col);
	inline void SetMap(int X, int Y, int x, int y, COLORREF col);
	inline void GetChr(int x, int y, int n, unsigned char& h, unsigned char& l);
	void RefreshPicture(unsigned char* dat, COLORREF* pal);
	COLORREF* m_bmpbuf;
//	COLORREF* m_bmpbufbk;
	unsigned char* m_datbuf;
	COLORREF m_col[4];
	CBitmap m_bmp;
	CNESViewChr();
	virtual ~CNESViewChr();
};

#endif // !defined(AFX_NESVIEWCHR_H__AB7E5518_B217_444B_9E4A_FEF062C159E6__INCLUDED_)
