
// 图片管理器Doc.cpp : C图片管理器Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "图片管理器.h"
#endif

#include "图片管理器Doc.h"
#include "图片管理器View.h"
#include <propkey.h>
#include "MyFileDialog.h"
#include "MainFrm.h"
#include "SizeDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C图片管理器Doc

IMPLEMENT_DYNCREATE(C图片管理器Doc, CDocument)

BEGIN_MESSAGE_MAP(C图片管理器Doc, CDocument)



	ON_COMMAND(ID_FILE_SAVE, &C图片管理器Doc::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &C图片管理器Doc::OnFileOpen)
	ON_COMMAND(ID_EDIT_UNDO, &C图片管理器Doc::OnEditUndo)
	ON_COMMAND(ID_FILE_SAVE_AS, &C图片管理器Doc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_SIZE, &C图片管理器Doc::OnUpdateChangeSize)
	ON_COMMAND(ID_CHANGE_SIZE, &C图片管理器Doc::OnChangeSize)
END_MESSAGE_MAP()


// C图片管理器Doc 构造/析构

C图片管理器Doc::C图片管理器Doc()
{
	// TODO: 在此添加一次性构造代码
	m_bkgclr = RGB(255,255,255);
	m_path_name = _T("");
	allowdraw = false;
}

C图片管理器Doc::~C图片管理器Doc()
{
}

BOOL C图片管理器Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	cm->enabledraw = true;
	cm->drawstatus = CMainFrame::DRAW_BRUSH;
	SetTitle(((C图片管理器App*)AfxGetApp())->CurrentUser+"-未命名");
	allowdraw = true;
	return TRUE;
}




// C图片管理器Doc 序列化

void C图片管理器Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void C图片管理器Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void C图片管理器Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void C图片管理器Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// C图片管理器Doc 诊断

#ifdef _DEBUG
void C图片管理器Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C图片管理器Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// C图片管理器Doc 命令




void C图片管理器Doc::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码


	if (!allowdraw) 
	{
		AfxMessageBox("在只读状态下无法保存");
		return;
	}
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp格式 (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	SetTitle(((C图片管理器App*)AfxGetApp())->CurrentUser+"-"+m_path_name);
	POSITION  POS = GetFirstViewPosition();
	C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);
	C图片管理器App* thisapp = (C图片管理器App*)AfxGetApp();
	myado.OnInitADOConn("权限");	
	myado.NewFile(thisapp->CurrentUser,m_path_name,"写");
	myado.ExitConnect();
	


}

void C图片管理器Doc::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg格式 (*.jpg)|*.jpg|bmp格式 (*.bmp)|*.bmp||",NULL);
	C图片管理器App* thisapp = (C图片管理器App* )AfxGetApp();
	if(dlg.DoModal()==IDOK)
	{
		m_path_name = dlg.GetPathName();
		if (CheckFileState(thisapp->CurrentUser,m_path_name)==NO_ACCESS)
		{
			AfxMessageBox("您没有访问权限");
			UpdateAllViews(NULL);
			return;
		}
		else
		{
			if (CheckFileState(thisapp->CurrentUser,m_path_name)==READ_ONLY) 
			{
				allowdraw = FALSE;	
				AfxMessageBox("您有只读权限");
			}
			else allowdraw = TRUE;
		}


		if(m_srcimg==NULL) m_srcimg=new CImage();
		else m_srcimg->Destroy();//释放以前的图片
		m_srcimg->Load(m_path_name);

		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//释放以前的图片
		SetTitle(((C图片管理器App*)AfxGetApp())->CurrentUser+"-"+m_path_name);

		if ((m_srcimg->GetHeight()>800)||(m_srcimg->GetWidth()>1200))
		{
			AfxMessageBox("您载入的图片太大，已经做了相应缩放");
			int tempheight = 600;
			int tempwidth = tempheight*m_srcimg->GetWidth()/m_srcimg->GetHeight();
			CreateStretchedImage(m_srcimg,m_img,tempheight,tempwidth);
		}
		else
			ImageCopy(*m_srcimg,*m_img);

		POSITION  POS = GetFirstViewPosition();
		C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		cm->enabledraw = false;
		SetWindowPos(cm->GetActiveFrame()->GetSafeHwnd(),HWND_TOP,0,0,m_img->GetWidth(),m_img->GetHeight(),SWP_SHOWWINDOW);
		UpdateAllViews(NULL);
	}
	// TODO: 在此添加命令处理程序代码
}


void C图片管理器Doc::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	if (!data.empty())
	{
		 data.pop_back(); 
	}
		 UpdateAllViews(NULL);
}


void C图片管理器Doc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	
	if (!allowdraw) 
		{
			AfxMessageBox("在只读状态下无法保存");
			return;
	}
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp格式 (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	SetTitle(((C图片管理器App*)AfxGetApp())->CurrentUser+"-"+m_path_name);
	
	
	C图片管理器App* thisapp = (C图片管理器App*)AfxGetApp();
	POSITION  POS = GetFirstViewPosition();
	C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);


	myado.OnInitADOConn("权限");
	myado.NewFile(thisapp->CurrentUser,m_path_name,"写");
	myado.ExitConnect();

}


void C图片管理器Doc::OnUpdateChangeSize(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	if ((m_img==NULL)&&(cm->enabledraw))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}


void C图片管理器Doc::OnChangeSize()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CSizeDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		SetWindowPos(cm->GetActiveFrame()->GetSafeHwnd(),HWND_TOP,0,0,dlg.width+20,dlg.height+43,SWP_SHOWWINDOW);
	}
}


//int C图片管理器Doc::CheckFileState(void)
//{
//	return 0;
//}


int C图片管理器Doc::CheckFileState(CString username, CString filepath)
{
	myado.OnInitADOConn("权限");
	myado.m_pRecordset->MoveFirst();
	bool findrecord = false;
	int state;
	CString du = "读",xie = "写";
	while (!myado.m_pRecordset->adoEOF)
	{
		if ((username.Compare((_bstr_t)(myado.m_pRecordset->GetCollect("用户名")))==0)&&(filepath.Compare((_bstr_t)(myado.m_pRecordset->GetCollect("文件路径")))==0))
		{
			findrecord = true;
			if (du.Compare((bstr_t)(myado.m_pRecordset->GetCollect("访问权限")))==0) {state =  READ_ONLY;break;}
			if (xie.Compare((bstr_t)(myado.m_pRecordset->GetCollect("访问权限")))==0) {state =  CAN_WRITE;break;}
		}
		myado.m_pRecordset->MoveNext();
	}
	myado.m_pRecordset->MoveFirst();
	myado.ExitConnect();
	if (!findrecord) state =  NO_ACCESS;
	return state;
}


int C图片管理器Doc::LoadImage()
{


	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg格式 (*.jpg)|*.jpg|bmp格式 (*.bmp)|*.bmp||",NULL);
	C图片管理器App* thisapp = (C图片管理器App* )AfxGetApp();
	if(dlg.DoModal()==IDOK)
	{
		m_path_name = dlg.GetPathName();
		if (CheckFileState(thisapp->CurrentUser,m_path_name)==NO_ACCESS)
		{
			AfxMessageBox("您没有访问权限");
			UpdateAllViews(NULL);
			return false;
		}
		else
		{
			if (CheckFileState(thisapp->CurrentUser,m_path_name)==READ_ONLY) 
			{
				allowdraw = FALSE;	
				AfxMessageBox("您有只读权限");
			}
			else allowdraw = TRUE;
		}


		if(m_srcimg==NULL) m_srcimg=new CImage();
		else m_srcimg->Destroy();//释放以前的图片
		m_srcimg->Load(m_path_name);

		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//释放以前的图片
		SetTitle(((C图片管理器App*)AfxGetApp())->CurrentUser+"-"+m_path_name);

		if ((m_srcimg->GetHeight()>800)||(m_srcimg->GetWidth()>1200))
		{
			AfxMessageBox("您载入的图片太大，已经做了相应缩放");
			int tempheight = 600;
			int tempwidth = tempheight*m_srcimg->GetWidth()/m_srcimg->GetHeight();
			CreateStretchedImage(m_srcimg,m_img,tempheight,tempwidth);
		}
		else
			ImageCopy(*m_srcimg,*m_img);

		POSITION  POS = GetFirstViewPosition();
		C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		cm->enabledraw = false;
		SetWindowPos(cm->GetActiveFrame()->GetSafeHwnd(),HWND_TOP,0,0,m_img->GetWidth(),m_img->GetHeight(),SWP_SHOWWINDOW);
		UpdateAllViews(NULL);
	}
	else 
		return false;
	return true;
}



// Resize CImage
void C图片管理器Doc::CreateStretchedImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth)
{
	if(pImage->IsDIBSection()){
		// 取得 pImage 的 DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image 因為有自己的 DC, 所以必須使用 FromHandle 取得對應的 DC


		CBitmap *bitmap1=pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);

		// 建立新的 CImage
		ResultImage->Create(StretchWidth,StretchHeight,bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());

		// 當 Destination 比較小的時候, 會根據 Destination DC 上的 Stretch Blt mode 決定是否要保留被刪除點的資訊
		ResultImageDC->SetStretchBltMode(HALFTONE); // 使用最高品質的方式
		::SetBrushOrgEx(ResultImageDC->m_hDC,0,0,NULL); // 調整 Brush 的起點

		// 把 pImage 畫到 ResultImage 上面
		StretchBlt(*ResultImageDC,0,0,StretchWidth,StretchHeight,*pImageDC1,0,0,pImage->GetWidth(),pImage->GetHeight(),SRCCOPY);
		// pImage->Draw(*ResultImageDC,0,0,StretchWidth,StretchHeight,0,0,pImage->GetWidth(),pImage->GetHeight());

		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
}



bool C图片管理器Doc::ImageCopy(const CImage &srcImage, CImage &destImage)
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

bool C图片管理器Doc::IsEmpty(void)
{
	if (((data.size()==0)&&(m_path_name==""))||(!allowdraw))
		return true;
	else
	return false;
}
