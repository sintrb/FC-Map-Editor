// FC地图编辑器Doc.h : interface of the CFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FCDOC_H__6737DD48_9650_4F99_8551_44FA18E555DF__INCLUDED_)
#define AFX_FCDOC_H__6737DD48_9650_4F99_8551_44FA18E555DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Map.h"
#include "NESViewChr.h"	// Added by ClassView
#include "Tile.h"	// Added by ClassView


class CFCDoc : public CDocument
{
protected: // create from serialization only
	CFCDoc();
	DECLARE_DYNCREATE(CFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CheckFileTime();
	CTime m_tChr;
	CTime m_tCol;
	CTime m_tAtb;
	CTime m_tNam;
	void IgnoreFileTime();
	BOOL m_bListened;
	BOOL m_bListenFile;
	unsigned char GetAtb(unsigned char* pal);
	void SavePal();
	void SaveNam();
	void SaveChr();
	void SaveAtb();
	inline void GetPal(unsigned char atb, unsigned char *pal);
	void SetAtb(CString fn);
	void SetNam(CString fn);
	void RefresgBmp();
	void RefreshCol();
	void SetPal(CString fn, int index);
	BOOL GetKeyValue(CString& kv, CString& k, CString& v);
	int m_iColBank;
	int m_iChrBank;
	BOOL m_bHaveName;
	CString m_sProjectPath;
	CString m_sProjectName;
	CString m_sColPath;
	CString m_sChrPath;
	void SetChr(CString fn, int index);
	
	CString m_sColName;	//调色
	CString m_sNamName;	//名字表
	CString m_sAtbName;	//属性表
	CString m_sChrName;	//字模
	CMap m_Map;

	virtual ~CFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFCDoc)
	afx_msg void OnUpdateViewReload(CCmdUI* pCmdUI);
	afx_msg void OnViewReload();
	afx_msg void OnUpdateSetListen(CCmdUI* pCmdUI);
	afx_msg void OnSetListen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FCDOC_H__6737DD48_9650_4F99_8551_44FA18E555DF__INCLUDED_)
