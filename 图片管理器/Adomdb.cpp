#include "stdafx.h"
#include "Adomdb.h"


Adomdb::Adomdb(void)
{
}


Adomdb::~Adomdb(void)
{
}


void Adomdb::OnInitADOConn(CString sheetname)
{
	
	//::CoInitialize(NULL); //初始化OLE/COM库环境
	//****************************************************************************
	// _ConnectionPtr通常被用来创建一个数据连接或执行一条不返回任何结果的SQL语句，
	// 如一个存储过程。
	// _ConnectionPtr m_pCon(__uuidof(Connection)); 
	m_pConnection.CreateInstance(__uuidof(Connection));
	//*****************************************************************************
	//****************************************************************************
	//_RecordsetPtr是一个记录集对象。与以上两种对象相比它对记录集提供了更多的控制功能，
	// 如记录锁定、游标控制等
	// _RecordsetPtr m_pRec(__uuidof(Recordset)); 
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//*****************************************************************************

	CString str = "SELECT * FROM "+sheetname;
	try
	{
		//连接数据库
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //输出错误信息
	}
	try
	{
		m_pRecordset->Open(_variant_t(str),
			_variant_t((IDispatch*)m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: 静态 adOpenDynamic：动态 adLockOptimistic乐观封锁法 adCmdText：文本查询语句
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage()); //输出错误信息
	}
}


void Adomdb::ExitConnect(void)
{
	if(m_pRecordset->State)
	{		
		m_pRecordset->Close();
		m_pRecordset= NULL;
	}
	if(m_pConnection->State)
	{
		m_pConnection->Close();
		m_pConnection= NULL;
	}
	//
}


bool Adomdb::NewUser(CString name, CString password)
{
	bool flag = true;
	try{
		//增加数据到数据库操作
		m_pRecordset->AddNew(); 
		m_pRecordset->PutCollect("用户名", _variant_t(name));
		m_pRecordset->PutCollect("密码", _variant_t(password));
		m_pRecordset->Update();
	}
	catch(_com_error e)
	{ 
		flag = false;
		AfxMessageBox(e.ErrorMessage());
	}

	
	return flag;
}




bool Adomdb::NewFile(CString username, CString filename, CString sudo,CString group)
{
	bool flag = true;
	try{
		//增加数据到数据库操作
		m_pRecordset->AddNew(); 
		m_pRecordset->PutCollect("用户名", _variant_t(username));
		m_pRecordset->PutCollect("文件路径", _variant_t(filename));
		m_pRecordset->PutCollect("访问权限", _variant_t(sudo));
		m_pRecordset->Update();

	}
	catch(_com_error e)
	{ 
		flag = false;
		AfxMessageBox(e.ErrorMessage());
	}


	return flag;
}



int Adomdb::CheckFileState(CString username, CString filepath)
{
	OnInitADOConn("权限");
	m_pRecordset->MoveFirst();
	bool findrecord = false;
	int state;
	CString du = "读",xie = "写";
	while (!m_pRecordset->adoEOF)
	{
		if ((username.Compare((_bstr_t)(m_pRecordset->GetCollect("用户名")))==0)&&(filepath.Compare((_bstr_t)(m_pRecordset->GetCollect("文件路径")))==0))
		{
			findrecord = true;
			if (du.Compare((bstr_t)(m_pRecordset->GetCollect("访问权限")))==0) {state =  READ_ONLY;break;}
			if (xie.Compare((bstr_t)(m_pRecordset->GetCollect("访问权限")))==0) {state =  CAN_WRITE;break;}
		}
		m_pRecordset->MoveNext();
	}
	m_pRecordset->MoveFirst();
	ExitConnect();
	if (!findrecord) state =  NO_ACCESS;
	return state;
}



bool Adomdb::NewFileToGroup(CString username, CString filename, CString sudo,CString group)
{
	bool flag = true;
	try{
		//增加数据到数据库操作
		m_pRecordset->AddNew(); 
		m_pRecordset->PutCollect("用户名", _variant_t(username));
		m_pRecordset->PutCollect("文件路径", _variant_t(filename));
		m_pRecordset->PutCollect("图片组", _variant_t(group));
		m_pRecordset->Update();

	}
	catch(_com_error e)
	{ 
		flag = false;
		AfxMessageBox(e.ErrorMessage());
	}


	return flag;
}
