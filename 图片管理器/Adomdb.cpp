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
	
	//::CoInitialize(NULL); //��ʼ��OLE/COM�⻷��
	//****************************************************************************
	// _ConnectionPtrͨ������������һ���������ӻ�ִ��һ���������κν����SQL��䣬
	// ��һ���洢���̡�
	// _ConnectionPtr m_pCon(__uuidof(Connection)); 
	m_pConnection.CreateInstance(__uuidof(Connection));
	//*****************************************************************************
	//****************************************************************************
	//_RecordsetPtr��һ����¼���������������ֶ���������Լ�¼���ṩ�˸���Ŀ��ƹ��ܣ�
	// ���¼�������α���Ƶ�
	// _RecordsetPtr m_pRec(__uuidof(Recordset)); 
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//*****************************************************************************

	CString str = "SELECT * FROM "+sheetname;
	try
	{
		//�������ݿ�
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //���������Ϣ
	}
	try
	{
		m_pRecordset->Open(_variant_t(str),
			_variant_t((IDispatch*)m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: ��̬ adOpenDynamic����̬ adLockOptimistic�ֹ۷����� adCmdText���ı���ѯ���
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage()); //���������Ϣ
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
		//�������ݵ����ݿ����
		m_pRecordset->AddNew(); 
		m_pRecordset->PutCollect("�û���", _variant_t(name));
		m_pRecordset->PutCollect("����", _variant_t(password));
		m_pRecordset->Update();
	}
	catch(_com_error e)
	{ 
		flag = false;
		AfxMessageBox(e.ErrorMessage());
	}

	
	return flag;
}




bool Adomdb::NewFile(CString username, CString filename, CString sudo)
{
	bool flag = true;
	try{
		//�������ݵ����ݿ����
		m_pRecordset->AddNew(); 
		m_pRecordset->PutCollect("�û���", _variant_t(username));
		m_pRecordset->PutCollect("�ļ�·��", _variant_t(filename));
		m_pRecordset->PutCollect("����Ȩ��", _variant_t(sudo));
		m_pRecordset->Update();

	}
	catch(_com_error e)
	{ 
		flag = false;
		AfxMessageBox(e.ErrorMessage());
	}


	return flag;
}