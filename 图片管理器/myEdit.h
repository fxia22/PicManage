#pragma once


// myEdit

class myEdit : public CEdit
{
	DECLARE_DYNAMIC(myEdit)

public:
	myEdit();
	virtual ~myEdit();
	BOOL PreTranslateMessage(MSG* pMsg); 
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChange();
};


