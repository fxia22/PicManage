
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "MainFrm.h"
#include "ͼƬ������Doc.h"
#include "ͼƬ������View.h"
#include "StyleDlg.h"
#include "MyLine.h"
#include "Adomdb.h"
#include "MyRectangle.h"
#include "ChildFrm.h"
#include "MyCircle.h"
#include "MyEllipse.h"
#include "FilesearchDlg.h"
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
	
	ON_UPDATE_COMMAND_UI(ID_CALLADMIN, &CMainFrame::OnUpdateCalladmin)
	ON_COMMAND(ID_DRAW_BKGCOLOR, &CMainFrame::OnDrawBkgcolor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BKGCOLOR, &CMainFrame::OnUpdateDrawBkgcolor)
	ON_COMMAND(ID_DRAW_STYLE, &CMainFrame::OnDrawStyle)
	ON_MESSAGE(ID_RETURN_PRESSED, OnReturnPressed)
	ON_MESSAGE(ID_CONTENT_CHANGE, OnContentChange)
	ON_COMMAND(ID_COMMAND_SET, &CMainFrame::OnCommandSet)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMainFrame::OnUpdateEditUndo)
//	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
ON_WM_CLOSE()
ON_COMMAND(ID_DRAW_MOVE, &CMainFrame::OnDrawMove)
ON_UPDATE_COMMAND_UI(ID_DRAW_MOVE, &CMainFrame::OnUpdateDrawMove)
ON_COMMAND(ID_FILESEARCH, &CMainFrame::OnFilesearch)

ON_COMMAND(ID_DRAW_SELECT, &CMainFrame::OnDrawSelect)
ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, &CMainFrame::OnUpdateDrawSelect)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_clr= RGB(0,255,255);
	m_nLineStyle = PS_SOLID;
	m_nLineWidth = 1;
	m_bkgclr = RGB(255,255,255);
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*if(!m_wndClient.SubclassWindow(m_hWndMDIClient)) 

	{ 
		TRACE("Fail to subclass MDI client window/n"); 
		return -1; 
	} 
	*/

	




	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_REGISTERDROP, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBARDRAW))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_CmdBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_CmdBar.LoadToolBar(IDR_TOOLBAR_CMD))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	m_CmdBar.EnableDocking(CBRS_ALIGN_ANY);


	EnableDocking(CBRS_ALIGN_ANY);
	
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBar2);
	DockControlBar(&m_CmdBar);
	

	m_CmdBar.SetButtonInfo(0, ID_BAR_STATIC1, TBBS_SEPARATOR, 160 ); 
	if(!m_CmdBar.m_Static1.Create ("����Ԫ��:",WS_CHILD|WS_VISIBLE,CRect(0,0,100,25), &m_CmdBar, ID_BAR_STATIC1))
		return -1;
	m_CmdBar.SetButtonInfo(1, ID_BAR_EDIT1, TBBS_SEPARATOR, 160 ); 
	if(!m_CmdBar.m_Edit1.Create (WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER,CRect(100,0,360,22), &m_CmdBar, ID_BAR_EDIT1))
		return -1;
	m_CmdBar.SetButtonInfo(2, ID_BAR_STATIC2, TBBS_SEPARATOR, 320 ); 
	if(!m_CmdBar.m_Static2.Create ("��������:",WS_CHILD|WS_VISIBLE,CRect(400,0,500,25), &m_CmdBar, ID_BAR_STATIC2))
		return -1;
	m_CmdBar.SetButtonInfo(3, ID_BAR_EDIT2, TBBS_SEPARATOR, 120 ); 
	if(!m_CmdBar.m_Edit2.Create (WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER,CRect(500,0,760,22), &m_CmdBar, ID_BAR_EDIT2))
		return -1;
	
	
	//m_myListBox.Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD|WS_HSCROLL, 
	
		//CRect(10,10,200,200), pParentWnd, IDC_MYLISTBOX)
		



	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	 
	enabledraw = false;
	viewtoolbar = true;
	//�����༭��
	
	


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



void CMainFrame::OnEnabledraw()
{
	// TODO: �ڴ���������������
	enabledraw = !enabledraw;
	drawstatus = enabledraw?DRAW_BRUSH:DRAW_CONNOTDRAW;
}


void CMainFrame::OnDrawBrush()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_BRUSH;

}



void CMainFrame::OnDrawLine()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_LINE;
}


void CMainFrame::OnDrawCircle()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_CIRCLE;
}


void CMainFrame::OnDrawEclipse()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_ECLIPSE;
}


void CMainFrame::OnDrawRect()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_RECT;
}


void CMainFrame::OnDrawCurl()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_CURL;
}


void CMainFrame::OnDrawErase()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_ERASER;
}


void CMainFrame::OnDrawColor()
{
	// TODO: �ڴ���������������
	
	CColorDialog cdlg(m_clr, CC_FULLOPEN | CC_RGBINIT); // ����Ĭ����ɫ
	if(cdlg.DoModal() == IDOK)
		m_clr = cdlg.GetColor();
	UpdateData(FALSE);
	
}


void CMainFrame::OnUpdateEnabledraw(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	
	GetMenu()->GetSubMenu(3)->CheckMenuItem(0,(enabledraw?MF_CHECKED:MF_UNCHECKED)|MF_BYPOSITION);
	if (enabledraw) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
	if (((CͼƬ������App*)AfxGetApp())->m_LoginStatus)
		 pCmdUI->Enable(TRUE);
	else
	{
		 pCmdUI->Enable(FALSE);
	}
}




void CMainFrame::OnUpdateDrawBrush(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(1,((drawstatus==DRAW_BRUSH)?MF_CHECKED:MF_UNCHECKED)|MF_BYPOSITION);
	if (enabledraw&&(drawstatus==DRAW_BRUSH)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);

}


void CMainFrame::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
		else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_LINE)) pCmdUI->SetCheck(1);
		else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_CIRCLE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawEclipse(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_ECLIPSE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawRect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_RECT)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawCurl(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_CURL)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawErase(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_ERASER)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CMainFrame::OnUpdateDrawColor(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateDrawStyle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnCreateele()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnCreateobj()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateCreateele(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateCreateobj(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}


void CMainFrame::OnViewToolbardraw()
{
	// TODO: �ڴ���������������
	viewtoolbar = !viewtoolbar;
	if (viewtoolbar) ShowControlBar(&m_wndToolBar2,TRUE,FALSE);
	else ShowControlBar(&m_wndToolBar2,FALSE,FALSE);

}


void CMainFrame::OnUpdateViewToolbardraw(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (viewtoolbar) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}



void CMainFrame::OnUpdateCalladmin(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	 
}


void CMainFrame::OnDrawBkgcolor()
{
	// TODO: �ڴ���������������
	CͼƬ������Doc* pDoc = (CͼƬ������Doc*)(GetActiveFrame()->GetActiveDocument());
	CColorDialog cdlg(pDoc->m_bkgclr, CC_FULLOPEN | CC_RGBINIT); // ����Ĭ����ɫ
	if(cdlg.DoModal() == IDOK)
	pDoc->m_bkgclr = cdlg.GetColor();
	UpdateData(FALSE);
	pDoc->UpdateAllViews(NULL);
	

	//CͼƬ������App* pWinApp=(CͼƬ������App*)AfxGetApp();
	
}


void CMainFrame::OnUpdateDrawBkgcolor(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	//if (MDIGetActive()==NULL) 
		//MessageBox("NoActive");
}


void CMainFrame::OnDrawStyle()
{
	// TODO: �ڴ���������������
	CStyleDlg dlg;
	dlg.DoModal();
	
}


LRESULT CMainFrame::OnReturnPressed(WPARAM,LPARAM)
{
	CͼƬ������Doc* pDoc = (CͼƬ������Doc*)(GetActiveFrame()->GetActiveDocument());
	if (pDoc==NULL) return TRUE;
	
	CͼƬ������View * cv =(CͼƬ������View *)GetActiveFrame()->GetActiveView();
	if (cv!=NULL)
	{
		if (cv->tmp!=NULL) delete cv->tmp;
		cv->tmp =NULL;
		pDoc->UpdateAllViews(NULL);
	}

	char* buf=(char*)malloc(m_CmdBar.m_Edit1.GetWindowTextLength()+1);
	char* buf2=(char*)malloc(m_CmdBar.m_Edit2.GetWindowTextLength()+1);
	m_CmdBar.m_Edit1.GetWindowText(buf,m_CmdBar.m_Edit1.GetWindowTextLength()+1);
	m_CmdBar.m_Edit1.SetWindowText("");//�����ǰ������
	m_CmdBar.m_Edit2.GetWindowText(buf2,m_CmdBar.m_Edit2.GetWindowTextLength()+1);
	m_CmdBar.m_Edit2.SetWindowText("");//�����ǰ������
	if (!pDoc->allowdraw) return TRUE;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	int currentstyle = cm->m_nLineStyle;
	int currentwidth = cm->m_nLineWidth;
	COLORREF currentcolor = cm->m_clr;
	
	int arr[4];
	if (!getorder(buf,arr,geti(buf))) return true;
	getword(geti(buf),buf);
	for(int i=0;i<strlen(buf);i++){
		buf[i]=toupper(buf[i]);}
	if(strcmp(buf,"LINE")==0)
	{
		MyObject * n =new MyLine(arr[0],arr[1],arr[2],arr[3],currentstyle,currentwidth,currentcolor);
		pDoc->data.push_back(n);
	}
	if(strcmp(buf,"RECTANGLE")==0)
	{			
		MyObject * n =new MyRectangle(arr[0],arr[1],arr[2],arr[3],currentstyle,currentwidth,currentcolor);
		pDoc->data.push_back(n);
	}
	if(strcmp(buf,"CIRCLE")==0)
	{			
		MyObject * n =new MyCircle(arr[0],arr[1],arr[2],arr[3],currentstyle,currentwidth,currentcolor);
		pDoc->data.push_back(n);
	}
	if(strcmp(buf,"ELLIPSE")==0)
	{
		MyObject * n =new MyEllipse(arr[0],arr[1],arr[2],arr[3],currentstyle,currentwidth,currentcolor);
		pDoc->data.push_back(n);
	}
	
	
	free(buf);
	free(buf2);
		//�뽫�����������
		//�벻Ҫ������������
		pDoc->UpdateAllViews(NULL);

	return TRUE;
}		



void CMainFrame::OnCommandSet()
{
	((CͼƬ������App*)AfxGetApp())->OnCerTainFileOpen("\\psf\Home\Desktop\1234.bmp");
	// TODO: �ڴ���������������
	//MessageBox("haha");
}


void CMainFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CͼƬ������Doc* pDoc = (CͼƬ������Doc*)(GetActiveFrame()->GetActiveDocument());
	if (pDoc->data.empty())  pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}




void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POSITION pos=m_ChildFramePtrList.GetHeadPosition();
	CChildFrame* pChildFrame;

	while(pos != NULL)
	{
		pChildFrame=(CChildFrame*)m_ChildFramePtrList.GetNext(pos);
		pChildFrame->OnClose();
	}
	if (NULL==m_ChildFramePtrList.GetHeadPosition())
	CMDIFrameWnd::OnClose();
}


int CMainFrame::ExitAllChildFrame(void)
{
	POSITION pos=m_ChildFramePtrList.GetHeadPosition();
	CChildFrame* pChildFrame;

	while(pos != NULL)
	{
		pChildFrame=(CChildFrame*)m_ChildFramePtrList.GetNext(pos);
		pChildFrame->OnClose();
		
	}
	pos=m_ChildFramePtrList.GetHeadPosition();
	if (pos==NULL) return 1;
	else return 0;

}


void CMainFrame::OnDrawMove()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_MOVE;
}


void CMainFrame::OnUpdateDrawMove(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_MOVE)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


bool CMainFrame::getorder(char* fullorder, int* arr, int i)
{
	char *p=fullorder+i;
	int a=-1,b=-1,c=-1,d=-1;
	sscanf_s(p,"(%d,%d,%d,%d)",&a,&b,&c,&d);
	if ((a!=-1)&&(b!=-1)&&(c!=-1)&&(d!=-1))
	{
		*arr = a;
		*(arr+1) = b;
		*(arr+2) = c;
		*(arr+3) = d;
		return 1;
	}
	else
	{
		return 0;
	}
}



void CMainFrame::getword(int i, char* fullorder)
{
	char *p=fullorder+i;
	*p=0;
}


int CMainFrame::geti(char* fullorder)
{
	int i;
	for(i=0;fullorder[i]!='\0';i++)
	{
		if(fullorder[i]=='(')
			return i;
	}
	return 0;
}


LRESULT CMainFrame::OnContentChange(WPARAM,LPARAM)
{
	char* buf=(char*)malloc(m_CmdBar.m_Edit1.GetWindowTextLength()+1);
	char* buf2=(char*)malloc(m_CmdBar.m_Edit2.GetWindowTextLength()+1);
	m_CmdBar.m_Edit1.GetWindowText(buf,m_CmdBar.m_Edit1.GetWindowTextLength()+1);
	m_CmdBar.m_Edit2.GetWindowText(buf2,m_CmdBar.m_Edit2.GetWindowTextLength()+1);
	CͼƬ������Doc* pDoc = (CͼƬ������Doc*)(GetActiveFrame()->GetActiveDocument());
	
	if (strchr(buf,')'))
	{
		if (pDoc==NULL) return TRUE;
		CͼƬ������View * cv =(CͼƬ������View *)GetActiveFrame()->GetActiveView();
		if (cv ==NULL) {
			return TRUE;
			MessageBox("cv=NULL");
		}
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		int currentstyle = cm->m_nLineStyle;
		int currentwidth = cm->m_nLineWidth;
		COLORREF currentcolor = cm->m_clr;
		if (cv->tmp!=NULL) delete cv->tmp;
		cv->tmp =NULL;
		int arr[4];
		if (!getorder(buf,arr,geti(buf))) return true;
		getword(geti(buf),buf);
		for(int i=0;i<strlen(buf);i++){
			buf[i]=toupper(buf[i]);}
		if(strcmp(buf,"LINE")==0)
		{
			cv->tmp =new MyLine(arr[0],arr[1],arr[2],arr[3],PS_DOT,1,RGB(0,0,0));
		}
		if(strcmp(buf,"RECTANGLE")==0)
		{			
			cv->tmp =new MyRectangle(arr[0],arr[1],arr[2],arr[3],PS_DOT,1,RGB(0,0,0));
		}
		if(strcmp(buf,"CIRCLE")==0)
		{			
				cv->tmp =new MyCircle(arr[0],arr[1],arr[2],arr[3],PS_DOT,1,RGB(0,0,0));
		}
		if(strcmp(buf,"ELLIPSE")==0)
		{
				cv->tmp =new MyEllipse(arr[0],arr[1],arr[2],arr[3],PS_DOT,1,RGB(0,0,0));
		}
			pDoc->UpdateAllViews(NULL);
	}
	free(buf);
	free(buf2);
	//�뽫�����������
	//�벻Ҫ������������

	return TRUE;
}

void CMainFrame::OnFilesearch()
{
	// TODO: �ڴ���������������
	CFilesearchDlg dlg;
	dlg.DoModal();
}


//void CMainFrame::OnSelChangeMyList(void)
//{
//	AfxMessageBox("oops");
//}


void CMainFrame::OnDrawSelect()
{
	// TODO: �ڴ���������������
	drawstatus = DRAW_SELECT;
}


void CMainFrame::OnUpdateDrawSelect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!enabledraw) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (enabledraw&&(drawstatus==DRAW_SELECT)) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}
