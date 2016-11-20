
// DirectoryView.h : interface of the CDirectoryView class
//


#pragma once

#include "ObjectManager.h"

class CObjectBrowserDoc;

class CDirectoryView : public CTreeView
{
protected: // create from serialization only
	CDirectoryView();
	DECLARE_DYNCREATE(CDirectoryView)

// Attributes
public:
	CObjectBrowserDoc* GetDocument();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct


// Implementation
public:
	virtual ~CDirectoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_Images;
	HTREEITEM m_hRoot;
	CObjectManager m_Manager;

	void InitFolders(const CString& name, HTREEITEM);
	CString GetPathFromItem(HTREEITEM);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorFolder(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorObjectCount(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in DirectoryView.cpp
inline CObjectBrowserDoc* CDirectoryView::GetDocument()
   { return reinterpret_cast<CObjectBrowserDoc*>(m_pDocument); }
#endif

