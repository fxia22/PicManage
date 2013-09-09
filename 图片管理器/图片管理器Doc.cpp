
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
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C图片管理器Doc

IMPLEMENT_DYNCREATE(C图片管理器Doc, CDocument)

BEGIN_MESSAGE_MAP(C图片管理器Doc, CDocument)



	ON_COMMAND(ID_FILE_SAVE, &C图片管理器Doc::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &C图片管理器Doc::OnFileOpen)
	ON_COMMAND(ID_EDIT_UNDO, &C图片管理器Doc::OnEditUndo)
END_MESSAGE_MAP()


// C图片管理器Doc 构造/析构

C图片管理器Doc::C图片管理器Doc()
{
	// TODO: 在此添加一次性构造代码
	m_bkgclr = RGB(255,255,255);
	m_path_name = _T("");
}

C图片管理器Doc::~C图片管理器Doc()
{
}

BOOL C图片管理器Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

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
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp格式 (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	POSITION  POS = GetFirstViewPosition();
	C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);

}


void C图片管理器Doc::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg格式 (*.jpg)|*.jpg|bmp格式 (*.bmp)|*.bmp||",NULL);
	if(dlg.DoModal()==IDOK)
	{
		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//释放以前的图片
		m_img->Load(dlg.GetPathName());
		POSITION  POS = GetFirstViewPosition();
		C图片管理器View *cv = (C图片管理器View *) GetNextView(POS);
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		cm->enabledraw = false;

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
