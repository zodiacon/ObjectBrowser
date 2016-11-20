#pragma once

class CSecurityInformation : public ISecurityInformation {
public:
	CSecurityInformation(LPCWSTR name, HANDLE hObject) : m_ObjectName(name), m_hObject(hObject) {}
	~CSecurityInformation();

	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObj);
	STDMETHOD_(ULONG, AddRef)() {
		return 2;
	}
	STDMETHOD_(ULONG, Release)() {
		return 1;
	}

	// *** ISecurityInformation methods ***
	STDMETHOD(GetObjectInformation) (PSI_OBJECT_INFO pObjectInfo) ;
	STDMETHOD(GetSecurity) (SECURITY_INFORMATION RequestedInformation,
		PSECURITY_DESCRIPTOR *ppSecurityDescriptor, BOOL fDefault);
	STDMETHOD(SetSecurity) ( SECURITY_INFORMATION SecurityInformation,
		PSECURITY_DESCRIPTOR pSecurityDescriptor) ;
	STDMETHOD(GetAccessRights) ( const GUID* pguidObjectType,
		DWORD dwFlags, // SI_EDIT_AUDITS, SI_EDIT_PROPERTIES
		PSI_ACCESS *ppAccess,
		ULONG *pcAccesses,
		ULONG *piDefaultAccess) ;
	STDMETHOD(MapGeneric) ( const GUID *pguidObjectType,
		UCHAR *pAceFlags,
		ACCESS_MASK *pMask) ;
	STDMETHOD(GetInheritTypes) ( PSI_INHERIT_TYPE *ppInheritTypes,
		ULONG *pcInheritTypes) ;
	STDMETHOD(PropertySheetPageCallback)( HWND hwnd, UINT uMsg, SI_PAGE_TYPE uPage) ;

private:
	CString m_ObjectName;
	HANDLE m_hObject;
};

