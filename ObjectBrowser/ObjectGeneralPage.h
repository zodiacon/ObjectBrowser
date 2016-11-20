#pragma once

#include "NtDll.h"

// CObjectGeneralPage dialog

class CObjectGeneralPage : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectGeneralPage)

public:
	CObjectGeneralPage(LPCWSTR name, CWnd* parent, LPCWSTR type, NT::POBJECT_BASIC_INFORMATION, HANDLE hObject);
	virtual ~CObjectGeneralPage();

// Dialog Data
	enum { IDD = IDD_OBJECT_GENERAL };

protected:
	NT::POBJECT_BASIC_INFORMATION m_pInfo;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InsertSpecificData();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CString m_ObjectName;
	CString m_TypeName;
	int m_HandleCount;
	int m_RefCount;
	HANDLE m_hObject;
public:
	afx_msg void OnEnSetfocusName();
	afx_msg void OnBnClickedCopy();
private:
	int m_NonPagedPool;
	int m_PagedPool;
	CString m_SpecificTitle;
public:
	CString m_Name1;
	CString m_Value1;
	CString m_Name2;
	CString m_Value2;
	afx_msg void OnBnClickedSecurity();
};
