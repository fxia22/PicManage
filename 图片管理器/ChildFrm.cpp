
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "图片管理器.h"
#include "图片管理器Doc.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "图片管理器View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//子文档消息映射

	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_LBN_SELCHANGE(ID_PLACE_FOR_LIST, &OnSelchangeMylist)
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


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!listbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!listbar.LoadToolBar(IDR_TOOLBAR_LIST))

	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	listbar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&listbar);

	CRect rect(0,0,120,200);
	//listbar.SetButtonInfo(0,ID_PLACE_FOR_LIST,TBBS_SEPARATOR, 160 ); 
	listbar.Lis.Create (WS_CHILD|WS_VISIBLE|LBS_NOTIFY| WS_VSCROLL | WS_BORDER|WS_HSCROLL|LBS_MULTIPLESEL|LBS_EXTENDEDSEL,rect,&listbar,ID_PLACE_FOR_LIST);
	//listbar.Lis.
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CChildFrame::OnSelchangeMylist(void)
{
	C图片管理器Doc* pDoc =(C图片管理器Doc*) GetActiveDocument();
	int n  = listbar.Lis.GetSelCount();
	int * pt = new int[n];
	listbar.Lis.GetSelItems(n,pt);
	for (int i=0;i<n;i++)
	{
		(pDoc->data)[pt[i]]->selected = true;
	}

	delete [] pt;

	//(pDoc->data)[listbar.Lis.GetCurSel()]->selected =!(pDoc->data)[listbar.Lis.GetCurSel()]->selected;
	//pDoc->UpdateAllViews(NULL);
}
