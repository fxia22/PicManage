
// stdafx.cpp : 只包括标准包含文件的源文件
// 图片管理器.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
/*
BOOL OpenRecordSet(_RecordsetPtr &recPtr, CString &strmdb)
{
	CdatabaseApp* pApp=(CdatabaseApp*)AfxGetApp();
	//修改App类

	try
	{
		recPtr->Open(strmdb.AllocSysString(),pApp->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		CString strError;
		strError.Format("警告：打开数据表发生异常,错误信息：%s",e.ErrorMessage());
		AfxMessageBox(strError);
		return FALSE;
	}
	return TRUE;
}

*/