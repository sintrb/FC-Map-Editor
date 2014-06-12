// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__BA68CEEC_2B18_4C48_AA03_7C2CD1B1A676__INCLUDED_)
#define AFX_MAP_H__BA68CEEC_2B18_4C48_AA03_7C2CD1B1A676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Tile.h"
class CMap  
{
public:
	void OnNew();
	void SetSize(int mw, int mh, int cw, int ch);
	int GetAtbSize();
	int GetNamSize();

	int iMapWidth;
	int iMapHeight;
	int iCellWidth;
	int iCellHeight;
	int iTileWidth;
	int iTileHeight;
	CTile* m_pal;	//属性表
	CTile* m_tiles;	//名字表
	BOOL bIsChange;
	int iSaveStyle;
	//0:单元格横向
	//1:单元格纵向
	//2:整体横向
	//3:整体纵向
	CMap();
	virtual ~CMap();

};

#endif // !defined(AFX_MAP_H__BA68CEEC_2B18_4C48_AA03_7C2CD1B1A676__INCLUDED_)
