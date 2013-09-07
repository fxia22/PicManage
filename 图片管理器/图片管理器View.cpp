
// ͼƬ������View.cpp : CͼƬ������View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ͼƬ������.h"
#endif

#include "ͼƬ������Doc.h"
#include "ͼƬ������View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CͼƬ������View

IMPLEMENT_DYNCREATE(CͼƬ������View, CView)

BEGIN_MESSAGE_MAP(CͼƬ������View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	
END_MESSAGE_MAP()

// CͼƬ������View ����/����

CͼƬ������View::CͼƬ������View()
	: m_pre_point(CPoint(0,0))
{
	// TODO: �ڴ˴���ӹ������

}

CͼƬ������View::~CͼƬ������View()
{
}

BOOL CͼƬ������View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//m_mousestatus = false;
	return CView::PreCreateWindow(cs);
}

// CͼƬ������View ����

void CͼƬ������View::OnDraw(CDC* pDC)
{
	CͼƬ������Doc* pDoc = GetDocument();
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
	//��MeMDC��ͼ
	
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
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CͼƬ������View ��ӡ

BOOL CͼƬ������View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CͼƬ������View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CͼƬ������View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CͼƬ������View ���

#ifdef _DEBUG
void CͼƬ������View::AssertValid() const
{
	CView::AssertValid();
}

void CͼƬ������View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CͼƬ������Doc* CͼƬ������View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CͼƬ������Doc)));
	return (CͼƬ������Doc*)m_pDocument;
}
#endif //_DEBUG


// CͼƬ������View ��Ϣ�������


void CͼƬ������View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void CͼƬ������View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void CͼƬ������View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
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


BOOL CͼƬ������View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}
