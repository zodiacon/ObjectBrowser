
// ObjectView.h : interface of the CObjectView class
//

#pragma once

#include "ObjectManager.h"

class CObjectView : public CListView {
protected: // create from serialization only
	CObjectView();
	DECLARE_DYNCREATE(CObjectView)

	// Attributes
public:
	CObjectBrowserDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

	// Implementation
public:
	virtual ~CObjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_Images, m_Images2, m_HeaderImages;
	CObjectManager m_Manager;
	CString m_CurrentFolder;
	int m_SortColumn;
	bool m_Ascending;
	CString m_ColumnNames[3];

	// Generated message map functions
protected:
	void UpdateList();
	static int CALLBACK SortFunction(LPARAM index1, LPARAM index2, LPARAM lParamSort);
	int GetIconIndexFromType(const CString&, const CString&) const;
	void SetSortImage(int old);

	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	//	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReturn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	//	afx_msg void OnUpdateIndicatorObjectcount(CCmdUI *pCmdUI);
	afx_msg void OnViewProperties();
};

#ifndef _DEBUG  // debug version in ObjectView.cpp
inline CObjectBrowserDoc* CObjectView::GetDocument() const
{ return reinterpret_cast<CObjectBrowserDoc*>(m_pDocument); }
#endif

