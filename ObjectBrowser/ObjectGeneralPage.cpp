// ObjectGeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "ObjectBrowser.h"
#include "ObjectGeneralPage.h"
#include "afxdialogex.h"
#include "Clipboard.h"
#include "NtDll.h"
#include "SecurityInformation.h"

// CObjectGeneralPage dialog

IMPLEMENT_DYNAMIC(CObjectGeneralPage, CPropertyPage)

CObjectGeneralPage::CObjectGeneralPage(LPCWSTR name, CWnd* parent, LPCWSTR type, NT::POBJECT_BASIC_INFORMATION info, HANDLE hObject)
	: CDialogEx(CObjectGeneralPage::IDD, parent), m_ObjectName(name), m_TypeName(type), m_hObject(hObject)
	, m_HandleCount(0), m_RefCount(0), m_NonPagedPool(0), m_PagedPool(0), m_SpecificTitle(_T("")), m_Name1(_T("")), m_Value1(_T("")), m_Name2(_T("")), m_Value2(_T("")) {
	m_pInfo = info;
}

CObjectGeneralPage::~CObjectGeneralPage()
{
}

void CObjectGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_ObjectName);
	DDX_Text(pDX, IDC_TYPE, m_TypeName);
	DDX_Text(pDX, IDC_HANDLES, m_HandleCount);
	DDX_Text(pDX, IDC_REFS, m_RefCount);
	DDX_Text(pDX, IDC_NONPAGEDPOOL, m_NonPagedPool);
	DDX_Text(pDX, IDC_PAGEDPOOL, m_PagedPool);
	DDX_Text(pDX, IDC_SPECIFIC_TITLE, m_SpecificTitle);
	DDX_Text(pDX, IDC_NAME1, m_Name1);
	DDX_Text(pDX, IDC_VALUE1, m_Value1);
	DDX_Text(pDX, IDC_NAME2, m_Name2);
	DDX_Text(pDX, IDC_VALUE2, m_Value2);
}


BEGIN_MESSAGE_MAP(CObjectGeneralPage, CDialogEx)
	ON_BN_CLICKED(IDC_COPY, &CObjectGeneralPage::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_SECURITY, &CObjectGeneralPage::OnBnClickedSecurity)
END_MESSAGE_MAP()

// CObjectGeneralPage message handlers

BOOL CObjectGeneralPage::OnInitDialog() {
	m_HandleCount = m_pInfo->HandleCount - 1;
	m_RefCount = (m_pInfo->ReferenceCount - 1) & 0x7fff;
	m_PagedPool = m_pInfo->PagedPoolUsage;
	m_NonPagedPool = m_pInfo->NonPagedPoolUsage;

	InsertSpecificData();

	CDialogEx::OnInitDialog();
	SetWindowText(m_ObjectName + L" Properties");

	return FALSE;
}

void CObjectGeneralPage::OnBnClickedCopy() {
	CClipboard::SetClipboardData(m_ObjectName);
}

void CObjectGeneralPage::InsertSpecificData() {
	using namespace NT;
	ULONG size;
	if(m_TypeName == L"Event") {
		EVENT_BASIC_INFORMATION info;
		auto status = NtQueryEvent(m_hObject, EventBasicInformation, &info, sizeof(info), &size);
		if(status == 0) {
			m_Name1 = L"Type:"; m_Name2 = "Signaled:";
			m_Value1 = info.EventType == NotificationEvent ? L"Notification (Manual Reset)" : L"Synchronization (Auto Reset)";
			m_Value2 = info.EventState ? L"True" : L"False";
		}
	}
	else if(m_TypeName == L"Mutant") {
		MUTANT_BASIC_INFORMATION info;
		auto status = NtQueryMutant(m_hObject, MutantBasicInformation, &info, sizeof(info), nullptr);
		if(status == 0) {
			m_Name1 = L"Hold Count:"; m_Name2 = L"Abandoned:";
			m_Value1.Format(L"%d", 1 - info.CurrentCount);
			m_Value2 = info.AbandonedState ? L"True" : L"False";
		}
	}
	else if(m_TypeName == L"Semaphore") {
		SEMAPHORE_BASIC_INFORMATION info;
		auto status = NtQuerySemaphore(m_hObject, SemaphoreBasicInfo, &info, sizeof(info), nullptr);
		if(status == 0) {
			m_Name1 = L"Current Count:"; m_Name2 = L"Maximum Count:";
			m_Value1.Format(L"%d", info.CurrentCount);
			m_Value2.Format(L"%d", info.MaximumCount);
		}
	}
	else if(m_TypeName == L"Section") {
		SECTION_BASIC_INFORMATION info;
		auto status = NtQuerySection(m_hObject, SectionBasicInformation, &info, sizeof(info), nullptr);
		if(status == 0) {
			m_Name1 = L"Section Size:"; //m_Name2 = L"Attributes:";
			m_Value1.Format(L"0x%lX", info.SectionSize);
			//m_Value2.Format(L"%X", info.SectionAttributes);
		}
	}
	else
		return;
	m_SpecificTitle = m_TypeName + L" Info";

}


void CObjectGeneralPage::OnBnClickedSecurity() {
	CSecurityInformation secInfo(m_ObjectName, m_hObject);
	::EditSecurity(GetSafeHwnd(), &secInfo);

}
