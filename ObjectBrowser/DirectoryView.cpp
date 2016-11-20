
// DirectoryView.cpp : implementation of the CDirectoryView class
//

#include "stdafx.h"
#include "ObjectBrowser.h"
#include "ObjectBrowserDoc.h"
#include "DirectoryView.h"
#include "Clipboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectoryView

IMPLEMENT_DYNCREATE(CDirectoryView, CTreeView)

BEGIN_MESSAGE_MAP(CDirectoryView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDirectoryView::OnTvnItemChanged)
	ON_COMMAND(ID_EDIT_COPY, &CDirectoryView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CDirectoryView::OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLDER, &CDirectoryView::OnUpdateIndicatorFolder)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OBJECTCOUNT, &CDirectoryView::OnUpdateIndicatorObjectCount)
END_MESSAGE_MAP()


// CDirectoryView construction/destruction

CDirectoryView::CDirectoryView() {
	// TODO: add construction code here
}

CDirectoryView::~CDirectoryView() {
}

BOOL CDirectoryView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CDirectoryView::OnInitialUpdate() {
	//	CTreeView::OnInitialUpdate();

	m_Images.Create(16, 16, ILC_COLOR32, 16, 4);
	for(int i = IconBase; i <= IconBase + 12; i++)
		m_Images.Add(AfxGetApp()->LoadIcon(i));

	auto& tree = GetTreeCtrl();
	tree.ModifyStyle(0, TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_SHOWSELALWAYS);
	tree.SetImageList(&m_Images, TVSIL_NORMAL);
	m_hRoot = tree.InsertItem(L"\\", IDI_FOLDER_OPEN - IconBase, IDI_FOLDER_OPEN - IconBase);

	InitFolders(L"\\", m_hRoot);
	tree.SortChildren(m_hRoot);
	tree.Expand(m_hRoot, TVE_EXPAND);

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}


// CDirectoryView diagnostics

#ifdef _DEBUG
void CDirectoryView::AssertValid() const {
	CTreeView::AssertValid();
}

void CDirectoryView::Dump(CDumpContext& dc) const {
	CTreeView::Dump(dc);
}

CObjectBrowserDoc* CDirectoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObjectBrowserDoc)));
	return (CObjectBrowserDoc*)m_pDocument;
}
#endif //_DEBUG


void CDirectoryView::InitFolders(const CString& root, HTREEITEM hParent) {
	auto items = m_Manager.GetFolders(root);
	auto& tree = GetTreeCtrl();
	for each(auto item in items) {
		if(item.second == L"Directory") {
			auto hItem = tree.InsertItem(item.first, IDI_FOLDER_CLOSED - IconBase, IDI_FOLDER_OPEN - IconBase, hParent);
			if(root == L"\\")
				InitFolders(root + item.first, hItem);
			else
				InitFolders(root + L"\\" + item.first, hItem);
			tree.SortChildren(hItem);
		}
	}
}

void CDirectoryView::OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult) {

	GetDocument()->SetCurrentFolder(GetPathFromItem(GetTreeCtrl().GetSelectedItem()));
	GetDocument()->UpdateAllViews(this);

	*pResult = 0;
}

CString CDirectoryView::GetPathFromItem(HTREEITEM hItem) {
	CString path;
	while(hItem != m_hRoot) {
		path = GetTreeCtrl().GetItemText(hItem) + (path.IsEmpty() ? L"" : (L"\\" + path));
		hItem = GetTreeCtrl().GetParentItem(hItem);
	}
	return L"\\" + path;
}

void CDirectoryView::OnEditCopy() {
	auto item = GetTreeCtrl().GetSelectedItem();
	CClipboard::SetClipboardData(GetTreeCtrl().GetItemText(item));
}

void CDirectoryView::OnUpdateEditCopy(CCmdUI *pCmdUI) {
	pCmdUI->Enable(GetTreeCtrl().GetSelectedCount() > 0);
}

void CDirectoryView::OnUpdateIndicatorFolder(CCmdUI *pCmdUI) {
	pCmdUI->SetText(L"Current Directory: " + GetDocument()->GetCurrentFolder());
}

void CDirectoryView::OnUpdateIndicatorObjectCount(CCmdUI *pCmdUI) {
	CString count;
	count.Format(L"Objects: %d", GetDocument()->GetObjectCount());
	pCmdUI->SetText(count);
}