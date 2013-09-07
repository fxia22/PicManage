// StyleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "StyleDlg.h"
#include "afxdialogex.h"


// CStyleDlg 对话框

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


// CStyleDlg 消息处理程序


void CStyleDlg::OnNMCustomdrawStSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	str.Format("%d",m_csc.GetPos());
	//MessageBox(NULL,str);
	m_linewidth.SetWindowTextA(str);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}


BOOL CStyleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_csc.SetRange(1,20);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStyleDlg::OnBnClickedRadio(UINT ID)
{
	// TODO: 在此添加控件通知处理程序代码
}
