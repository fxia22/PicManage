#if !defined(AFX_TOOLBAREDITSTATIC_H__2EC217EE_E3AC_42C5_A9E9_4D0AADA7EFA4__INCLUDED_)
#define AFX_TOOLBAREDITSTATIC_H__2EC217EE_E3AC_42C5_A9E9_4D0AADA7EFA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarEditStatic.h : header file
//
#include "myEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CToolBarEditStatic window

class CToolBarEditStatic : public CToolBar
{
// Construction
public:
	CToolBarEditStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEditStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	CStatic m_Static1,m_Static2;
	myEdit m_Edit1,m_Edit2;
	virtual ~CToolBarEditStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarEditStatic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAREDITSTATIC_H__2EC217EE_E3AC_42C5_A9E9_4D0AADA7EFA4__INCLUDED_)
