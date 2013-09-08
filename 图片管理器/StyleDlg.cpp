// StyleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "StyleDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CStyleDlg �Ի���

IMPLEMENT_DYNAMIC(CStyleDlg, CDialogEx)

CStyleDlg::CStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStyleDlg::IDD, pParent)
{
	
	m_width = 0;
	m_style = -1;
}

CStyleDlg::~CStyleDlg()
{
}

void CStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_SLIDER, m_csc);
	DDX_Control(pDX, IDC_ST_EDIT, m_linewidth);
}


BEGIN_MESSAGE_MAP(CStyleDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ST_SLIDER, &CStyleDlg::OnNMCustomdrawStSlider)
	ON_COMMAND_RANGE(IDC_STYLE_RADIO1,IDC_STYLE_RADIO3, OnBnClickedRadio)
	ON_WM_PAINT()
//	ON_NOTIFY(TRBN_THUMBPOSCHANGING,   _SLIDER, &CStyleDlg::OnTRBNThumbPosChangingStSlider)
//ON_WM_LBUTTONUP()
ON_WM_HSCROLL()
ON_BN_CLICKED(IDOK, &CStyleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStyleDlg ��Ϣ�������
void CStyleDlg::OnNMCustomdrawStSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	m_width = m_csc.GetPos();
	str.Format("%d",m_width);
	//MessageBox(NULL,str);
	m_linewidth.SetWindowTextA(str);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;



}


BOOL CStyleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	m_csc.SetRange(1,20);
	CMainFrame* cm = (CMainFrame* )GetParent();
	m_width = cm->m_nLineWidth;
	m_csc.SetPos(m_width);
	switch(cm->m_nLineStyle)
	{
	case PS_SOLID:
			CheckDlgButton(IDC_STYLE_RADIO1,TRUE);
			CheckDlgButton(IDC_STYLE_RADIO2,FALSE);
			CheckDlgButton(IDC_STYLE_RADIO3,FALSE);
		break;
	case PS_DASH:
			CheckDlgButton(IDC_STYLE_RADIO2,TRUE);
			CheckDlgButton(IDC_STYLE_RADIO1,FALSE);
			CheckDlgButton(IDC_STYLE_RADIO3,FALSE);
		break;
	case PS_DASHDOT:
			CheckDlgButton(IDC_STYLE_RADIO1,FALSE);
			CheckDlgButton(IDC_STYLE_RADIO2,FALSE);
			CheckDlgButton(IDC_STYLE_RADIO3,TRUE);
		break;
	default:
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CStyleDlg::OnBnClickedRadio(UINT ID)
{
	CRect rect;
	GetDlgItem(IDC_ST_EXAMPLE)->GetWindowRect(&rect);
	switch (ID)
	{
		case IDC_STYLE_RADIO1:
		m_style = PS_SOLID;
		
			break;
		case IDC_STYLE_RADIO2:
			m_style = PS_DASH;
			
			break;
		case IDC_STYLE_RADIO3:
			m_style = PS_DASHDOT;
			
			break;
	default:
		break;
	}


	Invalidate();
	UpdateWindow();


	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CStyleDlg::OnPaint()
{
	 // device context for painting
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	UpdateData();
	//CPen pen(m_nLineStyle, m_nLineWidth, RGB(255, 0, 0)); 
	CPen pen(m_style,m_width, RGB(0,0,0));
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_ST_EXAMPLE)->GetWindowRect(&rect);
	

	ScreenToClient(&rect);

	dc.MoveTo(rect.left+20, rect.top+rect.Height()/2); 
	dc.LineTo(rect.right-20, rect.top+rect.Height()/2); 

	


	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


//void CStyleDlg::OnTRBNThumbPosChangingStSlider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// �˹���Ҫ�� Windows Vista ����߰汾��
//	// _WIN32_WINNT ���ű��� >= 0x0600��
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	Invalidate();
//	UpdateWindow();
//	*pResult = 0;
//}


//void CStyleDlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	Invalidate();
//	UpdateWindow();
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


void CStyleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox("123");
	Invalidate();
	UpdateWindow();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CStyleDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* cm = (CMainFrame* )GetParent();
	cm->m_nLineWidth = m_width;
	cm->m_nLineStyle = m_style;
	CDialogEx::OnOK();
}
