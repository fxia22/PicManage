
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
#include "MainFrm.h"

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	
END_MESSAGE_MAP()

// C图片管理器View 构造/析构

C图片管理器View::C图片管理器View()
	: m_pre_point(CPoint(0,0))
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
	//m_mousestatus = false;
	return CView::PreCreateWindow(cs);
}

// C图片管理器View 绘制

void C图片管理器View::OnDraw(CDC* pDC)
{
	C图片管理器Doc* pDoc = GetDocument();
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CClientDC dc(this);
	//pDC->MoveTo(100,100);
	//pDC->LineTo(200,200);
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	//MemDC.SetBkColor(cm->m_bkgclr);
	MemDC.CreateCompatibleDC(NULL);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC,rect.right-rect.left,rect.bottom-rect.top);
	//MemBitmap.LoadBitmap(IDR_IDB_BITMAP11); 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//给MeMDC绘图
	
	if(tmp)
	{
			CPen pen(0,0,tmp->m_lineclr); 
			CPen *penOld = MemDC.SelectObject( &pen ); 
			tmp->draw(MemDC);
			MemDC.SelectObject(penOld);
	}
	for(int i=0;i<pDoc->data.size();i++)
	{
		//CBrush brush(RGB(rand()%255,rand()%255,rand()%255)); 
		//CBrush *pOld = MemDC.SelectObject( &brush ); 
		CPen pen(2,3,pDoc->data[i]->m_lineclr); 
		CPen *penOld = MemDC.SelectObject( &pen ); 
		
		pDoc->data[i]->draw(MemDC);
		//MemDC.SelectObject(pOld);
		MemDC.SelectObject(penOld);


		//pen.DeleteObject();
	}
	
	pDC->BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
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


void C图片管理器View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//m_mousestatus = true;
	if(tmp==NULL)tmp=new Line();
	else {delete tmp;tmp=new Line();}
	tmp->x1=tmp->x2=point.x;
	tmp->y1=tmp->y2=point.y;
	tmp->m_lineclr = cm->m_clr;
	m_pre_point = point;
	Invalidate();
	UpdateWindow();
	CView::OnLButtonDown(nFlags, point);
	
}


void C图片管理器View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_mousestatus = false;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (cm->enabledraw)
	{
		if(tmp)GetDocument()->data.push_back(tmp);
		tmp=NULL;
		if (cm->drawstatus==DRAW_BRUSH)
		{
			Invalidate();
			UpdateWindow();
		}
	}


	CView::OnLButtonUp(nFlags, point);
}


void C图片管理器View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CPen pen(cm->m_nLineStyle, cm->m_nLineWidth, cm->m_clr); 
	CPen* pOldpen = dc.SelectObject(&pen);
	if (cm->enabledraw)
		switch (cm->drawstatus)
	{
		case (DRAW_BRUSH) : 
			if (nFlags&MK_LBUTTON)
			{
				//dc.SetDCBrushColor(cm->m_clr);
				dc.MoveTo(m_pre_point);
				dc.LineTo(point);
				tmp=new Line();
					tmp->x1 = m_pre_point.x;
					tmp->y1 = m_pre_point.y;
					tmp->x2 = point.x;
					tmp->y2 = point.y;
					tmp->m_lineclr = cm->m_clr;
				GetDocument()->data.push_back(tmp);
				//dc.SetPixel(point, cm->m_clr);
				m_pre_point = point;
			};
			break;
		case (DRAW_LINE):
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{
				
				if(tmp){tmp->x2=point.x;tmp->y2=point.y;
				tmp->m_lineclr = cm->m_clr;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		default:
		break;
	} 
	
	
	CView::OnMouseMove(nFlags, point);
}


BOOL C图片管理器View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}
