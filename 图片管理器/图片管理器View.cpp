
// 图片管理器View.cpp : C图片管理器View 类的实现
//

#include "stdafx.h"
#include <typeinfo>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "图片管理器.h"
#endif

#include "图片管理器Doc.h"
#include "图片管理器View.h"
#include "MainFrm.h"
#include "MyLine.h"
#include "MyRectangle.h"
#include "MyEllipse.h"
#include "MyCircle.h"
#include "MyPolyLine.h"
#include "MyBezier.h"
#include "MyMultipleLine.h"
#include "ChildFrm.h"
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
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_SHANGE, &C图片管理器View::OnShange)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// C图片管理器View 构造/析构

C图片管理器View::C图片管理器View()
	: m_pre_point(CPoint(0,0))
{

	
	// TODO: 在此处添加构造代码
	m_normalize = false;
	bzdraw = 0;
}

C图片管理器View::~C图片管理器View()
{
	m_normalize = false;
	
}

BOOL C图片管理器View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//m_mousestatus = false;
	m_normalize = false;
	
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
	//给MeMDC绘图
	
	MemDC.SetBkMode(TRANSPARENT);

	for(int i=0;i<pDoc->data.size();i++)
	{
		if (pDoc->data[i]->selected)
		
			{
				if(m_drawselect)
				pDoc->data[i]->draw(MemDC);
			
		}
		else
		{
				pDoc->data[i]->draw(MemDC);
		}
	}


	if(tmp)
	{
		tmp->draw(MemDC);
	}
	//先绘制文件中的，再绘制内存中的
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
		C图片管理器Doc* pDoc = GetDocument();
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
			if(tmp==NULL)tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DOT,1,RGB(0,0,0));
			else {delete tmp;tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DOT,1,RGB(0,0,0));}
			break;
		case DRAW_SELECT:
			if(tmp==NULL)tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DOT,1,RGB(0,0,0));
			else {delete tmp;tmp=new MyRectangle(point.x,point.y,point.x,point.y,PS_DOT,1,RGB(0,0,0));}
			break;
		case DRAW_MOVE:
			tmp = NULL;
			break;
		case DRAW_CURL:
			if (bzdraw ==1)
			{
				if (tmp!=NULL)
				{
					MyBezier* bz = (MyBezier*)tmp;
					bz->_x3=bz->_x4 = point.x;
					bz->_y3=bz->_y4 = point.y;
					bz->comp = true;
				}
			}
			else
			{
				if(tmp==NULL)tmp=new MyBezier(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				else {delete tmp;tmp=new MyBezier(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
				((MyBezier*)tmp)->comp = false;
				bzdraw = 0;
			}
			break;
		case DRAW_BRUSH:
			if(tmp==NULL)tmp=new MyMultipleLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new MyMultipleLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;

		}
		
	
	}
	
	
	
	
	m_pre_point = point;
	Invalidate();
	UpdateWindow();
	CView::OnLButtonDown(nFlags, point);
	
}


void C图片管理器View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_mousestatus = false;
	//m_normalize = false;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	C图片管理器Doc* pDoc = GetDocument();
		vector<MyObject*> ::iterator Iter;
	if (cm->drawstatus!=DRAW_SELECT)
		 for (Iter = pDoc->data.begin();Iter!= pDoc->data.end();Iter++)
		{
			(*Iter)->selected = false;
		}
	
	
	
	if ((cm->enabledraw)&&(pDoc->allowdraw))
	{
		
		if (cm->drawstatus==DRAW_CURL)
		{
			if (bzdraw==0) bzdraw++;
			else
			{
				if(tmp) pDoc->data.push_back(tmp);
				tmp=NULL;
				bzdraw =0;
			}

		}
		else
		{
			bzdraw = 0;
			if (( cm->drawstatus== DRAW_ERASER)||(cm->drawstatus == DRAW_SELECT))
			{
			//删除一些元素
				MyRectangle * mr = (MyRectangle *)tmp;
				vector<MyObject*> ::iterator Iter;
				for (Iter = pDoc->data.begin();Iter!= pDoc->data.end();)
				{

						MyLine* ml = (MyLine*)*Iter;

						if ((mr!=NULL)&&(ml!=NULL))
							if (mr->includeLine(ml))
							{
								
								if (cm->drawstatus==DRAW_ERASER)
								{
									delete *Iter;
									pDoc->data.erase(Iter);
								}
								else
								{
									(*Iter)->selected = true;
									Iter++;
								}



							}
							else Iter++;
							
				}

			}
		else
		{
			
			if(tmp) pDoc->data.push_back(tmp);
			CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			
		}
			tmp=NULL;
		 
		}
	}
	updateListBox();
	Invalidate(TRUE);
	UpdateWindow();
	CView::OnLButtonUp(nFlags, point);
}


void C图片管理器View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!(GetKeyState(VK_SHIFT) & 0x80000000))
		 m_normalize = false;
	else m_normalize = true;
	CClientDC dc(this);
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		C图片管理器Doc* pDoc = GetDocument();
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
			/*	tmp=new MyLine(m_pre_point.x,m_pre_point.y,point.x,point.y, cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				GetDocument()->data.push_back(tmp);
				Invalidate(1);
				UpdateWindow();
				//dc.SetPixel(point, cm->m_clr);
				m_pre_point = point;
			*/
				if (tmp!=NULL)
				{

				
					MyMultipleLine* ml = (MyMultipleLine*) tmp;
					ml->AddPoint(point.x,point.y);
					Invalidate();
					UpdateWindow();
				}			
			
			
			};
			break;
		case (DRAW_LINE):
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{
				
				if(tmp){
					MyLine* ml = (MyLine*)tmp;
					ml->_x2=point.x;
					ml->_y2=point.y;
					if (m_normalize)
						if (abs(ml->_x1-point.x)<abs(ml->_y1-point.y))
							 ml->_x2 = ml->_x1;
						else 
							 ml->_y2 = ml->_y1;
				ml->m_clr = cm->m_clr;
				ml->m_style = cm->m_nLineStyle;
				ml->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;

		case DRAW_RECT:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{

				if(tmp){
					MyRectangle* mr = (MyRectangle*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					if (m_normalize)
					{
						mr->_x2 = mr->_x1+(point.x-mr->_x1+point.y-mr->_y1)/2;
						mr->_y2 = mr->_y1+(point.x-mr->_x1+point.y-mr->_y1)/2;
					}
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_ECLIPSE:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{

				if(tmp){
					MyEllipse* mr = (MyEllipse*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					if (m_normalize)
					{
						mr->_x2 = mr->_x1+(point.x-mr->_x1+point.y-mr->_y1)/2;
						mr->_y2 = mr->_y1+(point.x-mr->_x1+point.y-mr->_y1)/2;
					}
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_CIRCLE:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
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
			if(nFlags&MK_LBUTTON)
			if (tmp)
			{
				MyRectangle* mr = (MyRectangle*) tmp;
				mr->_x2 = point.x;
				mr->_y2 = point.y;

			}
			Invalidate();
			UpdateWindow();
			break;


		case DRAW_SELECT:
			if(nFlags&MK_LBUTTON)
				if (tmp)
				{
					MyRectangle* mr = (MyRectangle*) tmp;
					mr->_x2 = point.x;
					mr->_y2 = point.y;

				}
				Invalidate();
				UpdateWindow();
				break;

		case DRAW_MOVE:
			if (nFlags&MK_LBUTTON)
			{
				vector<MyObject*> ::iterator Iter;
				
				for (Iter = pDoc->data.begin();Iter!= pDoc->data.end();Iter++)
				{
					if ((*Iter)->selected)
						(*Iter)->moveto(point.x-m_pre_point.x,point.y-m_pre_point.y);

				}

			}

			m_pre_point = point;
			Invalidate();
			UpdateWindow();
			break;


		case DRAW_CURL:
			if(nFlags&MK_LBUTTON)
				if (tmp)
				{
					MyBezier* bz = (MyBezier*) tmp;
					if (bzdraw==0)
					{
						bz->_x2 = point.x;
						bz->_y2 = point.y;
					}
					else
					{
						if (bzdraw == 1)
						{
							bz->_x3 = point.x;
							bz->_y3 = point.y;
						}
					}
				}
				Invalidate();
				UpdateWindow();
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


bool C图片管理器View::SaveBitmap(HBITMAP  hBitmap, char* filename)
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


bool C图片管理器View::SaveCurrentImage(char* filename1)
{
	bool flag;
	C图片管理器Doc* pDoc = GetDocument();
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
	//给MeMDC绘图

	MemDC.SetBkMode(TRANSPARENT);
	for(int i=0;i<pDoc->data.size();i++)
	{
		pDoc->data[i]->draw(MemDC);
	}
	if(tmp)
	{
		tmp->draw(MemDC);
	}

	//先绘制文件中的，再绘制内存中的
	MemDC.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&MemDC,0,0,SRCCOPY);
	flag = SaveBitmap(*(MemDC.GetCurrentBitmap()),filename1);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	
	return flag;
}



bool C图片管理器View::ImageCopy(const CImage &srcImage, CImage &destImage)
{
	int i;//循环变量
	if(srcImage.IsNull())
		return FALSE;
	//源图像参数
	BYTE* srcPtr=(BYTE*)srcImage.GetBits();
	int srcBitsCount=srcImage.GetBPP();
	int srcWidth=srcImage.GetWidth();
	int srcHeight=srcImage.GetHeight();
	int srcPitch=srcImage.GetPitch(); 
	//销毁原有图像
	if( !destImage.IsNull())
	{
		destImage.Destroy();
	}
	//创建新图像
	if(srcBitsCount==32)   //支持alpha通道
	{
		destImage.Create(srcWidth,srcHeight,srcBitsCount,1);
	}
	else
	{
		destImage.Create(srcWidth,srcHeight,srcBitsCount,0);
	}
	//加载调色板
	if(srcBitsCount<=8&&srcImage.IsIndexed())//需要调色板
	{
		RGBQUAD pal[256];
		int nColors=srcImage.GetMaxColorTableEntries();
		if(nColors>0)
		{     
			srcImage.GetColorTable(0,nColors,pal);
			destImage.SetColorTable(0,nColors,pal);//复制调色板程序
		}   
	} 
	//目标图像参数
	BYTE *destPtr=(BYTE*)destImage.GetBits();
	int destPitch=destImage.GetPitch();
	//复制图像数据
	for(i=0 ; i<srcHeight;i++)
	{
		memcpy( destPtr+i*destPitch, srcPtr+i*srcPitch, abs(srcPitch) );
	} 

	return TRUE;
} 

void C图片管理器View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetKeyState(VK_SHIFT) & 0x80000000)
	 m_normalize = true;
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void C图片管理器View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_normalize = false;
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void C图片管理器View::OnShange()
{
	// TODO: 在此添加命令处理程序代码
	C图片管理器Doc* pDoc = GetDocument();
	if (pDoc==NULL) return;
	pDoc->data.clear();
	pDoc->UpdateAllViews(NULL);









}


void C图片管理器View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	updateListBox();
	Invalidate(TRUE);
	UpdateWindow();
	CView::OnUpdate(pSender,lHint,pHint);
}


void C图片管理器View::updateListBox(void)
{
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CListBox * list = &	((CChildFrame*)cm->GetActiveFrame())->listbar.Lis;
	if (list==NULL) return;
	C图片管理器Doc* pDoc  =(C图片管理器Doc*) GetDocument();
	vector<MyObject*> ::iterator Iter;
	list->ResetContent();
	for (Iter = pDoc->data.begin();Iter!= pDoc->data.end();Iter++)
	{
		list->AddString((*Iter)->label);
		
	}
}

void C图片管理器View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
		{ 
			m_drawselect = !m_drawselect;
			Invalidate(NULL);
			UpdateWindow();
			break;
		}
	}
	CView::OnTimer(nIDEvent);
}


int C图片管理器View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1,500,NULL);

	return 0;
}


void C图片管理器View::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: 在此处添加消息处理程序代码
}
