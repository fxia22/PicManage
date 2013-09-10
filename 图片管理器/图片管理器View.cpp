
// ͼƬ������View.cpp : CͼƬ������View ���ʵ��
//

#include "stdafx.h"
#include <typeinfo>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ͼƬ������.h"
#endif

#include "ͼƬ������Doc.h"
#include "ͼƬ������View.h"
#include "MainFrm.h"
#include "MyLine.h"
#include "MyRectangle.h"
#include "MyEllipse.h"
#include "MyCircle.h"
#include "MyPolyLine.h"


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
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	CBitmap bitmap;


	MemDC.CreateCompatibleDC(NULL);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC,rect.right-rect.left,rect.bottom-rect.top);
	HBITMAP bit=NULL;
	CImage imgcopy;
	

	if (pDoc->m_img!=NULL )
		{
			ImageCopy(*(pDoc->m_img),imgcopy);
			bit = imgcopy.Detach();
			MemBitmap.Attach(bit);
		
	}
	
	
	
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	if (pDoc->m_img==NULL)
	MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//��MeMDC��ͼ
	
	MemDC.SetBkMode(TRANSPARENT);
	for(int i=0;i<pDoc->data.size();i++)
	{
		pDoc->data[i]->draw(MemDC);
	}
	if(tmp)
	{
		tmp->draw(MemDC);
	}
	
	//�Ȼ����ļ��еģ��ٻ����ڴ��е�
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
		CͼƬ������Doc* pDoc = GetDocument();
	if ((pDoc->allowdraw)&&(cm->enabledraw))
	{
		switch (cm->drawstatus)
		{
		case DRAW_LINE:
			if(tmp==NULL)tmp=new MyLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new  MyLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			
			break;
		case DRAW_RECT:
			if(tmp==NULL)tmp=new MyRectangle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				else {delete tmp;tmp=new MyRectangle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;

		case DRAW_ECLIPSE:
			if(tmp==NULL)tmp=new MyEllipse(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new MyEllipse(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;
		case DRAW_CIRCLE:
			if(tmp==NULL)tmp=new MyCircle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new MyCircle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;
		case DRAW_ERASER:
			if(tmp==NULL)tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DASH,1,RGB(0,0,0));
			else {delete tmp;tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DASH,1,RGB(0,0,0));}
			break;
		}
		
	
	}
	
	
	
	
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
	CͼƬ������Doc* pDoc = GetDocument();
	if ((cm->enabledraw)&&(pDoc->allowdraw))
	{
		if (cm->drawstatus == DRAW_ERASER)
		{
			//ɾ��һЩԪ��
		MyRectangle * mr = (MyRectangle *)tmp;
		for (int i = 0 ; i<pDoc->data.size();i++)
			{
				
				MyLine* ml = (MyLine*)pDoc->data[i];
				if ((mr!=NULL)&&(ml!=NULL))
				if (mr->includeLine(ml))
					{
						ml->enable = false;
				}
			}
			
		}
		else
		if(tmp) pDoc->data.push_back(tmp);
		tmp=NULL;
	
	}

	Invalidate(TRUE);
	UpdateWindow();
	CView::OnLButtonUp(nFlags, point);
}


void CͼƬ������View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CͼƬ������Doc* pDoc = GetDocument();
	CPen pen(cm->m_nLineStyle, cm->m_nLineWidth, cm->m_clr); 
	CPen* pOldpen = dc.SelectObject(&pen);
	if ((cm->enabledraw)&&(pDoc->allowdraw))
		switch (cm->drawstatus)
	{
		case (DRAW_BRUSH) : 
			if (nFlags&MK_LBUTTON)
			{
				//dc.SetDCBrushColor(cm->m_clr);
				//dc.MoveTo(m_pre_point);
				//dc.LineTo(point);
				tmp=new MyLine(m_pre_point.x,m_pre_point.y,point.x,point.y, cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				GetDocument()->data.push_back(tmp);
				Invalidate(1);
				UpdateWindow();
				//dc.SetPixel(point, cm->m_clr);
				m_pre_point = point;
			};
			break;
		case (DRAW_LINE):
			if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
			{
				
				if(tmp){
					MyLine* ml = (MyLine*)tmp;
					ml->_x2=point.x;
					ml->_y2=point.y;
				ml->m_clr = cm->m_clr;
				ml->m_style = cm->m_nLineStyle;
				ml->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;

		case DRAW_RECT:
			if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
			{

				if(tmp){
					MyRectangle* mr = (MyRectangle*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_ECLIPSE:
			if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
			{

				if(tmp){
					MyEllipse* mr = (MyEllipse*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_CIRCLE:
			if(nFlags&MK_LBUTTON)//���������ڰ���״̬�Ž��д���
			{

				if(tmp){
					MyCircle* mr = (MyCircle*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_ERASER:
			if (tmp)
			{
				MyRectangle* mr = (MyRectangle*) tmp;
				mr->_x2 = point.x;
				mr->_y2 = point.y;

			}
			Invalidate();
			UpdateWindow();
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


bool CͼƬ������View::SaveBitmap(HBITMAP  hBitmap, char* filename)
{
	BITMAP bitmap;
	GetObject(hBitmap,sizeof(BITMAP),&bitmap);

	LPVOID lp=VirtualAlloc(0,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_COMMIT,PAGE_READWRITE);
	if(lp==0) return false;
	GetBitmapBits(hBitmap,bitmap.bmHeight*bitmap.bmWidthBytes,lp);
	BITMAPFILEHEADER b1={0};
	BITMAPINFOHEADER b2={0};
	b1.bfType=(DWORD)(('M'<<8)|'B');
	b1.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	b1.bfSize=sizeof(BITMAPFILEHEADER)+bitmap.bmHeight*bitmap.bmWidthBytes+sizeof(BITMAPINFOHEADER);

	b2.biSize=sizeof(BITMAPINFOHEADER);
	b2.biWidth=bitmap.bmWidth;
	b2.biHeight=bitmap.bmHeight;
	b2.biPlanes=1;
	b2.biBitCount=bitmap.bmBitsPixel;
	b2.biCompression=BI_RGB;
	b2.biSizeImage=bitmap.bmHeight*bitmap.bmWidthBytes;

	HANDLE hFile=CreateFileA(filename,FILE_ALL_ACCESS,NULL,NULL,CREATE_ALWAYS,NULL,NULL);
	HANDLE hmap=CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,b1.bfSize,0);
	LPVOID l=MapViewOfFile(hmap,FILE_MAP_WRITE,0,0,0);
	if(l==0) return false;
	memcpy(l,&b1,sizeof(BITMAPFILEHEADER));
	memcpy((BYTE*)l+sizeof(b1),&b2,sizeof(BITMAPINFOHEADER));
	for(int i=0;i<bitmap.bmHeight;i++)
		memcpy((BYTE*)l+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+i*bitmap.bmWidthBytes,(BYTE*)lp+(bitmap.bmHeight-1-i)*bitmap.bmWidthBytes,bitmap.bmWidthBytes);
	UnmapViewOfFile(l);
	CloseHandle(hmap);
	CloseHandle(hFile);
	VirtualFree(lp,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_FREE);
	if(GetLastError()) return false;
	return true;
}


bool CͼƬ������View::SaveCurrentImage(char* filename1)
{
	bool flag;
	/*CͼƬ������Doc* pDoc = GetDocument();
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		{
			return FALSE;
			MessageBox("Cannot open file");
	}
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	CDC *pDC=GetDC();
	if (pDC==NULL) MessageBox("PDC==NUll");
	MemDC.CreateCompatibleDC(CDC::FromHandle(::GetDC(NULL)));

	CBitmap MemBitmap;
	
	MemBitmap.CreateCompatibleBitmap(pDC,rect.right-rect.left,rect.bottom-rect.top);
	MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//��MeMDC��ͼ


	for(int i=0;i<pDoc->data.size();i++)
	{
		
		pDoc->data[i]->draw(MemDC);
		
	}
	
	MemDC.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,GetDC(),rect.left,rect.top,SRCCOPY);
	flag = SaveBitmap(*(MemDC.GetCurrentBitmap()),filename1);
	

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();*/
	CͼƬ������Doc* pDoc = GetDocument();
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CDC *pDC=GetDC();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	CBitmap bitmap;


	MemDC.CreateCompatibleDC(CDC::FromHandle(::GetDC(NULL)));
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC,rect.right-rect.left,rect.bottom-rect.top);
	HBITMAP bit=NULL;
	CImage imgcopy;


	if (pDoc->m_img!=NULL )
	{
		ImageCopy(*(pDoc->m_img),imgcopy);
		bit = imgcopy.Detach();
		MemBitmap.Attach(bit);

	}



	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	if (pDoc->m_img==NULL) MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//��MeMDC��ͼ

	MemDC.SetBkMode(TRANSPARENT);
	for(int i=0;i<pDoc->data.size();i++)
	{
		pDoc->data[i]->draw(MemDC);
	}
	if(tmp)
	{
		tmp->draw(MemDC);
	}

	//�Ȼ����ļ��еģ��ٻ����ڴ��е�
	MemDC.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&MemDC,0,0,SRCCOPY);
	flag = SaveBitmap(*(MemDC.GetCurrentBitmap()),filename1);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	
	return flag;
}

/*
BOOL CͼƬ������View::TranslateBitmapSize(
	HDC hCurScreemDC,	//��ǰ��ĻDC����ͨ��GetDC���
	HBITMAP hBmpSrc,	//ԭBITMAP���
	int nSrcWidth,		//ԭBITMAP�Ŀ��
	int nSrcHeight,		//ԭBITMAP�ĸ߶�
	HBITMAP &hBmpDst,	//�ı��С���BITMAP�ľ��
	int nDstWidth,		//�ı��С���BITMAP�Ŀ��
	int nDstHeight		//�ı��С���BITMAP�ĸ߶�
	)
{
	if (hBmpSrc == NULL || hCurScreemDC == NULL)
	{
		return FALSE;
	}
	if (hBmpDst != NULL)
	{
		DeleteObject(hBmpDst);
	}
	HDC hOldSrcDC = NULL;
	HDC hOldDstDC = NULL;
	HDC hSrcDC = CreateCompatibleDC(hCurScreemDC);
	HDC hDstDC = CreateCompatibleDC(hCurScreemDC);
	hBmpDst = CreateCompatibleBitmap(hCurScreemDC,nDstWidth,nDstHeight);
	hOldSrcDC = (HDC)SelectObject(hSrcDC,hBmpSrc);
	hOldDstDC = (HDC)SelectObject(hDstDC,hBmpDst);
	StretchBlt(hDstDC,0,0,nDstWidth,nDstHeight,hSrcDC,0,0,nSrcWidth,nSrcHeight,SRCCOPY);
	SelectObject(hSrcDC,hOldSrcDC);
	SelectObject(hDstDC,hOldDstDC);
	DeleteObject(hSrcDC);
	DeleteObject(hDstDC);
	return TRUE;	
}
*/


bool CͼƬ������View::ImageCopy(const CImage &srcImage, CImage &destImage)
{
	int i;//ѭ������
	if(srcImage.IsNull())
		return FALSE;
	//Դͼ�����
	BYTE* srcPtr=(BYTE*)srcImage.GetBits();
	int srcBitsCount=srcImage.GetBPP();
	int srcWidth=srcImage.GetWidth();
	int srcHeight=srcImage.GetHeight();
	int srcPitch=srcImage.GetPitch(); 
	//����ԭ��ͼ��
	if( !destImage.IsNull())
	{
		destImage.Destroy();
	}
	//������ͼ��
	if(srcBitsCount==32)   //֧��alphaͨ��
	{
		destImage.Create(srcWidth,srcHeight,srcBitsCount,1);
	}
	else
	{
		destImage.Create(srcWidth,srcHeight,srcBitsCount,0);
	}
	//���ص�ɫ��
	if(srcBitsCount<=8&&srcImage.IsIndexed())//��Ҫ��ɫ��
	{
		RGBQUAD pal[256];
		int nColors=srcImage.GetMaxColorTableEntries();
		if(nColors>0)
		{     
			srcImage.GetColorTable(0,nColors,pal);
			destImage.SetColorTable(0,nColors,pal);//���Ƶ�ɫ�����
		}   
	} 
	//Ŀ��ͼ�����
	BYTE *destPtr=(BYTE*)destImage.GetBits();
	int destPitch=destImage.GetPitch();
	//����ͼ������
	for(i=0 ; i<srcHeight;i++)
	{
		memcpy( destPtr+i*destPitch, srcPtr+i*srcPitch, abs(srcPitch) );
	} 

	return TRUE;
} 