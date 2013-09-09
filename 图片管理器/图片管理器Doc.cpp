
// ͼƬ������Doc.cpp : CͼƬ������Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ͼƬ������.h"
#endif

#include "ͼƬ������Doc.h"
#include "ͼƬ������View.h"
#include <propkey.h>
#include "MyFileDialog.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CͼƬ������Doc

IMPLEMENT_DYNCREATE(CͼƬ������Doc, CDocument)

BEGIN_MESSAGE_MAP(CͼƬ������Doc, CDocument)



	ON_COMMAND(ID_FILE_SAVE, &CͼƬ������Doc::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CͼƬ������Doc::OnFileOpen)
	ON_COMMAND(ID_EDIT_UNDO, &CͼƬ������Doc::OnEditUndo)
END_MESSAGE_MAP()


// CͼƬ������Doc ����/����

CͼƬ������Doc::CͼƬ������Doc()
{
	// TODO: �ڴ����һ���Թ������
	m_bkgclr = RGB(255,255,255);
	m_path_name = _T("");
}

CͼƬ������Doc::~CͼƬ������Doc()
{
}

BOOL CͼƬ������Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CͼƬ������Doc ���л�

void CͼƬ������Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CͼƬ������Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CͼƬ������Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CͼƬ������Doc::SetSearchContent(const CString& value)
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

// CͼƬ������Doc ���

#ifdef _DEBUG
void CͼƬ������Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CͼƬ������Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CͼƬ������Doc ����




void CͼƬ������Doc::OnFileSave()
{
	// TODO: �ڴ���������������
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	POSITION  POS = GetFirstViewPosition();
	CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);

}


void CͼƬ������Doc::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg��ʽ (*.jpg)|*.jpg|bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if(dlg.DoModal()==IDOK)
	{
		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//�ͷ���ǰ��ͼƬ
		m_img->Load(dlg.GetPathName());
		POSITION  POS = GetFirstViewPosition();
		CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		cm->enabledraw = false;

		UpdateAllViews(NULL);
	}
	// TODO: �ڴ���������������
}


void CͼƬ������Doc::OnEditUndo()
{
	// TODO: �ڴ���������������
	if (!data.empty())
	{
		 data.pop_back(); 
	}
		 UpdateAllViews(NULL);
}
