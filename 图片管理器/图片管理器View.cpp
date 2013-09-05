
// 图片管理器View.cpp : C图片管理器View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "图片管理器.h"
#endif

#include "图片管理器Doc.h"
#include "图片管理器View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C图片管理器View

IMPLEMENT_DYNCREATE(C图片管理器View, CView)

BEGIN_MESSAGE_MAP(C图片管理器View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// C图片管理器View 构造/析构

C图片管理器View::C图片管理器View()
{
	// TODO: 在此处添加构造代码

}

C图片管理器View::~C图片管理器View()
{
}

BOOL C图片管理器View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C图片管理器View 绘制

void C图片管理器View::OnDraw(CDC* /*pDC*/)
{
	C图片管理器Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}


// C图片管理器View 打印

BOOL C图片管理器View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C图片管理器View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C图片管理器View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C图片管理器View 诊断

#ifdef _DEBUG
void C图片管理器View::AssertValid() const
{
	CView::AssertValid();
}

void C图片管理器View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C图片管理器Doc* C图片管理器View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C图片管理器Doc)));
	return (C图片管理器Doc*)m_pDocument;
}
#endif //_DEBUG


// C图片管理器View 消息处理程序
