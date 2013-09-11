
// MainFrm.h : CMainFrame 类的接口
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

// 特性
public:

public:
// 操作

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CToolBar          m_wndToolBar2;
	CToolBarEditStatic		  m_CmdBar;
	
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnabledraw();

	
public:
	//自己申请的变量
	bool enabledraw;
	int drawstatus;
	bool viewtoolbar;
	int m_nLineWidth;
	int m_nLineStyle;
	COLORREF m_clr;
	COLORREF m_bkgclr;
	CFont m_font;


public:
	//消息处理函数
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
	afx_msg LRESULT OnReturnPressed(WPARAM,LPARAM);//处理自定义消息的函数
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


