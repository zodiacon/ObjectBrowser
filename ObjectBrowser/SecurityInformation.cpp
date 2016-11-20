#include "stdafx.h"
#include "SecurityInformation.h"



CSecurityInformation::~CSecurityInformation() {
}

STDMETHODIMP CSecurityInformation::QueryInterface(_In_ REFIID riid, _Outptr_ void **ppvObj) {
	if(riid == IID_IUnknown || riid == IID_ISecurityInformation)
		return *ppvObj = this, S_OK;
	return E_NOINTERFACE;
}

STDMETHODIMP CSecurityInformation::GetObjectInformation(PSI_OBJECT_INFO pInfo) {
	pInfo->dwFlags = SI_ADVANCED | SI_READONLY;
	pInfo->hInstance = nullptr;
	pInfo->pszPageTitle = nullptr;
	pInfo->pszObjectName = (LPWSTR)(LPCWSTR)m_ObjectName;

	return S_OK;
}

STDMETHODIMP CSecurityInformation::GetAccessRights(const GUID* pguidObjectType,
	DWORD dwFlags, PSI_ACCESS *ppAccess, ULONG *pcAccesses, ULONG *piDefaultAccess) {
	static SI_ACCESS access [] = {
		{ &GUID_NULL, GENERIC_READ, L"Read", SI_ACCESS_GENERAL },
		{ &GUID_NULL, GENERIC_WRITE, L"Write", SI_ACCESS_GENERAL },
		{ &GUID_NULL, GENERIC_EXECUTE, L"Execute", SI_ACCESS_GENERAL },
		{ &GUID_NULL, MUTANT_QUERY_STATE, L"Query State", SI_ACCESS_GENERAL },
		{ &GUID_NULL, EVENT_MODIFY_STATE, L"Modify State", SI_ACCESS_GENERAL },
		{ &GUID_NULL, SYNCHRONIZE, L"Synchronize", SI_ACCESS_GENERAL }
	};

	*ppAccess = access;
	*pcAccesses = 6;
	*piDefaultAccess = 0;

	return S_OK;
}

STDMETHODIMP CSecurityInformation::GetInheritTypes(PSI_INHERIT_TYPE *ppInheritTypes, ULONG *pcInheritTypes) {
	return S_OK;
}

STDMETHODIMP CSecurityInformation::SetSecurity(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor) {
	return E_NOTIMPL;
}

STDMETHODIMP CSecurityInformation::MapGeneric(const GUID *pguidObjectType, UCHAR *pAceFlags, ACCESS_MASK *pMask) {
	return S_OK;

	static GENERIC_MAPPING objMap = {
		MUTANT_QUERY_STATE,
		EVENT_MODIFY_STATE,
		GENERIC_EXECUTE,
		EVENT_ALL_ACCESS,
	};
	MapGenericMask(pMask, &objMap);

	return S_OK;
}

STDMETHODIMP CSecurityInformation::PropertySheetPageCallback(HWND hwnd, UINT uMsg, SI_PAGE_TYPE uPage) {
	return S_OK;
}

STDMETHODIMP CSecurityInformation::GetSecurity(SECURITY_INFORMATION RequestedInformation,
	PSECURITY_DESCRIPTOR *ppSecurityDescriptor, BOOL fDefault) {
	auto code = GetSecurityInfo(m_hObject, SE_KERNEL_OBJECT, RequestedInformation, nullptr, nullptr, nullptr, nullptr, ppSecurityDescriptor);

	return code == 0 ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}
