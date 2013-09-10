#pragma once
class Adomdb
{
public:
	Adomdb(void);
	~Adomdb(void);
	_ConnectionPtr  m_pConnection;
	_RecordsetPtr m_pRecordset;
	_CommandPtr m_pCommand;
	void OnInitADOConn(CString);
	void ExitConnect(void);
	bool NewUser(CString name, CString password);
	bool NewFile(CString username, CString filename, CString sudo);
};

