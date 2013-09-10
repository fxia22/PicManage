
// ͼƬ������.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ͼƬ������.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ͼƬ������Doc.h"
#include "ͼƬ������View.h"
#include "LogInBox.h"
#include "CAboutDlg.h"
#include "CommandDlg.h"
#include "CommanddlgObj.h"
#include "AdminDlg.h"
#include "StyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CͼƬ������App

BEGIN_MESSAGE_MAP(CͼƬ������App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CͼƬ������App::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
//	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	//�Լ����������
	ON_COMMAND(ID_LOGIN, &CͼƬ������App::OnLogin)
	ON_COMMAND(ID_LOGOUT, &CͼƬ������App::OnLogout)
	ON_COMMAND(ID_CREATEELE, &CͼƬ������App::OnCreateele)
	ON_COMMAND(ID_CREATEOBJ, &CͼƬ������App::OnCreateobj)
	ON_COMMAND(ID_CALLADMIN, &CͼƬ������App::OnCalladmin)
	ON_COMMAND(ID_FILE_NEW, &CͼƬ������App::OnFileNew)
	//ON_COMMAND(ID_FILE_NEW, &CͼƬ������App::OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CͼƬ������App::OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CͼƬ������App::OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CͼƬ������App::OnFileOpen)
	
	
	ON_UPDATE_COMMAND_UI(ID_MYFILE, &CͼƬ������App::OnUpdateMyfile)
	ON_COMMAND(ID_MYFILE, &CͼƬ������App::OnMyfile)
END_MESSAGE_MAP()


// CͼƬ������App ����

CͼƬ������App::CͼƬ������App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ͼƬ������.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	CurrentUser = _T("");
	m_LoginStatus = false;
}

// Ψһ��һ�� CͼƬ������App ����

CͼƬ������App theApp;


// CͼƬ������App ��ʼ��

BOOL CͼƬ������App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	::CoInitialize(NULL);//��ʼ�����ݿ�����
	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(5);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MyTYPE,
		RUNTIME_CLASS(CͼƬ������Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CͼƬ������View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CͼƬ������App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
	::CoUninitialize();//�ر�COM����
	return CWinApp::ExitInstance();
}

// CͼƬ������App ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NEWCLIENT, &CAboutDlg::OnBnClickedNewclient)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CͼƬ������App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CͼƬ������App ��Ϣ�������

void CͼƬ������App::OnLogin()
{
	LogInBox lbx;
	lbx.DoModal();
}


void CͼƬ������App::OnLogout()
{
	((CMainFrame*)m_pMainWnd)->ExitAllChildFrame();
	CurrentUser = "";
	m_LoginStatus = false;
	MessageBox(NULL,"ע���ɹ�","ע��",MB_OK);
}


void CAboutDlg::OnBnClickedNewclient()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������




}


void CͼƬ������App::OnCreateele()
{
	// TODO: �ڴ���������������
	CommandDlg dlg;
	dlg.DoModal();
}


void CͼƬ������App::OnCreateobj()
{
	// TODO: �ڴ���������������
	CommandDlgObj dlg;
	dlg.DoModal();
}


void CͼƬ������App::OnCalladmin()
{
	CAdminDlg dlg;
	dlg.DoModal();
	// TODO: �ڴ���������������
}




//void CͼƬ������App::OnFileNew()
//{
//	// TODO: �ڴ���������������]
//	CWin::OnFileNew()
//}


void CͼƬ������App::OnFileNew()
{
	// TODO: �ڴ���������������
	while (!m_LoginStatus) 
		{	
		//	AfxMessageBox("��ӭ������ϵͳ��������½");
			OnLogin();
	}
	CWinApp::OnFileNew();

}


void CͼƬ������App::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!m_LoginStatus)
		 pCmdUI->Enable(FALSE);
	else
	 pCmdUI->Enable();
}


void CͼƬ������App::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!m_LoginStatus)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}



void CͼƬ������App::OnFileOpen()
{
	OnFileNew();
	CMainFrame* cm = (CMainFrame*)m_pMainWnd;
	CͼƬ������Doc* cd = (CͼƬ������Doc*)cm->GetActiveFrame()->GetActiveDocument();
	if (!cd) return;
	cd->OnFileOpen();
	return;
	// TODO: �ڴ���������������
}



//void CͼƬ������App::NewFile(void)
//{
//	OnFileNew();
//}




void CͼƬ������App::OnUpdateMyfile(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!m_LoginStatus)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}


void CͼƬ������App::OnMyfile()
{
	// TODO: �ڴ���������������
	OnFileNew();
	CMainFrame* cm = (CMainFrame*)m_pMainWnd;
	CͼƬ������Doc* cd = (CͼƬ������Doc*)cm->GetActiveFrame()->GetActiveDocument();
	if (!cd->LoadImage())
		((CChildFrame*)cm->GetActiveFrame())->ExitWithoutQuery();
}
