
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
END_MESSAGE_MAP()

// CͼƬ������View ����/����

CͼƬ������View::CͼƬ������View()
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

	return CView::PreCreateWindow(cs);
}

// CͼƬ������View ����

void CͼƬ������View::OnDraw(CDC* /*pDC*/)
{
	CͼƬ������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
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
