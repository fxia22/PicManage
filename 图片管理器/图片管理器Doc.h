
// 图片管理器Doc.h : C图片管理器Doc 类的接口
//


#pragma once
#include "Line.h"
#include <vector>

using namespace std;
class C图片管理器Doc : public CDocument
{
public:enum 
	   {
		   CAN_WRITE,
		   READ_ONLY,
		   NO_ACCESS
	   };
protected: // 仅从序列化创建
	C图片管理器Doc();
	DECLARE_DYNCREATE(C图片管理器Doc)

// 特性
public:
		vector<MyObject*> data;//用于保存所有需要绘制的直线
		COLORREF m_bkgclr;
		// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~C图片管理器Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP();


//自己定义的变量


#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileUpdate();
	afx_msg void OnFileSave();
	CString m_path_name;
//	CImage m_img;
	afx_msg void OnFileOpen();
	CImage* m_img;
	afx_msg void OnEditUndo();
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateChangeSize(CCmdUI *pCmdUI);
	afx_msg void OnChangeSize();
//	Adomdb ado;
	Adomdb myado;
//	int CheckFileState(void);
	int CheckFileState(CString username, CString filepath);
	bool allowdraw;
	int LoadImage();
	void CreateStretchedImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth);
	bool ImageCopy(const CImage &srcImage, CImage &destImage);
	CImage* m_srcimg;
	bool IsEmpty(void);
};
