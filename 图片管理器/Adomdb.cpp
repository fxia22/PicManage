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
		printf(e.ErrorMessage()); //输出错误信息
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
