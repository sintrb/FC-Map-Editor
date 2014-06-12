// DiyChr.h: interface for the CDiyChr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIYCHR_H__2622494D_EF1A_4542_92E1_F73762B36FD9__INCLUDED_)
#define AFX_DIYCHR_H__2622494D_EF1A_4542_92E1_F73762B36FD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DIY_W	16
#define DIY_H	16


class CDiyChr
{
public:
	CBitmap m_bmp;
	unsigned char map[DIY_H][DIY_W];
	CDiyChr();
	virtual ~CDiyChr();
};

#endif // !defined(AFX_DIYCHR_H__2622494D_EF1A_4542_92E1_F73762B36FD9__INCLUDED_)
