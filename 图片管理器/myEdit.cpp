// myEdit.cpp : ʵ���ļ�
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
//����PreTranslateMessage����������CEdit�Ļس���Ϣ
BOOL myEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam == 0x0d)//����ǻس�
		{
			//�򸸴��ڷ�����Ϣ
			MessageBeep(0xFFFFFF);
			((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_RETURN_PRESSED,0,0);

			return true;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);

}

BEGIN_MESSAGE_MAP(myEdit, CEdit)
END_MESSAGE_MAP()



// myEdit ��Ϣ�������


