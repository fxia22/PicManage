#pragma once
class Adomdb
{
public:
	enum 
	{
		CAN_WRITE,
		READ_ONLY,
		NO_ACCESS
	};
public:
	Adomdb(void);
	~Adomdb(void);
	_ConnectionPtr  m_pConnection;
	_RecordsetPtr m_pRecordset;
	_CommandPtr m_pCommand;
	void OnInitADOConn(CString);
	void ExitConnect(void);
	bool NewUser(CString name, CString password);
	bool NewFile(CString username, CString filename, CString sudo,CString group="");
	int CheckFileState(CString username, CString filepath);
	bool NewFileToGroup(CString username, CString filename, CString sudo,CString group);
};

