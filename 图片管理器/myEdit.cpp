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
			
			((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_RETURN_PRESSED,0,0);

			return true;
		}
		
	}

	return CEdit::PreTranslateMessage(pMsg);

}

BEGIN_MESSAGE_MAP(myEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &myEdit::OnEnChange)
END_MESSAGE_MAP()



// myEdit ��Ϣ�������




void myEdit::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEdit::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CMainFrame*)AfxGetMainWnd())->PostMessage(ID_CONTENT_CHANGE,0,0);
	//����м��룬ֱ�ӷ��أ���Ϊ����Ҫʵ��Ԥ������
}
