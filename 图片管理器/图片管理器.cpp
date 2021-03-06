
// 图片管理器.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "图片管理器.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "图片管理器Doc.h"
#include "图片管理器View.h"
#include "LogInBox.h"
#include "CAboutDlg.h"
#include "CommandDlg.h"
#include "CommanddlgObj.h"
#include "AdminDlg.h"
#include "StyleDlg.h"
#include "FileManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C图片管理器App

BEGIN_MESSAGE_MAP(C图片管理器App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &C图片管理器App::OnAppAbout)
	// 基于文件的标准文档命令
//	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	//自己定义的命令
	ON_COMMAND(ID_LOGIN, &C图片管理器App::OnLogin)
	ON_COMMAND(ID_LOGOUT, &C图片管理器App::OnLogout)
	ON_COMMAND(ID_CREATEELE, &C图片管理器App::OnCreateele)
	ON_COMMAND(ID_CREATEOBJ, &C图片管理器App::OnCreateobj)
	ON_COMMAND(ID_CALLADMIN, &C图片管理器App::OnCalladmin)
	ON_COMMAND(ID_FILE_NEW, &C图片管理器App::OnFileNew)
	//ON_COMMAND(ID_FILE_NEW, &C图片管理器App::OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &C图片管理器App::OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &C图片管理器App::OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &C图片管理器App::OnFileOpen)
	
	
	ON_UPDATE_COMMAND_UI(ID_MYFILE, &C图片管理器App::OnUpdateMyfile)
	ON_COMMAND(ID_MYFILE, &C图片管理器App::OnMyfile)
	ON_UPDATE_COMMAND_UI(ID_LOGIN, &C图片管理器App::OnUpdateLogin)
	ON_COMMAND(ID_MENU_FILEMAN, &C图片管理器App::OnMenuFileman)
	ON_UPDATE_COMMAND_UI(ID_MENU_FILEMAN, &C图片管理器App::OnUpdateMenuFileman)
	ON_UPDATE_COMMAND_UI(ID_FILESEARCH, &C图片管理器App::OnUpdateFilesearch)
END_MESSAGE_MAP()


// C图片管理器App 构造

C图片管理器App::C图片管理器App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("图片管理器.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	CurrentUser = _T("");
	m_LoginStatus = false;
}

// 唯一的一个 C图片管理器App 对象

C图片管理器App theApp;


// C图片管理器App 初始化

BOOL C图片管理器App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	::CoInitialize(NULL);//初始化数据库连接
	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(5);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MyTYPE,
		RUNTIME_CLASS(C图片管理器Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(C图片管理器View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int C图片管理器App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);
	::CoUninitialize();//关闭COM环境
	return CWinApp::ExitInstance();
}

// C图片管理器App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NEWCLIENT, &CAboutDlg::OnBnClickedNewclient)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void C图片管理器App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// C图片管理器App 消息处理程序

void C图片管理器App::OnLogin()
{
	LogInBox lbx;
	lbx.DoModal();
}


void C图片管理器App::OnLogout()
{
	if (((CMainFrame*)m_pMainWnd)->ExitAllChildFrame())
	{
		CurrentUser = "";
		m_LoginStatus = false;
		MessageBox(NULL,"注销成功","注销",MB_OK);
		((CMainFrame*)m_pMainWnd)->enabledraw = 0;
	}
	else
	{
		AfxMessageBox("您尚有未关闭的文件");
	}
}


void CAboutDlg::OnBnClickedNewclient()
{
	// TODO: 在此添加控件通知处理程序代码




}


void C图片管理器App::OnCreateele()
{
	// TODO: 在此添加命令处理程序代码
	CommandDlg dlg;
	dlg.DoModal();
}


void C图片管理器App::OnCreateobj()
{
	// TODO: 在此添加命令处理程序代码
	CommandDlgObj dlg;
	dlg.DoModal();
}


void C图片管理器App::OnCalladmin()
{
	CAdminDlg dlg;
	dlg.DoModal();
	// TODO: 在此添加命令处理程序代码
}




//void C图片管理器App::OnFileNew()
//{
//	// TODO: 在此添加命令处理程序代码]
//	CWin::OnFileNew()
//}


void C图片管理器App::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	while (!m_LoginStatus) 
		{	
		//	AfxMessageBox("欢迎来到本系统，请您登陆");
			OnLogin();
	}
	CWinApp::OnFileNew();

}


void C图片管理器App::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_LoginStatus)
		 pCmdUI->Enable(FALSE);
	else
	 pCmdUI->Enable();
}


void C图片管理器App::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_LoginStatus)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}



void C图片管理器App::OnFileOpen()
{
	OnFileNew();
	CMainFrame* cm = (CMainFrame*)m_pMainWnd;
	C图片管理器Doc* cd = (C图片管理器Doc*)cm->GetActiveFrame()->GetActiveDocument();
	if (!cd) return;
	cd->OnFileOpen();
	return;
	// TODO: 在此添加命令处理程序代码
}



//void C图片管理器App::NewFile(void)
//{
//	OnFileNew();
//}




void C图片管理器App::OnUpdateMyfile(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_LoginStatus)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}


void C图片管理器App::OnMyfile()
{
	// TODO: 在此添加命令处理程序代码
	OnFileNew();
	CMainFrame* cm = (CMainFrame*)m_pMainWnd;
	C图片管理器Doc* cd = (C图片管理器Doc*)cm->GetActiveFrame()->GetActiveDocument();
	if (!cd->LoadImage())
		((CChildFrame*)cm->GetActiveFrame())->ExitWithoutQuery();
}


void C图片管理器App::OnUpdateLogin(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_LoginStatus)
		 pCmdUI->Enable(0);
	else pCmdUI->Enable();
}


void C图片管理器App::OnMenuFileman()
{
	// TODO: 在此添加命令处理程序代码
	CFileManageDlg dlg;
	dlg.DoModal();
}



void C图片管理器App::OnUpdateMenuFileman(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_LoginStatus)
		 pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}



void C图片管理器App::OnCerTainFileOpen(CString str)
{
	OnFileNew();
	CMainFrame* cm = (CMainFrame*)m_pMainWnd;
	C图片管理器Doc* cd = (C图片管理器Doc*)cm->GetActiveFrame()->GetActiveDocument();
	if (!cd->LoadImage(str))
	{
		((CChildFrame*)cm->GetActiveFrame())->GetActiveDocument()->OnCloseDocument();
	}
		// TODO: 在此添加命令处理程序代码
}



void C图片管理器App::OnUpdateFilesearch(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_LoginStatus)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}
