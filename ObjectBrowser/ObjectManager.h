#pragma once

#include "NtDll.h"

class CObjectManager {
public:
	CObjectManager();
	~CObjectManager();

	vector<pair<CString, CString>> GetFolders(const CString& root);
	CString GetSymbolicLinkFromName(const CString& directory, const CString& name) const;

	HANDLE OpenObject(const CString& name, ULONG access, const CString& type, NT::NTSTATUS* pStatus = nullptr);

private:
	unsigned _size;
	NT::POBJECT_DIRECTORY_INFORMATION _buffer;
};

