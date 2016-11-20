
// ObjectBrowserDoc.h : interface of the CObjectBrowserDoc class
//


#pragma once

enum { IconBase = 310 };

class CObjectBrowserDoc : public CDocument
{
protected: // create from serialization only
	CObjectBrowserDoc();
	DECLARE_DYNCREATE(CObjectBrowserDoc)

// Attributes
public:
	const CString& GetCurrentFolder() const {
		return m_CurrentFolder;
	}

	void SetCurrentFolder(LPCTSTR path) {
		m_CurrentFolder = path;
	}

	void SetObjectCount(int count) {
		m_Count = count;
	}

	int GetObjectCount() const {
		return m_Count;
	}
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CObjectBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_CurrentFolder;
	int m_Count;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
