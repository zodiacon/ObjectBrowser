
// ObjectView.cpp : implementation of the CObjectView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ObjectBrowser.h"
#endif

#pragma comment(lib, "Aclui.lib")

#include "ObjectBrowserDoc.h"
#include "ObjectView.h"
#include "Clipboard.h"
#include "SecurityInformation.h"
#include "ObjectGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CObjectView

IMPLEMENT_DYNCREATE(CObjectView, CListView)

BEGIN_MESSAGE_MAP(CObjectView, CListView)
	ON_WM_STYLECHANGED()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CObjectView::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CObjectView::OnNMRClick)
	ON_NOTIFY_REFLECT(NM_RETURN, &CObjectView::OnNMReturn)
	//ON_NOTIFY(HDN_ITEMCLICKA, 0, &CObjectView::OnHdnItemclick)
	ON_NOTIFY(HDN_ITEMCLICKW, 0, &CObjectView::OnHdnItemclick)
	ON_COMMAND(ID_EDIT_COPY, &CObjectView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CObjectView::OnUpdateEditCopy)
	ON_COMMAND(ID_VIEW_PROPERTIES, &CObjectView::OnViewProperties)
END_MESSAGE_MAP()

// CObjectView construction/destruction

CObjectView::CObjectView() : m_SortColumn(0), m_Ascending(true) {
}

CObjectView::~CObjectView() {
}

BOOL CObjectView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CObjectView::OnInitialUpdate() {
	m_Images.Create(16, 16, ILC_COLOR32, 20, 8);
	for(int i = IconBase; i <= IconBase + 31; i++)
		m_Images.Add(AfxGetApp()->LoadIcon(i));

	m_Images2.Create(32, 32, ILC_COLOR32, 20, 8);
	for(int i = IconBase; i <= IconBase + 31; i++)
		m_Images2.Add(AfxGetApp()->LoadIcon(i));

	m_HeaderImages.Create(16, 16, ILC_COLOR32, 2, 2);
	m_HeaderImages.Add(AfxGetApp()->LoadIcon(IDI_SORT_ASC));
	m_HeaderImages.Add(AfxGetApp()->LoadIcon(IDI_SORT_DESC));
	auto& list = GetListCtrl();
	list.SetImageList(&m_Images, LVSIL_SMALL);
	list.SetImageList(&m_Images2, LVSIL_NORMAL);
	list.InsertColumn(0, m_ColumnNames[0] = L"Name", LVCFMT_LEFT, 400);
	list.InsertColumn(1, m_ColumnNames[1] = L"Type", LVCFMT_LEFT, 150);
	list.InsertColumn(2, m_ColumnNames[2] = L"Link", LVCFMT_LEFT, 400);

	list.ModifyStyle(0, LVS_SORTASCENDING | LVS_REPORT);
	list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list.GetHeaderCtrl()->SetImageList(&m_HeaderImages);
}

// CObjectView diagnostics

#ifdef _DEBUG
void CObjectView::AssertValid() const {
	CListView::AssertValid();
}

void CObjectView::Dump(CDumpContext& dc) const {
	CListView::Dump(dc);
}

CObjectBrowserDoc* CObjectView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObjectBrowserDoc)));
	return (CObjectBrowserDoc*)m_pDocument;
}
#endif //_DEBUG


// CObjectView message handlers
void CObjectView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct) {
	//TODO: add code to react to the user changing the view style of your window	
	CListView::OnStyleChanged(nStyleType, lpStyleStruct);
}

int CALLBACK CObjectView::SortFunction(LPARAM index1, LPARAM index2, LPARAM lParamSort) {
	CObjectView* view = (CObjectView*)lParamSort;
	auto& list = view->GetListCtrl();
	bool asc = view->m_Ascending;
	auto s1 = list.GetItemText((int)index1, view->m_SortColumn);
	auto s2 = list.GetItemText((int)index2, view->m_SortColumn);
	int result = s1.CompareNoCase(s2);
	return asc ? result : -result;
}

void CObjectView::UpdateList() {
	auto& folder = GetDocument()->GetCurrentFolder();
	if(m_CurrentFolder == folder) return;
	m_CurrentFolder = folder;

	CWaitCursor wait;

	auto& list = GetListCtrl();
	list.SetRedraw(FALSE);

	auto items = m_Manager.GetFolders(folder);
	list.LockWindowUpdate();
	list.DeleteAllItems();
	for each(auto item in items) {
		if(item.second != L"Directory") {
			int n = list.InsertItem(list.GetItemCount(), item.first, GetIconIndexFromType(item.second, item.first));
			list.SetItemText(n, 1, item.second);
			if(item.second == L"SymbolicLink") {
				auto link = m_Manager.GetSymbolicLinkFromName(GetDocument()->GetCurrentFolder(), item.first);
				list.SetItemText(n, 2, link);
			}
		}
	}
	list.SortItemsEx(SortFunction, (DWORD_PTR)this);
	list.UnlockWindowUpdate();
	list.SetRedraw();

	GetDocument()->SetObjectCount(list.GetItemCount());
}

void CObjectView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) {
	UpdateList();
}

int CObjectView::GetIconIndexFromType(const CString& name, const CString& object) const {
	if(name == L"Type" && object != L"Type") {
		int index = GetIconIndexFromType(object, L"");
		if(index == IDI_GEAR - IconBase)
			index = IDI_MOLECULE - IconBase;
		return index;
	}

	static struct {
		CString Name;
		int IconId;
	} names [] = {
		{ L"Thread", IDI_THREAD },
		{ L"Mutant", IDI_LOCK },
		{ L"Timer", IDI_CLOCK },
		{ L"SymbolicLink", IDI_UNDO },
		{ L"Semaphore", IDI_TRAFFIC_LIGHT },
		{ L"Section", IDI_CPU },
		{ L"Device", IDI_PCI_CARD },
		{ L"Event", IDI_FLASH },
		{ L"Type", IDI_MOLECULE },
		{ L"Process", IDI_GEARS },
		{ L"Key", IDI_KEY },
		{ L"Job", IDI_FACTORY },
		{ L"Driver", IDI_CAR },
		{ L"Desktop", IDI_DESKTOP },
		{ L"WindowStation", IDI_WORKSTATION },
		{ L"Directory", IDI_FOLDER_CLOSED },
		{ L"File", IDI_FLOPPY },
		{ L"PowerRequest", IDI_PLUG },
		{ L"Session", IDI_LIGHT_BULB_ON }
	};
	for(int i = 0; i < _countof(names); i++) {
		if(name == names[i].Name)
			return names[i].IconId - IconBase;
	}
	return IDI_GEAR - IconBase;

}


void CObjectView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(GetListCtrl().GetSelectedCount() > 0)
		OnViewProperties();
	*pResult = 0;
}


void CObjectView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	auto& list = GetListCtrl();
	if(list.GetSelectedCount() == 0) return;

	CMenu menu;
	menu.LoadMenu(IDR_POPUP);
	CPoint pt;
	::GetCursorPos(&pt);
	menu.GetSubMenu(0)->TrackPopupMenu(0, pt.x, pt.y, this);

	*pResult = 0;
}


void CObjectView::OnNMReturn(NMHDR *pNMHDR, LRESULT *pResult) {
	if(GetListCtrl().GetSelectedCount() > 0)
		OnViewProperties();
	*pResult = 0;
}


void CObjectView::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	int old = m_SortColumn;
	if(m_SortColumn == phdr->iItem) {
		m_Ascending = !m_Ascending;
	}
	else {
		m_SortColumn = phdr->iItem;
		m_Ascending = true;
	}
	SetSortImage(old);
	GetListCtrl().SortItemsEx(SortFunction, (DWORD_PTR)this);
	*pResult = 0;
}

void CObjectView::SetSortImage(int old) {
	auto header = GetListCtrl().GetHeaderCtrl();
	HDITEM item;
	if(old >= 0) {
		//item.mask = 0;
		//header->GetItem(old, &item);
		item.fmt = HDF_STRING;
		item.mask = HDI_TEXT | HDI_IMAGE;
		item.iImage = -1;
		item.pszText = (LPWSTR)(LPCWSTR)m_ColumnNames[old];
		header->SetItem(old, &item);
	}
	header->GetItem(m_SortColumn, &item);
	item.fmt |= HDF_IMAGE | HDF_BITMAP_ON_RIGHT | HDF_STRING;
	item.mask |= HDI_FORMAT | HDI_IMAGE | HDI_TEXT;
	item.pszText = (LPWSTR)(LPCWSTR)m_ColumnNames[m_SortColumn];
	item.iImage = m_Ascending ? 0 : 1;
	header->SetItem(m_SortColumn, &item);

}

void CObjectView::OnEditCopy() {
	auto& list = GetListCtrl();
	auto pos = list.GetFirstSelectedItemPosition();
	int item = list.GetNextSelectedItem(pos);
	auto text = list.GetItemText(item, 0);
	CClipboard::SetClipboardData(text);
}


void CObjectView::OnUpdateEditCopy(CCmdUI *pCmdUI) {
	pCmdUI->Enable(GetListCtrl().GetSelectedCount() > 0);
}

void CObjectView::OnViewProperties() {
	using namespace NT;
	auto& list = GetListCtrl();
	auto pos = list.GetFirstSelectedItemPosition();
	CString fullname = GetDocument()->GetCurrentFolder(), name;
	if(fullname != L"\\")
		fullname += L"\\";
	int index;
	fullname += (name = list.GetItemText(index = list.GetNextSelectedItem(pos), 0));
	CString type;
	HANDLE hObject = m_Manager.OpenObject(fullname, STANDARD_RIGHTS_READ | 1, type = list.GetItemText(index, 1));
	if(!hObject) {
		AfxMessageBox(L"Failed to open object.");
		return;
	}
	OBJECT_BASIC_INFORMATION info;
	ULONG size;
	NtQueryObject(hObject, ObjectBasicInformation, &info, sizeof(info), &size);

	CObjectGeneralPage dlg(name, this, type, &info, hObject);
	dlg.DoModal();
	
	CloseHandle(hObject);
}

