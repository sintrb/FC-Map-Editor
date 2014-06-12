// FCµØÍ¼±à¼­Æ÷.h : main header file for the FCµØÍ¼±à¼­Æ÷ application
//

#if !defined(AFX_FC_H__BC734FF6_2AD4_4394_9DC2_AE07F40781D6__INCLUDED_)
#define AFX_FC_H__BC734FF6_2AD4_4394_9DC2_AE07F40781D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "NESViewChr.h"
#include "Tile.h"
/////////////////////////////////////////////////////////////////////////////
// CFCApp:
// See FCµØÍ¼±à¼­Æ÷.cpp for the implementation of this class
//
extern int g_iNowSelPal;
extern CNESViewChr g_chrBmps[4];
extern COLORREF g_pal[16];
extern COLORREF g_stdcol[0x40];
extern unsigned char g_stdpal[16];
extern CTile g_selTl;
extern int g_tm;
class CFCApp : public CWinApp
{
public:
	CFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FC_H__BC734FF6_2AD4_4394_9DC2_AE07F40781D6__INCLUDED_)
