
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "myEdit.h"
#include "ToolBarEditStatic.h"
#include "Adomdb.h"
class CMainFrame : public CMDIFrameWnd
{
	public:	enum
	{
		DRAW_CONNOTDRAW,
		DRAW_LINE,
		DRAW_BRUSH,
		DRAW_CIRCLE,
		DRAW_ECLIPSE,
		DRAW_RECT,
		DRAW_CURL,
		DRAW_ERASER,
		DRAW_MOVE
	};
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

public:
// ����

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CToolBar          m_wndToolBar2;
	CToolBarEditStatic		  m_CmdBar;
	
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnabledraw();

	
public:
	//�Լ�����ı���
	bool enabledraw;
	int drawstatus;
	bool viewtoolbar;
	int m_nLineWidth;
	int m_nLineStyle;
	COLORREF m_clr;
	COLORREF m_bkgclr;
	CFont m_font;


public:
	//��Ϣ������
	afx_msg void OnDrawBrush();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEclipse();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawCurl();
	afx_msg void OnDrawErase();
	afx_msg void OnDrawColor();
	afx_msg void OnUpdateEnabledraw(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawBrush(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEclipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCurl(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawErase(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawColor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawStyle(CCmdUI *pCmdUI);
	afx_msg void OnCreateele();
	afx_msg void OnCreateobj();
	afx_msg void OnUpdateCreateele(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateobj(CCmdUI *pCmdUI);
	afx_msg void OnViewToolbardraw();
	afx_msg void OnUpdateViewToolbardraw(CCmdUI *pCmdUI);
	afx_msg void OnCalladmin();
	afx_msg void OnUpdateCalladmin(CCmdUI *pCmdUI);
	afx_msg void OnDrawBkgcolor();
	afx_msg void OnUpdateDrawBkgcolor(CCmdUI *pCmdUI);
	afx_msg void OnDrawStyle();
	afx_msg LRESULT OnReturnPressed(WPARAM,LPARAM);//�����Զ�����Ϣ�ĺ���
	afx_msg void OnCommandSet();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
//	_ConnectionPtr m_pConnection;
//	_RecordsetPtr m_pRecordset;
//	void OnInitADOConn(void);
	Adomdb ado;
//	afx_msg void OnFileOpen();
	CPtrList m_ChildFramePtrList;
	afx_msg void OnClose();
	void ExitAllChildFrame(void);
	afx_msg void OnDrawMove();
	afx_msg void OnUpdateDrawMove(CCmdUI *pCmdUI);
	void getorder(char* fullorder, int* arr, int i);
	void getword(int i, char* fullorder);
	int geti(char* fullorder);



};


