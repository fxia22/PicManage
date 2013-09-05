
// 图片管理器View.h : C图片管理器View 类的接口
//

#pragma once


class C图片管理器View : public CView
{
protected: // 仅从序列化创建
	C图片管理器View();
	DECLARE_DYNCREATE(C图片管理器View)

// 特性
public:
	C图片管理器Doc* GetDocument() const;

// 操作
public:
	CRect m_client;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C图片管理器View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 图片管理器View.cpp 中的调试版本
inline C图片管理器Doc* C图片管理器View::GetDocument() const
   { return reinterpret_cast<C图片管理器Doc*>(m_pDocument); }
#endif

