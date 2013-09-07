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
			MessageBeep(0xFFFFFF);
			((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_RETURN_PRESSED,0,0);

			return true;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);

}

BEGIN_MESSAGE_MAP(myEdit, CEdit)
END_MESSAGE_MAP()



// myEdit 消息处理程序


