#include "stdafx.h"
#include "Clipboard.h"


bool CClipboard::SetClipboardData(const CString& text) {
	if(!::OpenClipboard(AfxGetMainWnd()->GetSafeHwnd()))
		return false;
	::EmptyClipboard();
	HGLOBAL h = ::GlobalAlloc(GMEM_MOVEABLE, (text.GetLength() + 1) * sizeof(TCHAR));
	LPTSTR pString = (LPTSTR)GlobalLock(h);
	lstrcpy(pString, text);
	::GlobalUnlock(h);
	::SetClipboardData(CF_UNICODETEXT, h);
	::CloseClipboard();
	return true;
}