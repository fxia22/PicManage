// myEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "myEdit.h"
#include "Resource.h"
#include "MainFrm.h"

// myEdit

IMPLEMENT_DYNAMIC(myEdit, CEdit)

myEdit::myEdit()
{

}

myEdit::~myEdit()
{
}
//重载PreTranslateMessage函数，拦截CEdit的回车信息
BOOL myEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam == 0x0d)//如果是回车
		{
			//向父窗口发送消息
			
			((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_RETURN_PRESSED,0,0);

			return true;
		}
		
	}

	return CEdit::PreTranslateMessage(pMsg);

}

BEGIN_MESSAGE_MAP(myEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &myEdit::OnEnChange)
END_MESSAGE_MAP()



// myEdit 消息处理程序




void myEdit::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_CONTENT_CHANGE,0,0);
	//如果有键入，直接返回，因为我需要实现预览功能
}
