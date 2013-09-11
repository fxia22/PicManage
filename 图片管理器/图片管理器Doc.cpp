
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
#include "SizeDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CͼƬ������Doc

IMPLEMENT_DYNCREATE(CͼƬ������Doc, CDocument)

BEGIN_MESSAGE_MAP(CͼƬ������Doc, CDocument)



	ON_COMMAND(ID_FILE_SAVE, &CͼƬ������Doc::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CͼƬ������Doc::OnFileOpen)
	ON_COMMAND(ID_EDIT_UNDO, &CͼƬ������Doc::OnEditUndo)
	ON_COMMAND(ID_FILE_SAVE_AS, &CͼƬ������Doc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_SIZE, &CͼƬ������Doc::OnUpdateChangeSize)
	ON_COMMAND(ID_CHANGE_SIZE, &CͼƬ������Doc::OnChangeSize)
END_MESSAGE_MAP()


// CͼƬ������Doc ����/����

CͼƬ������Doc::CͼƬ������Doc()
{
	// TODO: �ڴ����һ���Թ������
	m_bkgclr = RGB(255,255,255);
	m_path_name = _T("");
	allowdraw = false;
}

CͼƬ������Doc::~CͼƬ������Doc()
{
}

BOOL CͼƬ������Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	cm->enabledraw = true;
	cm->drawstatus = CMainFrame::DRAW_BRUSH;
	SetTitle(((CͼƬ������App*)AfxGetApp())->CurrentUser+"-δ����");
	allowdraw = true;
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


	if (!allowdraw) 
	{
		AfxMessageBox("��ֻ��״̬���޷�����");
		return;
	}
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	SetTitle(((CͼƬ������App*)AfxGetApp())->CurrentUser+"-"+m_path_name);
	POSITION  POS = GetFirstViewPosition();
	CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);
	CͼƬ������App* thisapp = (CͼƬ������App*)AfxGetApp();
	myado.OnInitADOConn("Ȩ��");	
	myado.NewFile(thisapp->CurrentUser,m_path_name,"д");
	myado.ExitConnect();
	


}

void CͼƬ������Doc::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg��ʽ (*.jpg)|*.jpg|bmp��ʽ (*.bmp)|*.bmp||",NULL);
	CͼƬ������App* thisapp = (CͼƬ������App* )AfxGetApp();
	if(dlg.DoModal()==IDOK)
	{
		m_path_name = dlg.GetPathName();
		if (CheckFileState(thisapp->CurrentUser,m_path_name)==NO_ACCESS)
		{
			AfxMessageBox("��û�з���Ȩ��");
			UpdateAllViews(NULL);
			return;
		}
		else
		{
			if (CheckFileState(thisapp->CurrentUser,m_path_name)==READ_ONLY) 
			{
				allowdraw = FALSE;	
				AfxMessageBox("����ֻ��Ȩ��");
			}
			else allowdraw = TRUE;
		}


		if(m_srcimg==NULL) m_srcimg=new CImage();
		else m_srcimg->Destroy();//�ͷ���ǰ��ͼƬ
		m_srcimg->Load(m_path_name);

		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//�ͷ���ǰ��ͼƬ
		SetTitle(((CͼƬ������App*)AfxGetApp())->CurrentUser+"-"+m_path_name);

		if ((m_srcimg->GetHeight()>800)||(m_srcimg->GetWidth()>1200))
		{
			AfxMessageBox("�������ͼƬ̫���Ѿ�������Ӧ����");
			int tempheight = 600;
			int tempwidth = tempheight*m_srcimg->GetWidth()/m_srcimg->GetHeight();
			CreateStretchedImage(m_srcimg,m_img,tempheight,tempwidth);
		}
		else
			ImageCopy(*m_srcimg,*m_img);

		POSITION  POS = GetFirstViewPosition();
		CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
		CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		cm->enabledraw = false;
		SetWindowPos(cm->GetActiveFrame()->GetSafeHwnd(),HWND_TOP,0,0,m_img->GetWidth(),m_img->GetHeight(),SWP_SHOWWINDOW);
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


void CͼƬ������Doc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	
	if (!allowdraw) 
		{
			AfxMessageBox("��ֻ��״̬���޷�����");
			return;
	}
	CFileDialog fdlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,"bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if (m_path_name=="")
	{
		if(fdlg.DoModal() == IDOK) 
		{  
			m_path_name = fdlg.GetPathName()+".bmp"; 
		}
	}
	SetTitle(((CͼƬ������App*)AfxGetApp())->CurrentUser+"-"+m_path_name);
	
	
	CͼƬ������App* thisapp = (CͼƬ������App*)AfxGetApp();
	POSITION  POS = GetFirstViewPosition();
	CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
	cv->SaveCurrentImage((LPSTR)(LPCTSTR)m_path_name);


	myado.OnInitADOConn("Ȩ��");
	myado.NewFile(thisapp->CurrentUser,m_path_name,"д");
	myado.ExitConnect();

}


void CͼƬ������Doc::OnUpdateChangeSize(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	if ((m_img==NULL)&&(cm->enabledraw))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}


void CͼƬ������Doc::OnChangeSize()
{
	// TODO: �ڴ���������������
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CSizeDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		SetWindowPos(cm->GetActiveFrame()->GetSafeHwnd(),HWND_TOP,0,0,dlg.width+20,dlg.height+43,SWP_SHOWWINDOW);
	}
}


//int CͼƬ������Doc::CheckFileState(void)
//{
//	return 0;
//}


int CͼƬ������Doc::CheckFileState(CString username, CString filepath)
{
	myado.OnInitADOConn("Ȩ��");
	myado.m_pRecordset->MoveFirst();
	bool findrecord = false;
	int state;
	CString du = "��",xie = "д";
	while (!myado.m_pRecordset->adoEOF)
	{
		if ((username.Compare((_bstr_t)(myado.m_pRecordset->GetCollect("�û���")))==0)&&(filepath.Compare((_bstr_t)(myado.m_pRecordset->GetCollect("�ļ�·��")))==0))
		{
			findrecord = true;
			if (du.Compare((bstr_t)(myado.m_pRecordset->GetCollect("����Ȩ��")))==0) {state =  READ_ONLY;break;}
			if (xie.Compare((bstr_t)(myado.m_pRecordset->GetCollect("����Ȩ��")))==0) {state =  CAN_WRITE;break;}
		}
		myado.m_pRecordset->MoveNext();
	}
	myado.m_pRecordset->MoveFirst();
	myado.ExitConnect();
	if (!findrecord) state =  NO_ACCESS;
	return state;
}


int CͼƬ������Doc::LoadImage()
{


	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"jpg��ʽ (*.jpg)|*.jpg|bmp��ʽ (*.bmp)|*.bmp||",NULL);
	CͼƬ������App* thisapp = (CͼƬ������App* )AfxGetApp();
	if(dlg.DoModal()==IDOK)
	{
		m_path_name = dlg.GetPathName();
		if (CheckFileState(thisapp->CurrentUser,m_path_name)==NO_ACCESS)
		{
			AfxMessageBox("��û�з���Ȩ��");
			UpdateAllViews(NULL);
			return false;
		}
		else
		{
			if (CheckFileState(thisapp->CurrentUser,m_path_name)==READ_ONLY) 
			{
				allowdraw = FALSE;	
				AfxMessageBox("����ֻ��Ȩ��");
			}
			else allowdraw = TRUE;
		}


		if(m_srcimg==NULL) m_srcimg=new CImage();
		else m_srcimg->Destroy();//�ͷ���ǰ��ͼƬ
		m_srcimg->Load(m_path_name);

		if(m_img==NULL) m_img=new CImage();
		else m_img->Destroy();//�ͷ���ǰ��ͼƬ
		SetTitle(((CͼƬ������App*)AfxGetApp())->CurrentUser+"-"+m_path_name);

		if ((m_srcimg->GetHeight()>800)||(m_srcimg->GetWidth()>1200))
		{
			AfxMessageBox("�������ͼƬ̫���Ѿ�������Ӧ����");
			int tempheight = 600;
			int tempwidth = tempheight*m_srcimg->GetWidth()/m_srcimg->GetHeight();
			CreateStretchedImage(m_srcimg,m_img,tempheight,tempwidth);
		}
		else
			ImageCopy(*m_srcimg,*m_img);

		POSITION  POS = GetFirstViewPosition();
		CͼƬ������View *cv = (CͼƬ������View *) GetNextView(POS);
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
void CͼƬ������Doc::CreateStretchedImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth)
{
	if(pImage->IsDIBSection()){
		// ȡ�� pImage �� DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image ������Լ��� DC, ���Ա��ʹ�� FromHandle ȡ�Ì����� DC


		CBitmap *bitmap1=pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);

		// �����µ� CImage
		ResultImage->Create(StretchWidth,StretchHeight,bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());

		// �� Destination ���^С�ĕr��, ������ Destination DC �ϵ� Stretch Blt mode �Q���Ƿ�Ҫ�������h���c���YӍ
		ResultImageDC->SetStretchBltMode(HALFTONE); // ʹ�����Ʒ�|�ķ�ʽ
		::SetBrushOrgEx(ResultImageDC->m_hDC,0,0,NULL); // �{�� Brush �����c

		// �� pImage ���� ResultImage ����
		StretchBlt(*ResultImageDC,0,0,StretchWidth,StretchHeight,*pImageDC1,0,0,pImage->GetWidth(),pImage->GetHeight(),SRCCOPY);
		// pImage->Draw(*ResultImageDC,0,0,StretchWidth,StretchHeight,0,0,pImage->GetWidth(),pImage->GetHeight());

		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
}



bool CͼƬ������Doc::ImageCopy(const CImage &srcImage, CImage &destImage)
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

bool CͼƬ������Doc::IsEmpty(void)
{
	if (((data.size()==0)&&(m_path_name==""))||(!allowdraw))
		return true;
	else
	return false;
}
