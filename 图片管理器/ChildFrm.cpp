
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "图片管理器.h"
#include "图片管理器Doc.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//子文档消息映射

	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	CMainFrame* pmain = (CMainFrame*)AfxGetMainWnd();
	pmain->m_ChildFramePtrList.AddHead( this );
	
	// TODO: 在此添加成员初始化代码
	}

CChildFrame::~CChildFrame()
{
	CMainFrame* pmain = (CMainFrame*)AfxGetMainWnd();
	POSITION pos = pmain->m_ChildFramePtrList.Find( this );
	if ( pos != NULL )
	{
		pmain->m_ChildFramePtrList.RemoveAt( pos );
	}
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_MINIMIZEBOX;
	cs.lpszClass = AfxRegisterWndClass(0);
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


void CChildFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (!((C图片管理器Doc*)GetActiveDocument())->IsEmpty())
		{
			if (MessageBox("您没有保存，确定要退出吗",((C图片管理器Doc*)GetActiveDocument())->GetTitle(),MB_OKCANCEL)==IDOK);
			else return ;
	}
	CMDIChildWnd::OnClose();
}


void CChildFrame::ExitWithoutQuery(void)
{
		CMDIChildWnd::OnClose();
}
