
// ͼƬ������View.h : CͼƬ������View ��Ľӿ�
//

#pragma once
using namespace std;

class CͼƬ������View : public CView
{
	enum
	{
		DRAW_CONNOTDRAW,
		DRAW_LINE,
		DRAW_BRUSH,
		DRAW_CIRCLE,
		DRAW_ECLIPSE,
		DRAW_RECT,
		DRAW_CURL,
		DRAW_ERASER
	};
protected: // �������л�����
	CͼƬ������View();
	DECLARE_DYNCREATE(CͼƬ������View)

// ����
public:
	CͼƬ������Doc* GetDocument() const;

// ����
public:
	CRect m_client;
	CPoint m_pre_point;
//	Line* tmp;
	//���ڸ���������Ϣ
//	vector<Line*> data;
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
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	MyObject* tmp;
	bool SaveBitmap(HBITMAP  Bipmap, char* filename);
	bool SaveCurrentImage(char* filename);
};

#ifndef _DEBUG  // ͼƬ������View.cpp �еĵ��԰汾
inline CͼƬ������Doc* CͼƬ������View::GetDocument() const
   { return reinterpret_cast<CͼƬ������Doc*>(m_pDocument); }
#endif

