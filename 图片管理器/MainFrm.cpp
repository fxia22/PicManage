
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "图片管理器.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_ENABLEDRAW, &CMainFrame::OnEnabledraw)
	ON_COMMAND(ID_DRAW_BRUSH, &CMainFrame::OnDrawBrush)
	ON_COMMAND(ID_DRAW_LINE, &CMainFrame::OnDrawLine)
	ON_COMMAND(ID_DRAW_CIRCLE, &CMainFrame::OnDrawCircle)
	ON_COMMAND(ID_DRAW_ECLIPSE, &CMainFrame::OnDrawEclipse)
	ON_COMMAND(ID_DRAW_RECT, &CMainFrame::OnDrawRect)
	ON_COMMAND(ID_DRAW_CURL, &CMainFrame::OnDrawCurl)
	ON_COMMAND(ID_DRAW_ERASE, &CMainFrame::OnDrawErase)
	ON_COMMAND(ID_DRAW_COLOR, &CMainFrame::OnDrawColor)
	ON_UPDATE_COMMAND_UI(ID_ENABLEDRAW, &CMainFrame::OnUpdateEnabledraw)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH, &CMainFrame::OnUpdateDrawBrush)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMainFrame::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CMainFrame::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ECLIPSE, &CMainFrame::OnUpdateDrawEclipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CMainFrame::OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURL, &CMainFrame::OnUpdateDrawCurl)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ERASE, &CMainFrame::OnUpdateDrawErase)
	ON_UPDATE_COMMAND_UI(ID_DRAW_COLOR, &CMainFrame::OnUpdateDrawColor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STYLE, &CMainFrame::OnUpdateDrawStyle)
	ON_COMMAND(ID_CREATEELE, &CMainFrame::OnCreateele)
	ON_COMMAND(ID_CREATEOBJ, &CMainFrame::OnCreateobj)
	ON_UPDATE_COMMAND_UI(ID_CREATEELE, &CMainFrame::OnUpdateCreateele)
	ON_UPDATE_COMMAND_UI(ID_CREATEOBJ, &CMainFrame::OnUpdateCreateobj)
	ON_COMMAND(ID_VIEW_TOOLBARDRAW, &CMainFrame::OnViewToolbardraw)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBARDRAW, &CMainFrame::OnUpdateViewToolbardraw)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_REGISTERDROP, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBARDRAW))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//DockControlBar(&m_wndToolBar2);
	enabledraw = false;
	viewtoolbar = true;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnEnabledraw()
{
	// TODO: 在此添加命令处理程序代码
	if (!enabledraw)
	MessageBox("EnableDraw");
	else
	MessageBox("DisableDraw");
	enabledraw = !enabledraw;
	drawstatus = enabledraw?DRAW_BRUSH:DRAW_CONNOTDRAW;
	
	
}


void CMainFrame::OnDrawBrush()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_BRUSH;

}



void CMainFrame::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_LINE;
}


void CMainFrame::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_CIRCLE;
}


void CMainFrame::OnDrawEclipse()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_ECLIPSE;
}


void CMainFrame::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_RECT;
}


void CMainFrame::OnDrawCurl()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_CURL;
}


void CMainFrame::OnDrawErase()
{
	// TODO: 在此添加命令处理程序代码
	drawstatus = DRAW_ERASER;
}


void CMainFrame::OnDrawColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	dlg.DoModal();
	
}


void CMainFrame::OnUpdateEnabledraw(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	GetMenu()->GetSubMenu(3)->CheckMenuItem(0,(enabledraw?MF_CHECKED:MF_UNCHECKED)|MF_BYPOSITION);
	if (enabledraw) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}




void CMainFrame::OnUpdateDrawBrush(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(1,((drawstatus==DRAW_BRUSH)?MF_CHECKED:MF_UNCHECKED)|MF_BYPOSITION);
	if (enabledraw&&(drawstatus==DRAW_BRUSH)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);

}


void CMainFrame::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_LINE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_CIRCLE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawEclipse(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_ECLIPSE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_RECT)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawCurl(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_CURL)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawErase(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_ERASER)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawColor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateDrawStyle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnCreateele()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnCreateobj()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateCreateele(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateCreateobj(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnViewToolbardraw()
{
	// TODO: 在此添加命令处理程序代码
	viewtoolbar = !viewtoolbar;
	if (viewtoolbar) ShowControlBar(&m_wndToolBar2,TRUE,FALSE);
	else ShowControlBar(&m_wndToolBar2,FALSE,FALSE);

}


void CMainFrame::OnUpdateViewToolbardraw(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (viewtoolbar) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}
