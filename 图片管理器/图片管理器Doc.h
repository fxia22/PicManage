
// ͼƬ������Doc.h : CͼƬ������Doc ��Ľӿ�
//


#pragma once
#include "Line.h"
#include <vector>

using namespace std;
class CͼƬ������Doc : public CDocument
{
protected: // �������л�����
	CͼƬ������Doc();
	DECLARE_DYNCREATE(CͼƬ������Doc)

// ����
public:
		vector<MyObject*> data;//���ڱ���������Ҫ���Ƶ�ֱ��
		COLORREF m_bkgclr;
		// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CͼƬ������Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP();


//�Լ�����ı���


#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileUpdate();
};
