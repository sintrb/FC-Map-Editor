// ClipboardData.h: interface for the CClipboardData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDDATA_H__5558C810_F5C7_43B0_BDE8_9F927CD8D41C__INCLUDED_)
#define AFX_CLIPBOARDDATA_H__5558C810_F5C7_43B0_BDE8_9F927CD8D41C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct CClipboardData
{
public:
	CClipboardData();
	virtual ~CClipboardData();
	int width;
	int height;
}CClipboardData;

#endif // !defined(AFX_CLIPBOARDDATA_H__5558C810_F5C7_43B0_BDE8_9F927CD8D41C__INCLUDED_)
