
// ͼƬ������View.h : CͼƬ������View ��Ľӿ�
//

#pragma once


class CͼƬ������View : public CView
{
protected: // �������л�����
	CͼƬ������View();
	DECLARE_DYNCREATE(CͼƬ������View)

// ����
public:
	CͼƬ������Doc* GetDocument() const;

// ����
public:
	CRect m_client;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CͼƬ������View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ͼƬ������View.cpp �еĵ��԰汾
inline CͼƬ������Doc* CͼƬ������View::GetDocument() const
   { return reinterpret_cast<CͼƬ������Doc*>(m_pDocument); }
#endif

