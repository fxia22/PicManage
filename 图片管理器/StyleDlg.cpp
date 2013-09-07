// StyleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "StyleDlg.h"
#include "afxdialogex.h"


// CStyleDlg �Ի���

IMPLEMENT_DYNAMIC(CStyleDlg, CDialogEx)

CStyleDlg::CStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStyleDlg::IDD, pParent)
{
	m_csc.SetRange(0,100);

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
END_MESSAGE_MAP()


// CStyleDlg ��Ϣ�������


void CStyleDlg::OnNMCustomdrawStSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	str.Format("%d",m_csc.GetPos());
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CStyleDlg::OnBnClickedRadio(UINT ID)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
