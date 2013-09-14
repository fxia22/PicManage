
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "ͼƬ������Doc.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "ͼƬ������View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//���ĵ���Ϣӳ��

	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_LBN_SELCHANGE(ID_PLACE_FOR_LIST, &OnSelchangeMylist)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	CMainFrame* pmain = (CMainFrame*)AfxGetMainWnd();
	pmain->m_ChildFramePtrList.AddHead( this );
	
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_MINIMIZEBOX;
	cs.lpszClass = AfxRegisterWndClass(0);
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

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

// CChildFrame ��Ϣ�������


void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (!((CͼƬ������Doc*)GetActiveDocument())->IsEmpty())
		{
			if (MessageBox("��û�б��棬ȷ��Ҫ�˳���",((CͼƬ������Doc*)GetActiveDocument())->GetTitle(),MB_OKCANCEL)==IDOK);
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	listbar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&listbar);

	CRect rect(0,0,120,200);
	//listbar.SetButtonInfo(0,ID_PLACE_FOR_LIST,TBBS_SEPARATOR, 160 ); 
	listbar.Lis.Create (WS_CHILD|WS_VISIBLE|LBS_NOTIFY| WS_VSCROLL | WS_BORDER|WS_HSCROLL|LBS_MULTIPLESEL|LBS_EXTENDEDSEL,rect,&listbar,ID_PLACE_FOR_LIST);
	//listbar.Lis.
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CChildFrame::OnSelchangeMylist(void)
{
	CͼƬ������Doc* pDoc =(CͼƬ������Doc*) GetActiveDocument();
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
